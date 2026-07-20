# Migration from 0.4.X

Version **V1** is a major rewrite. Objects are now exposed as JSI **Host objects** with their own classes, OpenCV functions are called **directly** on the `OpenCV` object, and native memory is managed automatically by the **garbage collector**. This removes the manual buffer bookkeeping (`clearBuffers`) that 0.4.X required.

> V1 supports **only the new architecture** and has been tested on **React Native 0.85 and later**. Make sure your app runs the new architecture before upgrading.

## Prerequisites

- React Native **0.85+** with the new architecture enabled.
- Rebuild the native app after upgrading (`pod install` on iOS, clean Android build).
- If you use the **VisionCamera** integration, the examples were updated to VisionCamera 5 with [react-native-vision-camera-skia](https://www.npmjs.com/package/react-native-vision-camera-skia) and [react-native-vision-camera-resizer](https://www.npmjs.com/package/react-native-vision-camera-resizer). Update those peer libraries accordingly.

## Key changes at a glance

| Area | 0.4.X | V1 |
| --- | --- | --- |
| Create object | `OpenCV.createObject(ObjectType.Point, 1, 2)` | `Point.create(1, 2)` |
| Create Mat | `OpenCV.createObject(ObjectType.Mat, 0, 0, DataTypes.CV_8U)` | `Mat.create(0, 0, DataTypes.CV_8U)` |
| Create vector | `OpenCV.createObject(ObjectType.MatVector)` | `MatVector.create()` |
| Call a function | `OpenCV.invoke('cvtColor', src, dst, code)` | `OpenCV.cvtColor(src, dst, code)` |
| Mat from Base64 | `OpenCV.base64ToMat(base64)` | `Mat.createFromBase64(base64)` |
| Mat from camera frame | `OpenCV.frameBufferToMat(h, w, 3, buffer)` | `Mat.createFromVisionCameraFrameBuffer(h, w, 3, buffer)` |
| Mat from raw buffer | – | `Mat.createFromBuffer('uint8', h, w, 3, buffer)` |
| Get item from vector | `OpenCV.copyObjectFromVector(vector, i)` | `vector.get(i)` |
| Vector length | `OpenCV.toJSValue(vector).array.length` | `vector.length` |
| Mat → Base64 | `OpenCV.toJSValue(mat).base64` | `mat.toBase64()` |
| Mat → buffer | `OpenCV.matToBuffer(mat, 'uint8')` | `mat.toBuffer('uint8')` |
| Read object fields | `OpenCV.toJSValue(rect)` → `{ x, y, ... }` | `rect.x`, `rect.y`, `rect.width`, `rect.height` |
| Free memory | `OpenCV.clearBuffers()` (required) | Automatic (GC); `release()` optional |

Functions that return a scalar result keep the same shape — for example `OpenCV.contourArea(contour, false)` still returns `{ value }`.

## Migration process

### 1. Update imports

Object classes are now first-class named exports. Import the ones you use instead of relying solely on `OpenCV` + `ObjectType`.

```js
// 0.4.X
import { OpenCV, ObjectType, DataTypes } from 'react-native-fast-opencv';

// V1
import { OpenCV, Mat, Scalar, MatVector, DataTypes } from 'react-native-fast-opencv';
```

### 2. Replace object creation

Swap every `OpenCV.createObject(ObjectType.X, ...)` for the matching `X.create(...)` static factory.

```js
// 0.4.X
const src = OpenCV.createObject(ObjectType.Mat, 0, 0, DataTypes.CV_8U);
const lower = OpenCV.createObject(ObjectType.Scalar, 30, 60, 60);
const channels = OpenCV.createObject(ObjectType.MatVector);

// V1
const src = Mat.create(0, 0, DataTypes.CV_8U);
const lower = Scalar.create(30, 60, 60);
const channels = MatVector.create();
```

### 3. Replace `invoke` with direct calls

Every `OpenCV.invoke('name', ...args)` becomes `OpenCV.name(...args)`.

```js
// 0.4.X
OpenCV.invoke('cvtColor', src, dst, ColorConversionCodes.COLOR_BGR2HSV);
OpenCV.invoke('inRange', dst, lower, upper, dst);

// V1
OpenCV.cvtColor(src, dst, ColorConversionCodes.COLOR_BGR2HSV);
OpenCV.inRange(dst, lower, upper, dst);
```

### 4. Update Mat creation and data access

```js
// 0.4.X
const mat = OpenCV.base64ToMat(base64);
const { base64: out } = OpenCV.toJSValue(mat);
const { buffer } = OpenCV.matToBuffer(mat, 'uint8');

// V1
const mat = Mat.createFromBase64(base64);
const out = mat.toBase64();
const { buffer } = mat.toBuffer('uint8');
```

### 5. Update vector access and object reads

Use the instance methods/properties directly instead of the `OpenCV` helpers.

```js
// 0.4.X
const count = OpenCV.toJSValue(contours).array.length;
for (let i = 0; i < count; i++) {
  const contour = OpenCV.copyObjectFromVector(contours, i);
  const { value: area } = OpenCV.invoke('contourArea', contour, false);
  const rect = OpenCV.invoke('boundingRect', contour);
  const r = OpenCV.toJSValue(rect); // r.x, r.y, r.width, r.height
}

// V1
const count = contours.length;
for (let i = 0; i < count; i++) {
  const contour = contours.get(i);
  const { value: area } = OpenCV.contourArea(contour, false);
  const rect = OpenCV.boundingRect(contour); // rect.x, rect.y, rect.width, rect.height
}
```

### 6. Remove `clearBuffers` and manual cleanup

This is the biggest behavioural change. In 0.4.X you had to call `OpenCV.clearBuffers()` (typically at the end of every frame) or memory would grow unbounded. In V1 objects are Host objects; when they go out of scope the garbage collector reclaims their native memory, and the size of the native buffers is reported to the runtime as external memory pressure so collections are scheduled in time.

```js
// 0.4.X — required, or memory leaks
OpenCV.clearBuffers();

// V1 — delete it. Memory is managed by the GC.
```

`release()` is still available and **optional** — use it only for very heavy workloads (e.g. many large objects allocated in a tight loop or a high frame-rate frame processor) where you want to free memory eagerly instead of waiting for the GC. See [Memory Management](./usage.md) for details.

## Full example

Before and after of a Vision Camera frame processor body:

```js
// 0.4.X
const src = OpenCV.frameBufferToMat(height, width, 3, resized);
const dst = OpenCV.createObject(ObjectType.Mat, 0, 0, DataTypes.CV_8U);
const lower = OpenCV.createObject(ObjectType.Scalar, 30, 60, 60);
const upper = OpenCV.createObject(ObjectType.Scalar, 50, 255, 255);
OpenCV.invoke('cvtColor', src, dst, ColorConversionCodes.COLOR_BGR2HSV);
OpenCV.invoke('inRange', dst, lower, upper, dst);

const channels = OpenCV.createObject(ObjectType.MatVector);
OpenCV.invoke('split', dst, channels);
const gray = OpenCV.copyObjectFromVector(channels, 0);

OpenCV.clearBuffers(); // REQUIRED
```

```js
// V1
const src = Mat.createFromVisionCameraFrameBuffer(height, width, 3, resized);
const dst = Mat.create(0, 0, DataTypes.CV_8U);
const lower = Scalar.create(30, 60, 60);
const upper = Scalar.create(50, 255, 255);
OpenCV.cvtColor(src, dst, ColorConversionCodes.COLOR_BGR2HSV);
OpenCV.inRange(dst, lower, upper, dst);

const channels = MatVector.create();
OpenCV.split(dst, channels);
const gray = channels.get(0);

// no clearBuffers — the GC handles it
```
