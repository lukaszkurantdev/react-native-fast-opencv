import { useState } from 'react';
import { Button, Image, SafeAreaView, Text } from 'react-native';
import {
  ColorConversionCodes,
  ContourApproximationModes,
  DataTypes,
  ObjectType,
  OpenCV,
  RetrievalModes,
  type Rect,
} from 'react-native-fast-opencv';
import { launchImageLibrary, type Asset } from 'react-native-image-picker';
import { useRunOnJS, useWorklet, Worklets } from 'react-native-worklets-core';

export function ImageExample() {
  const [photo, setPhoto] = useState<Asset | null>(null);
  const [b64, setB64] = useState<string>('');

  const test = async () => {
    const result = await launchImageLibrary({
      mediaType: 'photo',
      includeBase64: true,
    });
    setPhoto(result.assets?.at(0) || null);
  };

  const process = async () => {
    if (photo && photo.base64 && photo.width && photo.height) {
      const src = OpenCV.base64ToMat(photo.base64);
      const dst = OpenCV.createObject(ObjectType.Mat, 0, 0, DataTypes.CV_8U);

      await OpenCV.invokeAsync(
        'cvtColor',
        src,
        dst,
        ColorConversionCodes.COLOR_BGR2HSV
      );

      const lowerBound = OpenCV.createObject(ObjectType.Scalar, 40, 40, 40);
      const upperBound = OpenCV.createObject(ObjectType.Scalar, 100, 255, 255);

      await OpenCV.invokeAsync('inRange', dst, lowerBound, upperBound, dst);

      // const channels = OpenCV.createObject(ObjectType.MatVector);
      // OpenCV.invoke('split', dst, channels);
      // const grayChannel = OpenCV.copyObjectFromVector(channels, 0);

      // const contours = OpenCV.createObject(ObjectType.MatVector);

      // OpenCV.invoke(
      //   'findContours',
      //   grayChannel,
      //   contours,
      //   RetrievalModes.RETR_TREE,
      //   ContourApproximationModes.CHAIN_APPROX_SIMPLE
      // );

      // const contoursMats = OpenCV.toJSValue(contours);

      // const rectangles: Rect[] = [];

      // for (let i = 0; i < contoursMats.array.length; i++) {
      //   const contour = OpenCV.copyObjectFromVector(contours, i);
      //   const { value: area } = OpenCV.invoke('contourArea', contour, false);

      //   if (area > 3000) {
      //     const rect = OpenCV.invoke('boundingRect', contour);
      //     rectangles.push(rect);
      //   }
      // }

      // console.log(rectangles);

      // const result = OpenCV.toJSValue(dst);
      // setB64(result.base64);
      // console.log(array.length);
    }
  };

  const test2 = useRunOnJS((data: string) => {
    setB64(data);
  }, []);

  const worklet = useWorklet(
    'default',
    () => {
      'worklet';
      if (photo && photo.base64 && photo.width && photo.height) {
        const src = OpenCV.base64ToMat(photo.base64);
        const dst = OpenCV.createObject(ObjectType.Mat, 0, 0, DataTypes.CV_8U);

        OpenCV.invoke('cvtColor', src, dst, ColorConversionCodes.COLOR_BGR2HSV);

        const lowerBound = OpenCV.createObject(ObjectType.Scalar, 40, 40, 40);
        const upperBound = OpenCV.createObject(
          ObjectType.Scalar,
          100,
          255,
          255
        );

        OpenCV.invoke('inRange', dst, lowerBound, upperBound, dst);

        const result = OpenCV.toJSValue(dst);

        test2(result.base64);
      }
    },
    []
  );

  return (
    <SafeAreaView style={{ backgroundColor: 'white', flex: 1 }}>
      <Button title="Select photo" onPress={test} />
      <Text>
        URI: {photo?.uri} {photo?.height} {photo?.width}
      </Text>
      <Button title="Process" onPress={() => worklet()} />
      {photo?.base64 && photo?.width && photo?.height && (
        <Image
          source={{ uri: 'data:image/jpg;base64,' + photo.base64 }}
          height={300}
          width={300}
        />
      )}
      {b64 && photo?.width && photo?.height && (
        <Image
          source={{ uri: 'data:image/png;base64,' + b64 }}
          height={300}
          width={300}
        />
      )}
    </SafeAreaView>
  );
}
