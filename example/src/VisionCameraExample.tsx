import { PaintStyle, Skia } from '@shopify/react-native-skia';
import { useEffect, useState } from 'react';
import { Button, Image, StyleSheet, Text, View } from 'react-native';
import {
  OpenCV,
  ObjectType,
  type Rect,
  DataTypes,
  ColorConversionCodes,
  RetrievalModes,
  ContourApproximationModes,
} from 'react-native-fast-opencv';
import {
  Camera,
  useCameraDevice,
  useCameraPermission,
  useSkiaFrameProcessor,
} from 'react-native-vision-camera';
import { useSharedValue } from 'react-native-worklets-core';
import { useResizePlugin } from 'vision-camera-resize-plugin';

export function VisionCameraExample() {
  const device = useCameraDevice('back');
  const { resize } = useResizePlugin();

  const [b64, setB64] = useState<string>('');
  const r = useSharedValue<string>('');

  const { hasPermission, requestPermission } = useCameraPermission();

  useEffect(() => {
    requestPermission();
  }, [requestPermission]);

  const paint = Skia.Paint();
  paint.setStyle(PaintStyle.Fill);
  paint.setColor(Skia.Color('lime'));

  const frameProcessor = useSkiaFrameProcessor((frame) => {
    'worklet';

    const height = frame.height / 4;
    const width = frame.width / 4;

    const resized = resize(frame, {
      scale: {
        width: width,
        height: height,
      },
      pixelFormat: 'bgr',
      dataType: 'uint8',
    });
    const rectangles: Rect[] = [];

    const src = OpenCV.frameBufferToMat(height, width, resized);
    const dst = OpenCV.createObject(ObjectType.Mat, 0, 0, DataTypes.CV_8U);

    OpenCV.invoke('cvtColor', src, dst, ColorConversionCodes.COLOR_BGR2HSV);

    const lowerBound = OpenCV.createObject(ObjectType.Scalar, 30, 60, 60);
    const upperBound = OpenCV.createObject(ObjectType.Scalar, 50, 255, 255);
    OpenCV.invoke('inRange', dst, lowerBound, upperBound, dst);

    r.value = OpenCV.toJSValue(dst).base64;

    const channels = OpenCV.createObject(ObjectType.MatVector);
    OpenCV.invoke('split', dst, channels);

    const grayChannel = OpenCV.copyObjectFromVector(channels, 0);
    const contours = OpenCV.createObject(ObjectType.MatVector);

    OpenCV.invoke(
      'findContours',
      grayChannel,
      contours,
      RetrievalModes.RETR_TREE,
      ContourApproximationModes.CHAIN_APPROX_SIMPLE
    );

    const contoursMats = OpenCV.toJSValue(contours);

    for (let i = 0; i < contoursMats.array.length; i++) {
      const contour = OpenCV.copyObjectFromVector(contours, i);
      const { value: area } = OpenCV.invoke('contourArea', contour, false);

      if (area > 3000) {
        const rect = OpenCV.invoke('boundingRect', contour);
        rectangles.push(rect);
      }
    }

    frame.render();

    for (const rect of rectangles) {
      const rectangle = OpenCV.toJSValue(rect);

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

    OpenCV.clearBuffers(); // REMEMBER TO CLEAN
  }, []);

  if (!hasPermission) {
    return <Text>No permission</Text>;
  }
  if (device == null) {
    return <Text>No device</Text>;
  }
  return (
    <>
      <Camera
        style={StyleSheet.absoluteFill}
        device={device}
        isActive={true}
        frameProcessor={frameProcessor}
      />
      <View
        style={{ height: 200, width: 200, top: 100, backgroundColor: 'white' }}
      >
        <Button title="test" onPress={() => setB64(r.value)} />
        {b64 && (
          <Image
            source={{ uri: 'data:image/jpg;base64,' + b64 }}
            height={100}
            width={100}
          />
        )}
      </View>
    </>
  );
}
