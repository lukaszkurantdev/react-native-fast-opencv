import { NativeModules, Platform } from 'react-native';
import type { ObjectType } from './objects/ObjectType';
import type {
  Mat,
  MatVector,
  Point,
  PointVector,
  Rect,
  RectVector,
  Size,
  Vec3b,
  Array,
} from './objects/Objects';
import type { DataTypes } from './constants/DataTypes';
import type { ColorConversionCodes } from './constants/ColorConversionsCodes';
import type {
  ContourApproximationModes,
  RetrievalModes,
} from './constants/ImageProcessing';

const LINKING_ERROR =
  `The package 'react-native-fast-opencv' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';

// @ts-expect-error
const isTurboModuleEnabled = global.__turboModuleProxy != null;

const FastOpencvModule = isTurboModuleEnabled
  ? require('./NativeFastOpencv').default
  : NativeModules.FastOpencv;

const FastOpencv = FastOpencvModule
  ? FastOpencvModule
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );

const result = FastOpencvModule.install() as boolean;
if (result !== true) console.error('Failed to install Fast OpenCV bindings!');

declare global {
  // eslint-disable-next-line no-var
  var __loadOpenCV: () => OpenCVModel;
}

export const OpenCV = global.__loadOpenCV();

export interface OpenCVModel {
  clearBuffers(): void;
  frameBufferToMat(rows: number, cols: number, input: Uint8Array): Mat;
  base64ToMat(path: string): Mat;

  // Creation
  createObject(
    type: ObjectType.Mat,
    rows: number,
    cols: number,
    dataType: DataTypes
  ): Mat;
  createObject(type: ObjectType.MatVector): MatVector;
  createObject(type: ObjectType.Point, x: number, y: number): Point;
  createObject(type: ObjectType.PointVector): PointVector;
  createObject(
    type: ObjectType.Rect,
    x: number,
    y: number,
    width: number,
    height: number
  ): Rect;
  createObject(type: ObjectType.RectVector): RectVector;
  createObject(type: ObjectType.Size, width: number, height: number): Size;
  createObject(type: ObjectType.Vec3b, a: number, b: number, c: number): Vec3b;

  toJSValue(mat: Mat): {
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
  toJSValue(vec3b: Vec3b): {
    a: number;
    b: number;
    c: number;
  };

  copyObjectFromVector(vector: MatVector, itemIndex: number): Mat;
  copyObjectFromVector(vector: PointVector, itemIndex: number): Point;
  copyObjectFromVector(vector: RectVector, itemIndex: number): Rect;

  /**
   * Calculates a contour area
   * @param name Function name.
   * @param contour Input vector of 2D points (contour vertices), stored in std::vector or Mat.
   * @param oriented Oriented area flag. If it is true, the function returns a signed area value, depending on the contour orientation (clockwise or counter-clockwise). Using this feature you can determine orientation of a contour by taking the sign of an area. By default, the parameter is false, which means that the absolute value is returned
   * @returns area and the number of non-zero pixels,
   */
  invoke(
    name: 'contourArea',
    contour: PointVector,
    oriented: boolean
  ): { value: number };

  /**
   * Converts an image from one color space to another.
   * @param name Function name.
   * @param src input image: 8-bit unsigned, 16-bit unsigned ( CV_16UC... ), or single-precision floating-point.
   * @param dst output image of the same size and depth as src.
   * @param code color space conversion code.
   */
  invoke(
    name: 'cvtColor',
    src: Mat,
    dst: Mat,
    code: ColorConversionCodes
  ): void;
  /**
   * Converts an image from one color space to another.
   * @param name Function name.
   * @param src input image: 8-bit unsigned, 16-bit unsigned ( CV_16UC... ), or single-precision floating-point.
   * @param dst output image of the same size and depth as src.
   * @param code color space conversion code.
   * @param dstCn number of channels in the destination image; if the parameter is 0, the number of the channels is derived automatically from src and code.
   */
  invoke(
    name: 'cvtColor',
    src: Mat,
    dst: Mat,
    code: ColorConversionCodes,
    dstCd: number
  ): void;

  /**
   * Calculates the up-right bounding rectangle of a point set or non-zero pixels of gray-scale image.
   * @param name Function name.
   * @param array Input gray-scale image or 2D point set, stored in std::vector or Mat.
   * @returns the minimal up-right bounding rectangle for the specified point set or non-zero pixels of gray-scale image
   */
  invoke(name: 'boundingRect', points: PointVector | Mat): Rect;

  /**
   * Finds contours in a binary image
   * @param name Function name.
   * @param image Source, an 8-bit single-channel image. Non-zero pixels are treated as 1's. Zero pixels remain 0's, so the image is treated as binary . You can use compare, inRange, threshold , adaptiveThreshold, Canny, and others to create a binary image out of a grayscale or color one. If mode equals to RETR_CCOMP or RETR_FLOODFILL, the input can also be a 32-bit integer image of labels (CV_32SC1).
   * @param mode Contour retrieval mode, @see RetrievalModes
   * @param method Contour approximation method, @see ContourApproximationModes
   */
  invoke(
    name: 'findContours',
    src: Mat | MatVector,
    mode: RetrievalModes,
    method: ContourApproximationModes
  ): PointVector[];

  /** Checks if array elements lie between the elements of two other arrays. When the lower and/or upper boundary parameters are scalars, the indexes (I) at lowerb and upperb in the above formulas should be omitted.
   * @param name Function name.
   * @param src first input array.
   * @param lowerb inclusive lower boundary array or a scalar.
   * @param upperb inclusive upper boundary array or a scalar.
   * @param dst output array of the same size as src and CV_8U type.
   */
  invoke(
    name: 'inRange',
    src: Mat,
    lowerb: Array,
    upperb: Array,
    dst: Mat
  ): void;

  /**
   * Divides a multi-channel array into several single-channel arrays
   * @param src input multi-channel array
   * @param mv output vector of arrays; the arrays themselves are reallocated, if needed.
   */
  invoke(name: 'split', src: Mat, mv: Mat | MatVector): void;
}

export * from './objects/ObjectType';
export type * from './objects/Objects';
export * from './constants/ColorConversionsCodes';
export * from './constants/DataTypes';
export * from './constants/ImageProcessing';
export * from './utils/file';
