import { useState } from 'react';
import { Button, Image, SafeAreaView } from 'react-native';
import {
  DataTypes,
  ObjectType,
  OpenCV,
  BorderTypes,
} from 'react-native-fast-opencv';
import { launchImageLibrary, type Asset } from 'react-native-image-picker';
import { useRunOnJS, useWorklet } from 'react-native-worklets-core';

export function ImageExample() {
  const [photo, setPhoto] = useState<Asset | null>(null);
  const [result, setResult] = useState<string>('');

  const getImageFromGallery = async () => {
    const result = await launchImageLibrary({
      mediaType: 'photo',
      includeBase64: true,
    });
    setPhoto(result.assets?.at(0) || null);
  };

  const setImage = useRunOnJS((data: string) => {
    setResult(data);
  }, []);

  const worklet = useWorklet('default', () => {
    'worklet';
    if (photo?.base64) {
      const src = OpenCV.base64ToMat(photo.base64);
      const dst = OpenCV.createObject(ObjectType.Mat, 0, 0, DataTypes.CV_8U);
      const kernel = OpenCV.createObject(ObjectType.Size, 20, 20);
      const point = OpenCV.createObject(ObjectType.Point, 0, 0);

      OpenCV.invoke(
        'blur',
        src,
        dst,
        kernel,
        point,
        BorderTypes.BORDER_DEFAULT
      );
      const dstResult = OpenCV.toJSValue(dst);

      setImage(dstResult.base64);

      OpenCV.clearBuffers(); // IMPORTANT
    }
  });

  return (
    <SafeAreaView style={{ backgroundColor: 'white', flex: 1 }}>
      <Button title="Select photo" onPress={getImageFromGallery} />
      <Button title="Process" onPress={() => worklet()} />

      {result && (
        <Image
          source={{ uri: 'data:image/png;base64,' + result }}
          height={530}
          width={390}
        />
      )}
    </SafeAreaView>
  );
}
