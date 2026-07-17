import type { TermCriteriaType } from '../constants/Core';
import type { DataTypes } from '../constants/DataTypes';
import type { ObjectType } from './ObjectType';

export declare class Mat {
  private constructor();
  type: ObjectType.Mat;
  release(): void;
  rows: number;
  cols: number;
  toBase64(): string;
  toBuffer(type: 'uint8'): {
    cols: number;
    rows: number;
    channels: number;
    buffer: Uint8Array;
  };
  toBuffer(type: 'uint16'): {
    cols: number;
    rows: number;
    channels: number;
    buffer: Uint16Array;
  };
  toBuffer(type: 'uint32'): {
    cols: number;
    rows: number;
    channels: number;
    buffer: Uint32Array;
  };
  toBuffer(type: 'int8'): {
    cols: number;
    rows: number;
    channels: number;
    buffer: Int8Array;
  };
  toBuffer(type: 'int16'): {
    cols: number;
    rows: number;
    channels: number;
    buffer: Int16Array;
  };
  toBuffer(type: 'int32'): {
    cols: number;
    rows: number;
    channels: number;
    buffer: Int32Array;
  };
  toBuffer(type: 'float32'): {
    cols: number;
    rows: number;
    channels: number;
    buffer: Float32Array;
  };
  toBuffer(type: 'float64'): {
    cols: number;
    rows: number;
    channels: number;
    buffer: Float64Array;
  };
  saveToFile(path: string): void;

  static create(
    rows?: number,
    cols?: number,
    dataType?: DataTypes,
    data?: number[]
  ): Mat;
  static createFromBase64(base64: string): Mat;
  static createFromBuffer(
    type: 'uint8' | 'uint16' | 'int8' | 'int16' | 'float32' | 'float64',
    rows: number,
    cols: number,
    channels: 1 | 3 | 4,
    buffer:
      | Uint8Array
      | Uint16Array
      | Int8Array
      | Int16Array
      | Float32Array
      | Float64Array
  ): Mat;
  static createFromVisionCameraFrameBuffer(
    rows: number,
    cols: number,
    channels: number,
    input: Uint8Array
  ): Mat;
}

export declare class MatVector {
  private constructor();
  type: ObjectType.MatVector;
  release(): void;
  get(index: number): Mat;
  push(item: Mat): void;
  length: number;

  static create(): MatVector;
}

export declare class Point {
  private constructor();
  type: ObjectType.Point;
  release(): void;
  x: number;
  y: number;

  static create(x: number, y: number): Point;
}

export declare class PointVector {
  private constructor();
  type: ObjectType.PointVector;
  release(): void;
  get(index: number): Point;
  push(item: Point): void;
  length: number;
  getAll(): Point[];

  static create(): PointVector;
}

export declare class Point2f {
  private constructor();
  type: ObjectType.Point2f;
  release(): void;
  x: number;
  y: number;

  static create(x: number, y: number): Point2f;
}

export declare class Point2fVector {
  private constructor();
  type: ObjectType.Point2fVector;
  release(): void;
  get(index: number): Point2f;
  push(item: Point2f): void;
  length: number;
  getAll(): Point2f[];

  static create(points?: Point2f[]): Point2fVector;
}

export declare class PointVectorOfVectors {
  private constructor();
  type: ObjectType.PointVectorOfVectors;
  release(): void;
  get(index: number): PointVector;
  push(item: PointVector): void;
  length: number;
  getAll(): PointVector[];

  static create(): PointVectorOfVectors;
}

export declare class Rect {
  private constructor();
  type: ObjectType.Rect;
  release(): void;
  x: number;
  y: number;
  width: number;
  height: number;

  static create(x: number, y: number, width: number, height: number): Rect;
}

export declare class RectVector {
  private constructor();
  type: ObjectType.RectVector;
  release(): void;
  get(index: number): Rect;
  push(item: Rect): void;
  length: number;
  getAll(): Rect[];

  static create(): RectVector;
}

export declare class Size {
  private constructor();
  type: ObjectType.Size;
  release(): void;
  width: number;
  height: number;

  static create(width: number, height: number): Size;
}

export declare class Vec3b {
  private constructor();
  type: ObjectType.Vec3b;
  release(): void;
  a: number;
  b: number;
  c: number;

  static create(): Vec3b;
}

export declare class Scalar {
  private constructor();
  type: ObjectType.Scalar;
  release(): void;
  a: number;
  b: number;
  c: number;
  d: number;

  static create(a: number, b?: number, c?: number, d?: number): Scalar;
}

export declare class RotatedRect {
  private constructor();
  type: ObjectType.RotatedRect;
  release(): void;
  x: number;
  y: number;
  width: number;
  height: number;
  angle: number;

  static create(): RotatedRect;
}

export declare class TermCriteria {
  private constructor();
  type: ObjectType.TermCriteria;
  release(): void;
  maxCount: number;
  epsilon: number;

  static create(
    termCriteriaType: TermCriteriaType,
    maxCount: number,
    epsilon: number
  ): TermCriteria;
}

/**
 * A single keypoint detected by a feature detector, as plain JS data.
 */
export interface KeyPoint {
  x: number;
  y: number;
  size: number;
  angle: number;
  response: number;
  octave: number;
  classId: number;
}

/**
 * A single descriptor match, as plain JS data.
 */
export interface DMatch {
  queryIdx: number;
  trainIdx: number;
  imgIdx: number;
  distance: number;
}

/**
 * ORB (Oriented FAST and Rotated BRIEF) feature detector.
 * Created with `OpenCV.ORB_create(...)`; passed to `OpenCV.detectAndCompute`.
 */
export declare class ORB {
  private constructor();
  type: ObjectType.ORB;
  release(): void;
}

/**
 * Brute-force descriptor matcher.
 * Created with `OpenCV.BFMatcher_create(...)`; passed to `matchBF`/`knnMatchBF`.
 */
export declare class BFMatcher {
  private constructor();
  type: ObjectType.BFMatcher;
  release(): void;
}

/**
 * Vector of keypoints returned by `detectAndCompute`.
 */
export declare class KeyPointVector {
  private constructor();
  type: ObjectType.KeyPointVector;
  release(): void;
  get(index: number): KeyPoint;
  toArray(): KeyPoint[];
  length: number;
}

/**
 * Vector of descriptor matches returned by `matchBF`.
 */
export declare class DMatchVector {
  private constructor();
  type: ObjectType.DMatchVector;
  release(): void;
  get(index: number): DMatch;
  toArray(): DMatch[];
  length: number;
}

/**
 * Vector of vectors of descriptor matches returned by `knnMatchBF`.
 * `get(i)` returns the array of k best matches for the i-th query descriptor.
 */
export declare class DMatchVectorVector {
  private constructor();
  type: ObjectType.DMatchVectorVector;
  release(): void;
  get(index: number): DMatch[];
  toArray(): DMatch[][];
  length: number;
}

export type Vector = MatVector | PointVector | RectVector;
export type Array = Mat | Vec3b;

export interface Objects {
  Mat: typeof Mat;
  MatVector: typeof MatVector;
  Point: typeof Point;
  PointVector: typeof PointVector;
  Point2f: typeof Point2f;
  Point2fVector: typeof Point2fVector;
  PointVectorOfVectors: typeof PointVectorOfVectors;
  Rect: typeof Rect;
  RectVector: typeof RectVector;
  Size: typeof Size;
  Vec3b: typeof Vec3b;
  Scalar: typeof Scalar;
  RotatedRect: typeof RotatedRect;
  TermCriteria: typeof TermCriteria;
}
