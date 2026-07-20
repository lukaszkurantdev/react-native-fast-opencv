import { PaintStyle, Skia } from '@shopify/react-native-skia';
import { useEffect } from 'react';
import { StyleSheet, Text } from 'react-native';
import {
  OpenCV,
  DataTypes,
  Mat,
  ColorConversionCodes,
  RetrievalModes,
  ContourApproximationModes,
  Scalar,
  MatVector,
  Rect,
} from 'react-native-fast-opencv';
import {
  useCameraDevice,
  useCameraPermission,
} from 'react-native-vision-camera';
import { SkiaCamera } from 'react-native-vision-camera-skia';
import { useResizer, type GPUFrame } from 'react-native-vision-camera-resizer';

const paint = Skia.Paint();
paint.setStyle(PaintStyle.Fill);
paint.setColor(Skia.Color('red'));

const RESIZER_WIDTH = 320;
const RESIZER_HEIGHT = 180;

export function CameraRealtimeDetection() {
  const device = useCameraDevice('back');
  const { hasPermission, requestPermission } = useCameraPermission();

  const { resizer } = useResizer({
    width: 320,
    height: 180,
    channelOrder: 'bgr',
    dataType: 'uint8',
    pixelLayout: 'interleaved',
    scaleMode: 'contain',
  });

  useEffect(() => {
    requestPermission();
  }, [requestPermission]);

  if (!hasPermission) {
    return <Text>No permission</Text>;
  }

  if (device == null) {
    return <Text>No device</Text>;
  }

  return (
    <SkiaCamera
      style={styles.container}
      device={device}
      isActive={true}
      orientationSource="interface"
      onFrame={(frame, render) => {
        'worklet';
        const height = frame.height / 4;
        const width = frame.width / 4;

        const scaleToCanvasX = frame.width / RESIZER_HEIGHT;
        const scaleToCanvasY = frame.height / RESIZER_WIDTH;

        const resized = resizer!.resize(frame) as GPUFrame;
        const pixels = new Uint8Array(resized.getPixelBuffer());
        const src = Mat.createFromBuffer('uint8', height, width, 3, pixels);
        const dst = Mat.create(0, 0, DataTypes.CV_8U);

        const lowerBound = Scalar.create(30, 60, 60);
        const upperBound = Scalar.create(50, 255, 255);
        OpenCV.cvtColor(src, dst, ColorConversionCodes.COLOR_BGR2HSV);
        OpenCV.inRange(dst, lowerBound, upperBound, dst);

        const channels = MatVector.create();
        OpenCV.split(dst, channels);
        const grayChannel = channels.get(0);

        const contours = MatVector.create();
        OpenCV.findContours(
          grayChannel,
          contours,
          RetrievalModes.RETR_TREE,
          ContourApproximationModes.CHAIN_APPROX_SIMPLE
        );

        const contoursCount = contours.length;
        const rectangles: Rect[] = [];

        for (let i = 0; i < contoursCount; i++) {
          const contour = contours.get(i);
          const { value: area } = OpenCV.contourArea(contour, false);

          if (area > 3000) {
            const rect = OpenCV.boundingRect(contour);
            rectangles.push(rect);
          }
        }

        render(({ canvas, frameTexture }) => {
          canvas.drawImage(frameTexture, 0, 0);

          for (const rect of rectangles) {
            canvas.drawRect(
              {
                x: (RESIZER_HEIGHT - rect.y - rect.height) * scaleToCanvasX,
                y: rect.x * scaleToCanvasY,
                width: rect.height * scaleToCanvasX,
                height: rect.width * scaleToCanvasY,
              },
              paint
            );
          }
        });

        resized.dispose();
        frame.dispose();
      }}
    />
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
});
