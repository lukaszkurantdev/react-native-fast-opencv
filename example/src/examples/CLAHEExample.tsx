import { useState } from 'react';
import {
  Button,
  Image,
  ScrollView,
  StyleSheet,
  Text,
  View,
} from 'react-native';
import {
  ColorConversionCodes,
  DataTypes,
  Mat,
  OpenCV,
  Size,
} from 'react-native-fast-opencv';
import { launchImageLibrary, type Asset } from 'react-native-image-picker';
import { useRunOnJS, useWorklet } from 'react-native-worklets-core';

export function CLAHEExample() {
  const [photo, setPhoto] = useState<Asset | null>(null);
  const [result, setResult] = useState<{
    original: string;
    processed: string;
  } | null>(null);

  const getImageFromGallery = async () => {
    const selection = await launchImageLibrary({
      mediaType: 'photo',
      includeBase64: true,
    });
    const selected = selection.assets?.at(0);

    if (selected?.base64) {
      setPhoto(selected);
      setResult(null);
    }
  };

  const setImages = useRunOnJS((original: string, processed: string) => {
    setResult({ original, processed });
  }, []);

  const worklet = useWorklet('default', () => {
    'worklet';
    if (!photo?.base64) return;

    const src = Mat.createFromBase64(photo.base64);
    const gray = Mat.create(0, 0, DataTypes.CV_8UC1);
    const dst = Mat.create(0, 0, DataTypes.CV_8UC1);
    const grid = Size.create(8, 8);
    const clahe = OpenCV.createCLAHE(2.0, grid);

    try {
      const { channels } = src.toBuffer('uint8');
      const input = channels === 1 ? src : gray;

      if (channels !== 1) {
        OpenCV.cvtColor(src, gray, ColorConversionCodes.COLOR_BGR2GRAY);
      }

      clahe.apply(input, dst);
      setImages(input.toBase64(), dst.toBase64());
    } finally {
      clahe.release();
      grid.release();
      src.release();
      gray.release();
      dst.release();
    }
  });

  return (
    <View style={styles.container}>
      <Button title="Select photo" onPress={getImageFromGallery} />
      <Button title="Process" onPress={() => worklet()} />

      <ScrollView contentContainerStyle={styles.images}>
        {photo?.uri && !result ? (
          <Image source={{ uri: photo.uri }} style={styles.image} />
        ) : null}

        {result ? (
          <>
            <Text style={styles.heading}>Grayscale</Text>
            <Image
              source={{ uri: 'data:image/jpeg;base64,' + result.original }}
              style={styles.image}
            />
            <Text style={styles.heading}>CLAHE</Text>
            <Image
              source={{ uri: 'data:image/jpeg;base64,' + result.processed }}
              style={styles.image}
            />
          </>
        ) : null}
      </ScrollView>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    backgroundColor: 'white',
    flex: 1,
  },
  images: {
    padding: 16,
    gap: 12,
  },
  heading: {
    fontSize: 16,
    fontWeight: 'bold',
    color: 'black',
  },
  image: {
    width: '100%',
    height: 300,
    resizeMode: 'contain',
  },
});
