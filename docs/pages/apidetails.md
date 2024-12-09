# API

## Objects

### Create Object
The function creates a new object of the selected type and stores it in memory. The returned object contains the object identifier and type.

```js
createObject(
  type: ObjectType.Mat,
  rows: number,
  cols: number,
  dataType: DataTypes,
  data?: number[]
): Mat;
createObject(type: ObjectType.MatVector): MatVector;
createObject(type: ObjectType.Point, x: number, y: number): Point;
createObject(type: ObjectType.PointVector): PointVector;
createObject(type: ObjectType.PointVectorOfVectors): PointVectorOfVectors;
createObject(
  type: ObjectType.Rect,
  x: number,
  y: number,
  width: number,
  height: number
): Rect;
createObject(type: ObjectType.RectVector): RectVector;
createObject(type: ObjectType.Size, width: number, height: number): Size;
createObject(type: ObjectType.Scalar, a: number): Scalar;
createObject(
  type: ObjectType.Scalar,
  a: number,
  b: number,
  c: number
): Scalar;
createObject(
  type: ObjectType.Scalar,
  a: number,
  b: number,
  c: number,
  d: number
): Scalar;
```

---

### Copy Object from Vector
Copies an object from a vector to a separate object.

```js
copyObjectFromVector(vector: MatVector, itemIndex: number): Mat;
copyObjectFromVector(vector: PointVector, itemIndex: number): Point;
copyObjectFromVector(
  vector: PointVectorOfVectors,
  itemIndex: number
): PointVector;
copyObjectFromVector(vector: RectVector, itemIndex: number): Rect;
```

---

### To JS Value
Converts an object to a JS-readable object.

```js
toJSValue(
    mat: Mat,
    outImageFormat?: 'jpeg' | 'png'
): {
  size: number;
  cols: number;
  rows: number;
  base64: string;
};
toJSValue(matVector: MatVector): {
  array: { size: number; cols: number; rows: number }[];
};
toJSValue(point: Point): {
  x: number;
  y: number;
};
toJSValue(pointVector: PointVector): {
  array: {
    x: number;
    y: number;
  }[];
};
toJSValue(pointVector: PointVectorOfVectors): {
  array: {
    x: number;
    y: number;
  }[][];
};
toJSValue(rect: Rect): {
  x: number;
  y: number;
  width: number;
  height: number;
};
toJSValue(rectVector: RectVector): {
  array: {
    x: number;
    y: number;
    width: number;
    height: number;
  }[];
};
toJSValue(size: Size): {
  width: number;
  height: number;
};
toJSValue(scalar: Scalar): {
  a: number;
  b?: number;
  c?: number;
  d?: number;
};
```

## Utils

### Clear Buffers
Clears stored objects from memory.

```js
clearBuffers(): void;
```

### Frame Buffer to Mat
Creates an object of type Mat based on an array of Uint8Array.

```js
frameBufferToMat(rows: number, cols: number, channels: number, input: Uint8Array): Mat;
```

### Base64 to Mat
Creates an object of type Mat based on image in Base64.

```js
base64ToMat(data: string): Mat;
```

### Mat to Buffer
Convert Mat object to Uint8Array or Float32Array based on value of parameter and returns with number of cols, rows and channels.

```ts
matToBuffer<T extends keyof BufferType>(
  mat: Mat,
  type: T
): { cols: number; rows: number; channels: number; buffer: BufferType[T] };
```

where `BufferType` is:

```ts
type BufferType = {
  uint8: Uint8Array;
  uint16: Uint16Array;
  uint32: Uint32Array;
  int8: Int8Array;
  int16: Int16Array;
  int32: Int32Array;
  float32: Float32Array;
  float64: Float64Array;
};
```

## Functions

### Invoke function

Performs a function with specified parameters. A full list of functions with parameters is available [here](./availablefunctions.md).

#### Example

```js
invoke(name: 'absdiff', src1: Mat, src2: Mat, dst: Mat): void;
```