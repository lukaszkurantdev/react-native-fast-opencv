import { useState } from 'react';
import { Button, Image, View, StyleSheet } from 'react-native';
import {
  OpenCV,
  DataTypes,
  Mat,
  Size,
  Point,
  BorderTypes,
} from 'react-native-fast-opencv';
import { launchImageLibrary, type Asset } from 'react-native-image-picker';
import { useRunOnJS, useWorklet } from 'react-native-worklets-core';

export function ImageExample() {
  const [photo, setPhoto] = useState<Asset | null>(null);
  const [result, setResult] = useState<string>('');

  const getImageFromGallery = async () => {
    const rawResult = await launchImageLibrary({
      mediaType: 'photo',
      includeBase64: true,
    });
    setPhoto(rawResult.assets?.at(0) || null);
  };

  const setImage = useRunOnJS((data: string) => {
    setResult(data);
  }, []);

  const worklet = useWorklet('default', () => {
    'worklet';
    if (photo?.base64) {
      const src = Mat.createFromBase64(photo.base64);

      const dst = Mat.create(0, 0, DataTypes.CV_8U);

      const kernel = Size.create(20, 20);
      const point = Point.create(0, 0);

      OpenCV.blur(src, dst, kernel, point, BorderTypes.BORDER_DEFAULT);
      const dstResult = dst.toBase64();

      setImage(dstResult);
    }
  });

  return (
    <View style={styles.container}>
      <Button title="Select photo" onPress={getImageFromGallery} />
      <Button title="Process" onPress={() => worklet()} />

      {result && (
        <Image
          source={{ uri: 'data:image/png;base64,' + result }}
          height={530}
          width={390}
        />
      )}
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    backgroundColor: 'white',
    flex: 1,
  },
});
