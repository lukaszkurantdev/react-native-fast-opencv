# Usage

## Objects

The library currently supports the following OpenCV objects: **Mat, MatVector, Point, Point Vector, Point Vector of Vectors, Rect, RectVector, Size, Scalar, TermCriteria and RotatedRect.**

> A vector is simply an array in which individual objects are held.

### Object creation

To create an object, execute the static `.create` function available on its corresponding class.

```js
import { Point } from 'react-native-fast-opencv';

const point = Point.create(1, 2); // x, y
```

A detailed list of properties and methods for each object type is available [here](./apidetails.md).

#### Mat creation from Base64 image

To create a Mat object with image data, you can use a function that creates it from a Base64 image. 

```js
import { Mat } from 'react-native-fast-opencv';

const mat = Mat.createFromBase64(base64string);
```

To convert an image, such as from a gallery, you can use the [react-native-image-picker](https://github.com/react-native-image-picker/react-native-image-picker) library with selected `includeBase64` option.

#### Mat creation from Vision Camera Frame

To process real-time frames from the vision camera library frame processor, you can use the following method:

```js
import { Mat } from 'react-native-fast-opencv';

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

  const mat = Mat.createFromVisionCameraFrameBuffer(height, width, 3, resized);

  // calculations ...

  mat.release(); // optional, but recommended in a frame processor: releasing eagerly avoids memory spikes at high frame rates.
});
```

It is good practice to scale the photo, such as using a frame processor from the [vision-camera-resize-plugin](https://github.com/mrousavy/vision-camera-resize-plugin) library. 

### Get object from vector

In some cases, you will need to pull a specific object from a vector, for example, a Mat object from MatVector. To get to it, use the `get` method:

```js
const object = vector.get(3); // gets the 4th item
```

### Accessing Object Data in JS

Since the data is stored in memory and managed by C++, the API provides helper methods to access the data.

```js
const point = Point.create(10, 20);
console.log(point.x, point.y);

// For Mats:
const mat = Mat.createFromBase64(photo.base64);
const base64Data = mat.toBase64(); // Returns standard string
const buffer = mat.toBuffer('uint8'); // Returns a JS TypedArray

mat.release();
point.release();
```

## Functions

Not all OpenCV features are currently available and ready for use. You can find how the function works on the official [OpenCV](https://opencv.org) website. The naming is consistent - all functions work in the same way as in the C++ version.

### Invocation

Functions are exposed directly on the exported `OpenCV` object. Example:

```js
import { OpenCV, ColorConversionCodes } from 'react-native-fast-opencv';

OpenCV.cvtColor(srcMat, dstMat, ColorConversionCodes.COLOR_BGR2HSV);
```

To check the list of available features, take a look [here](./availablefunctions.md). 

## Calculations from separated thread

Operations on images can be time-consuming, and the library works with synchronous functions, hence it is a good idea to move the execution of the operation to another thread, so as not to block the JavaScript thread. Integration with this library allows tasks to be delegated to another thread.

#### Example

```js
import { useRunOnJS, useWorklet } from 'react-native-worklets-core';
import { Mat, OpenCV } from 'react-native-fast-opencv';

// ...

const [base64, setBase64] = useState<string>('');

const setImage = useRunOnJS((data: string) => {
  setBase64(data);
}, []);

const worklet = useWorklet('default', () => {
  'worklet';
  if (photo) {
    const src = Mat.createFromBase64(photo.base64);
    const dst = Mat.create();
    
    // ... process image into dst
    
    const resultBase64 = dst.toBase64();
    setImage(resultBase64);

    // Objects are Host objects — their native memory is reclaimed
    // automatically by the garbage collector, so releasing is optional.
    // See "Memory Management" below.
  }
});
```

## **Important**: Memory Management

OpenCV objects during execution are held in native memory on the C++ side. Each object is exposed to JavaScript as a Host object, so **memory is managed by the JavaScript garbage collector** — when a Host object goes out of scope and is collected, its underlying native resources are freed automatically. The size of the native buffers is reported to the runtime as external memory pressure, so the GC can schedule collections before memory piles up.

In normal usage you therefore **do not need to release objects manually**. However, you can still free resources eagerly using the `release` function:

```js
mat.release();
```

Calling `release` is **optional and recommended only for very heavy computations** — for example, when you allocate many large objects in a tight loop and cannot wait for the GC to reclaim them. In such cases releasing objects as soon as you no longer need them keeps peak memory usage low:

```js
const mat = Mat.createFromBase64(base64string);
// heavy calculations ...
mat.release(); // optional: free immediately instead of waiting for GC
```