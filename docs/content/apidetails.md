# API Details

## Objects

The library provides an object-oriented API that maps to OpenCV structures. Each object has specific properties, methods, and static methods for creation.

### `Mat`

The core multidimensional array used to store images and matrices.

**Properties:**
- `type`: `ObjectType.Mat`
- `rows`: `number` (Read-only)
- `cols`: `number` (Read-only)

**Methods:**
- `release(): void` - Frees the memory allocated for the Mat.
- `toBase64(): string` - Returns a base64 encoded string of the Mat (default format: JPEG).
- `toBuffer(type: 'uint8' | 'uint16' | 'uint32' | 'int8' | 'int16' | 'int32' | 'float32' | 'float64')` - Converts the Mat to a TypedArray, returning `{ cols: number, rows: number, channels: number, buffer: TypedArray }`.
- `saveToFile(path: string): void` - Saves the Mat to the specified local file path.

**Static Methods:**
- `Mat.create(rows?: number, cols?: number, dataType?: DataTypes, data?: number[]): Mat`
- `Mat.createFromBase64(base64: string): Mat`
- `Mat.createFromBuffer(type: string, rows: number, cols: number, channels: number, buffer: TypedArray): Mat`
- `Mat.createFromVisionCameraFrameBuffer(rows: number, cols: number, channels: number, input: Uint8Array): Mat`

---

### `MatVector`

A vector (array) of `Mat` objects.

**Properties:**
- `type`: `ObjectType.MatVector`
- `length`: `number` (Read-only)

**Methods:**
- `release(): void` - Frees the memory allocated for the MatVector.
- `get(index: number): Mat` - Returns the `Mat` at the specified index.
- `push(item: Mat): void` - Adds a `Mat` to the vector.

**Static Methods:**
- `MatVector.create(): MatVector`

---

### `Point`

Represents a 2D point with integer coordinates.

**Properties:**
- `type`: `ObjectType.Point`
- `x`: `number`
- `y`: `number`

**Methods:**
- `release(): void` - Frees the memory allocated for the Point.

**Static Methods:**
- `Point.create(x: number, y: number): Point`

---

### `PointVector`

A vector of `Point` objects.

**Properties:**
- `type`: `ObjectType.PointVector`
- `length`: `number` (Read-only)

**Methods:**
- `release(): void` - Frees the memory allocated for the vector.
- `get(index: number): Point` - Returns the `Point` at the specified index.
- `push(item: Point): void` - Adds a `Point` to the vector.
- `getAll(): Point[]` - Returns a JS array of all points.

**Static Methods:**
- `PointVector.create(): PointVector`

---

### `Point2f`

Represents a 2D point with floating-point coordinates.

**Properties:**
- `type`: `ObjectType.Point2f`
- `x`: `number`
- `y`: `number`

**Methods:**
- `release(): void`

**Static Methods:**
- `Point2f.create(x: number, y: number): Point2f`

---

### `Point2fVector`

A vector of `Point2f` objects.

**Properties:**
- `type`: `ObjectType.Point2fVector`
- `length`: `number` (Read-only)

**Methods:**
- `release(): void`
- `get(index: number): Point2f`
- `push(item: Point2f): void`
- `getAll(): Point2f[]`

**Static Methods:**
- `Point2fVector.create(points?: Point2f[]): Point2fVector`

---

### `PointVectorOfVectors`

A vector of `PointVector` objects. Typically used for holding contours.

**Properties:**
- `type`: `ObjectType.PointVectorOfVectors`
- `length`: `number` (Read-only)

**Methods:**
- `release(): void`
- `get(index: number): PointVector`
- `push(item: PointVector): void`
- `getAll(): PointVector[]`

**Static Methods:**
- `PointVectorOfVectors.create(): PointVectorOfVectors`

---

### `Rect`

Represents a 2D rectangle.

**Properties:**
- `type`: `ObjectType.Rect`
- `x`: `number`
- `y`: `number`
- `width`: `number`
- `height`: `number`

**Methods:**
- `release(): void`

**Static Methods:**
- `Rect.create(x: number, y: number, width: number, height: number): Rect`

---

### `RectVector`

A vector of `Rect` objects.

**Properties:**
- `type`: `ObjectType.RectVector`
- `length`: `number` (Read-only)

**Methods:**
- `release(): void`
- `get(index: number): Rect`
- `push(item: Rect): void`
- `getAll(): Rect[]`

**Static Methods:**
- `RectVector.create(): RectVector`

---

### `Size`

Represents the size of an image or rectangle.

**Properties:**
- `type`: `ObjectType.Size`
- `width`: `number`
- `height`: `number`

**Methods:**
- `release(): void`

**Static Methods:**
- `Size.create(width: number, height: number): Size`

---

### `Vec3b`

Represents a 3-element vector, typically used for storing colors.

**Properties:**
- `type`: `ObjectType.Vec3b`
- `a`: `number`
- `b`: `number`
- `c`: `number`

**Methods:**
- `release(): void`

**Static Methods:**
- `Vec3b.create(): Vec3b`

---

### `Scalar`

Represents a 4-element vector, often used for representing colors (e.g. RGBA).

**Properties:**
- `type`: `ObjectType.Scalar`
- `a`: `number`
- `b`: `number`
- `c`: `number`
- `d`: `number`

**Methods:**
- `release(): void`

**Static Methods:**
- `Scalar.create(a: number, b?: number, c?: number, d?: number): Scalar`

---

### `RotatedRect`

Represents a rotated rectangle.

**Properties:**
- `type`: `ObjectType.RotatedRect`
- `x`: `number`
- `y`: `number`
- `width`: `number`
- `height`: `number`
- `angle`: `number`

**Methods:**
- `release(): void`

**Static Methods:**
- `RotatedRect.create(): RotatedRect`

---

### `TermCriteria`

Defines termination criteria for iterative algorithms.

**Properties:**
- `type`: `ObjectType.TermCriteria`
- `maxCount`: `number`
- `epsilon`: `number`

**Methods:**
- `release(): void`

**Static Methods:**
- `TermCriteria.create(termCriteriaType: TermCriteriaType, maxCount: number, epsilon: number): TermCriteria`

---

### `ORB`

An ORB (Oriented FAST and Rotated BRIEF) feature detector. Created by `OpenCV.ORB_create(...)` and passed to `OpenCV.detectAndCompute`. It is an opaque handle with no readable properties.

**Properties:**
- `type`: `ObjectType.ORB`

**Methods:**
- `release(): void`

> There is no `ORB.create()` static method — use the `OpenCV.ORB_create(...)` function instead.

---

### `BFMatcher`

A brute-force descriptor matcher. Created by `OpenCV.BFMatcher_create(...)` and passed to `OpenCV.matchBF` / `OpenCV.knnMatchBF`. It is an opaque handle with no readable properties.

**Properties:**
- `type`: `ObjectType.BFMatcher`

**Methods:**
- `release(): void`

> There is no `BFMatcher.create()` static method — use the `OpenCV.BFMatcher_create(...)` function instead.

---

### `KeyPointVector`

A vector of keypoints returned by `OpenCV.detectAndCompute`. A keypoint is exposed as plain JS data: `{ x, y, size, angle, response, octave, classId }`.

**Properties:**
- `type`: `ObjectType.KeyPointVector`
- `length`: `number` (Read-only)

**Methods:**
- `release(): void`
- `get(index: number): KeyPoint` - Returns the keypoint at the given index.
- `toArray(): KeyPoint[]` - Returns all keypoints as a plain array.

---

### `DMatchVector`

A vector of descriptor matches returned by `OpenCV.matchBF`. A match is exposed as plain JS data: `{ queryIdx, trainIdx, imgIdx, distance }`.

**Properties:**
- `type`: `ObjectType.DMatchVector`
- `length`: `number` (Read-only)

**Methods:**
- `release(): void`
- `get(index: number): DMatch` - Returns the match at the given index.
- `toArray(): DMatch[]` - Returns all matches as a plain array.

---

### `DMatchVectorVector`

A vector of vectors of descriptor matches returned by `OpenCV.knnMatchBF`. `get(i)` returns the array of the k best matches for the i-th query descriptor.

**Properties:**
- `type`: `ObjectType.DMatchVectorVector`
- `length`: `number` (Read-only)

**Methods:**
- `release(): void`
- `get(index: number): DMatch[]` - Returns the k best matches for the given query index.
- `toArray(): DMatch[][]` - Returns all match groups as a plain nested array.

---

## OpenCV Module

### General Functions

Functions from the OpenCV library are directly attached to the exported `OpenCV` instance. Instead of the previous generic `invoke()` method, you call functions directly with type-safety.

```typescript
import { OpenCV } from 'react-native-fast-opencv';

const src1 = Mat.create();
const src2 = Mat.create();
const dst = Mat.create();

// Direct invocation of OpenCV function
OpenCV.absdiff(src1, src2, dst);

// ...
src1.release();
src2.release();
dst.release();
```

For a full list of available OpenCV functions, refer to the [Available OpenCV Functions](./availablefunctions.md) section.
