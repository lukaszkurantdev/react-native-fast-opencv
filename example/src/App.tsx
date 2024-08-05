import { PaintStyle, Skia } from '@shopify/react-native-skia';
import { useEffect } from 'react';
import { StyleSheet, Text } from 'react-native';
import { useOpenCV, type Rect } from 'react-native-fast-opencv';
import {
  Camera,
  useCameraDevice,
  useCameraPermission,
  useSkiaFrameProcessor,
} from 'react-native-vision-camera';
import { useResizePlugin } from 'vision-camera-resize-plugin';

export default function App() {
  const device = useCameraDevice('back');
  const { resize } = useResizePlugin();

  const { hasPermission, requestPermission } = useCameraPermission();

  useEffect(() => {
    requestPermission();
  }, [requestPermission]);

  const paint = Skia.Paint();
  paint.setStyle(PaintStyle.Fill);
  paint.setColor(Skia.Color('lime'));

  const cv = useOpenCV();

  const frameProcessor = useSkiaFrameProcessor((frame) => {
    'worklet';
    const height = frame.height / 4;
    const width = frame.width / 4;

    const start1 = performance.now();
    const resized = resize(frame, {
      scale: {
        width: width,
        height: height,
      },
      pixelFormat: 'rgb',
      dataType: 'uint8',
    });
    const end1 = performance.now();

    const start2 = performance.now();
    const src = cv.frameBufferToMat(height, width, resized);
    const dst = cv.createMat();
    cv.cvtColor(src, dst, 4);
    cv.cvtColor(dst, dst, 40);
    cv.inRange(dst, [37, 120, 120], [60, 255, 255], dst);
    const channels = cv.split(dst);
    const grayChannel = channels[0];

    const rectangles: Rect[] = [];

    if (grayChannel) {
      const contours = cv.findContours(grayChannel, 3, 2);

      for (const contour of contours) {
        const area = cv.contourArea(contour, false);
        if (area > 3000) {
          const rectId = cv.boundingRect(contour);
          rectangles.push(cv.getRect(rectId));
        }
      }
    }
    cv.clearBuffers(); // REMEMBER TO CLEAN
    const end2 = performance.now();
    const diff1 = (end1 - start1).toFixed(2);
    const diff2 = (end2 - start2).toFixed(2);
    console.log(
      `Resize and conversion took ${diff1}ms! OpenCV things took ${diff2}ms!`
    );
    frame.render();

    for (const rectangle of rectangles) {
      frame.drawRect(
        {
          height: rectangle.height * 4,
          width: rectangle.width * 4,
          x: rectangle.x * 4,
          y: rectangle.y * 4,
        },
        paint
      );
    }
  }, []);

  if (!hasPermission) {
    return <Text>No permission</Text>;
  }
  if (device == null) {
    return <Text>No device</Text>;
  }
  return (
    <Camera
      style={StyleSheet.absoluteFill}
      device={device}
      isActive={true}
      frameProcessor={frameProcessor}
    />
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
