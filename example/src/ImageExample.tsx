import { useState } from 'react';
import { Button, Image, SafeAreaView, Text } from 'react-native';
import {
  ColorConversionCodes,
  DataTypes,
  ObjectType,
  OpenCV,
} from 'react-native-fast-opencv';
import { launchImageLibrary, type Asset } from 'react-native-image-picker';

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

      OpenCV.invoke('cvtColor', src, dst, ColorConversionCodes.COLOR_BGR2RGB);
      OpenCV.invoke('cvtColor', dst, dst, ColorConversionCodes.COLOR_BGR2HSV);

      const lowerBound = OpenCV.createObject(ObjectType.Vec3b, 0, 120, 120);
      const upperBound = OpenCV.createObject(ObjectType.Vec3b, 255, 255, 255);

      // OpenCV.invoke('inRange', dst, lowerBound, upperBound, dst);

      const result = OpenCV.toJSValue(dst);
      setB64(result.base64);
      // console.log(array.length);
    }
  };

  return (
    <SafeAreaView style={{ backgroundColor: 'white', flex: 1 }}>
      <Button title="Select photo" onPress={test} />
      <Text>
        URI: {photo?.uri} {photo?.height} {photo?.width}
      </Text>
      <Button title="Process" onPress={process} />
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
