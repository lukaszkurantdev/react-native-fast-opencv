# Usage

> The library is in the early stages of development and not all functions or objects available in OpenCV are supported. Add an issue if you have any problems or questions.

## **Important**: Cleaning of buffers

OpenCV objects during execution are held in internal memory and managed on the C++ side. Hence, after a calculation has been performed, it is necessary to release unused resources using a function:

```js
OpenCV.clearBuffers();
```

You can do this e.g. after a calculation, or after a specific step. **Remember that not executing this function will result in data being held in memory continuously.**


## Objects

The library currently supports the following OpenCV objects: **Mat, MatVector, Point, Point Vector, Rect, RectVector, Size, Scalar and RotatedRect.**

> A vector is simply an array in which individual objects are held.

### Object creation

To create an object, execute the createObject function, where the first argument will be the type of object (enum ObjectType) and the following parameters specific to a particular type of object.

```js
const point = OpenCV.createObject(ObjectType.Point, 1, 2); // x, y
```

A detailed list of parameters is available [here]().

#### Mat creation from Base64 image

To create a Mat object with image data, you can use a function that creates it from a Base64 image. 

```js
const mat = OpenCV.base64ToMat(base64string);
```

To convert an image, such as from a gallery, you can use the [react-native-image-picker](https://github.com/react-native-image-picker/react-native-image-picker) library with selected `includeBase64` option.

#### Mat creation from Vision Camera Frame

To process real-time frames from the vision camera library frame processor, you can use the following method:

```js
const { resize } = useResizePlugin();

const frameProcessor = useFrameProcessor((frame) => {
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

  const mat = OpenCV.frameBufferToMat(height, width, resized);

  // calculations ...

  OpenCV.clearBuffers(); // IMPORTANT! At the end.
});
```

It is good practice to scale the photo, such as using a frame processor from the [vision-camera-resize-plugin](https://github.com/mrousavy/vision-camera-resize-plugin) library. 


### Expose and copy object from vector

In some cases, you will need to pull a specific object from a vector, for example, a Mat object from MatVector. To get to it, use the function:

```js
const object = OpenCV.copyObjectFromVector(vector, 3); // vector, item index
```

### Object conversion to JavaScript value

Since the data is stored in memory and managed by C++, to get to know the OpenCV object data in the form of a JS object, use the function:

```js
const data = OpenCV.toJSValue(object);
```


## Functions

Not all OpenCV features are currently available and ready for use. You can find how the function works on the official [OpenCV](https://opencv.org) website. The naming is consistent - all functions work in the same way as in the C++ version.

### Invocation
To execute a function from OpenCV call the invoke method, where the first parameter is the name of the function, and the rest are the necessary parameters. Example:

```js
OpenCV.invoke('cvtColor', srcMat, dstMat, ColorConversionCodes.COLOR_BGR2HSV);
```

To check the list of available features, take a look [here](./availablefunctions.md). 



## Calculations from separated thread

Operations on images can be time-consuming, and the library works with synchronous functions, hence it is a good idea to move the execution of the operation to another thread, so as not to block the JavaScript thread. Integration with this library allows tasks to be delegated to another thread.


#### Example

```js
import { useRunOnJS, useWorklet } from 'react-native-worklets-core';

// ...

const [base64, setBase64] = useState<string>('');

const setImage = useRunOnJS((data: string) => {
  setBase64(data);
}, []);

const worklet = useWorklet('default', () => {
  'worklet';
  if (photo) {
    const src = OpenCV.base64ToMat(photo.base64);

    const result = OpenCV.toJSValue(dst);
    setImage(result.base64);

    OpenCV.clearBuffers(); // IMPORTANT
  }
});

```