# Blur image on separated thread

In this example, it will show a way to blur a photo from a photo gallery using another thread and the WorkletsCore library.



### Requirements

- We must have the react-native-fast-opencv and react-native-worklets-core libraries installed.
- We have a way to handle image from gallery and get it in Base64 format. For this purpose, I used the [react-native-image-picker](https://github.com/react-native-image-picker/react-native-image-picker) library.

### Code

Let's start with a simple code that allows us to select an image from the gallery in Base64 format.

```js
import { useState } from 'react';
import { Button, Image, View, StyleSheet } from 'react-native';
import { launchImageLibrary, type Asset } from 'react-native-image-picker';

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

  return (
    <View style={styles.container}>
      <Button title="Select photo" onPress={getImageFromGallery} />
      <Button title="Process" onPress={() => null} />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    backgroundColor: 'white',
    flex: 1,
  },
});
```

The next step will be to create a function to save the result on the JS thread when the job is done. We use `useRunOnJS` from WorkletsCore, so the value produced on the worklet thread can update our React state.

```js
import { useRunOnJS, useWorklet } from 'react-native-worklets-core';

// ...

const setImage = useRunOnJS((data: string) => {
  setResult(data);
}, []);
```

Now we can define the worklet that runs on a separate thread. Inside it, we create a Mat from the selected Base64 image, prepare a destination Mat, and apply the `blur` function with a chosen kernel size. The blurred result is converted back to Base64 and passed to the JS thread.

```js
import {
  OpenCV,
  DataTypes,
  Mat,
  Size,
  Point,
  BorderTypes,
} from 'react-native-fast-opencv';

// ...

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
```

> Objects created inside the worklet are Host objects and their native memory is reclaimed automatically by the garbage collector, so there is no need to release them manually. See [Memory Management](../usage.md) for details.

Finally, we wire the worklet up to the "Process" button and render the blurred result once it is ready.

```js
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
```

The complete component looks as follows:

```js
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
```
