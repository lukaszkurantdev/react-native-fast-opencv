import { useState } from 'react';
import { Button, Image, SafeAreaView, Text } from 'react-native';
import {
  ColorConversionCodes,
  convertUint8ArrayToBase64,
  DataTypes,
  ObjectType,
  OpenCV,
  readImageAsUint8Array,
} from 'react-native-fast-opencv';
import { launchImageLibrary, type Asset } from 'react-native-image-picker';

export function ImageExample() {
  const [photo, setPhoto] = useState<Asset | null>(null);
  const [base64, setBase64] = useState<string>('');

  const test = async () => {
    const result = await launchImageLibrary({ mediaType: 'photo' });
    console.log(result);
    setPhoto(result.assets?.at(0) || null);
  };

  const process = async () => {
    if (photo && photo.uri && photo.width && photo.height) {
      const array = await readImageAsUint8Array(photo.uri);
      const src = OpenCV.frameBufferToMat(photo.height, photo.width, array);

      const result = OpenCV.toJSValue(src);
      // const base64String = btoa(
      //   String.fromCharCode(...new Uint8Array(result.data))
      // );
      console.log(array.length);
    }
  };

  return (
    <SafeAreaView style={{ backgroundColor: 'white', flex: 1 }}>
      <Button title="Select photo" onPress={test} />
      <Text>
        URI: {photo?.uri} {photo?.height} {photo?.width}
      </Text>
      <Button title="Process" onPress={process} />
      {base64 && photo?.width && photo?.height && (
        <Image
          source={{ uri: 'data:image/png;base64,' + base64 }}
          height={300}
          width={300}
        />
      )}
    </SafeAreaView>
  );
}
