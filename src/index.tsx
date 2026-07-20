import { Platform } from 'react-native';
import type { ColorMap } from './functions/ImageProcessing/ColorMap';
import type { Drawing } from './functions/ImageProcessing/Drawing';
import type { Feature } from './functions/ImageProcessing/Feature';
import type { FeatureMatching } from './functions/ImageProcessing/FeatureMatching';
import type { ImageFiltering } from './functions/ImageProcessing/ImageFiltering';
import type { Misc } from './functions/ImageProcessing/Misc';
import type { ObjectDetection } from './functions/ImageProcessing/ObjectDetection';
import type { Shape } from './functions/ImageProcessing/Shape';
import type { ColorConversion } from './functions/ColorConversion';
import type { Core } from './functions/Core';
import type { Objects } from './objects/Objects';
import type { ImageTransform } from './functions/ImageProcessing/ImageTransform';

const LINKING_ERROR =
  `The package 'react-native-fast-opencv' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';

const FastOpencvModule = require('./NativeFastOpencv').default;

if (!FastOpencvModule) {
  throw new Error(LINKING_ERROR);
}

declare global {
  var __loadOpenCV: () => OpenCVModel;
}

if (globalThis.__loadOpenCV == null) {
  if (typeof FastOpencvModule.install !== 'function') {
    console.error(
      'Native Fast OpenCV Module cannot be found! Make sure you correctly ' +
        'installed native dependencies and rebuilt your app.'
    );
  } else {
    const result = FastOpencvModule.install();

    if (result !== true) {
      console.error(
        'Native OpenCV Module failed to correctly install JSI Bindings!'
      );
    }

    console.log('success');
  }
}

export const OpenCV = globalThis.__loadOpenCV() as OpenCVModel;

export type OpenCVModel = ColorMap &
  Drawing &
  Feature &
  FeatureMatching &
  ImageFiltering &
  ImageTransform &
  Misc &
  ObjectDetection &
  Shape &
  ColorConversion &
  Core &
  Objects;

export * from './objects/ObjectType';
export * from './constants/ColorConversionsCodes';
export * from './constants/DataTypes';
export * from './constants/ImageProcessing';
export * from './constants/ImageTransform';
export * from './constants/Core';
export * from './constants/FeatureMatching';

import type {
  Mat as _Mat,
  MatVector as _MatVector,
  Point as _Point,
  PointVector as _PointVector,
  Point2f as _Point2f,
  Point2fVector as _Point2fVector,
  PointVectorOfVectors as _PointVectorOfVectors,
  Rect as _Rect,
  RectVector as _RectVector,
  Size as _Size,
  Vec3b as _Vec3b,
  Scalar as _Scalar,
  RotatedRect as _RotatedRect,
  TermCriteria as _TermCriteria,
} from './objects/Objects';

export type { Vector, Array } from './objects/Objects';

export type Mat = _Mat;
export const Mat = OpenCV.Mat as unknown as typeof _Mat;
export type MatVector = _MatVector;
export const MatVector = OpenCV.MatVector as unknown as typeof _MatVector;
export type Point = _Point;
export const Point = OpenCV.Point as unknown as typeof _Point;
export type PointVector = _PointVector;
export const PointVector = OpenCV.PointVector as unknown as typeof _PointVector;
export type Point2f = _Point2f;
export const Point2f = OpenCV.Point2f as unknown as typeof _Point2f;
export type Point2fVector = _Point2fVector;
export const Point2fVector =
  OpenCV.Point2fVector as unknown as typeof _Point2fVector;
export type PointVectorOfVectors = _PointVectorOfVectors;
export const PointVectorOfVectors =
  OpenCV.PointVectorOfVectors as unknown as typeof _PointVectorOfVectors;
export type Rect = _Rect;
export const Rect = OpenCV.Rect as unknown as typeof _Rect;
export type RectVector = _RectVector;
export const RectVector = OpenCV.RectVector as unknown as typeof _RectVector;
export type Size = _Size;
export const Size = OpenCV.Size as unknown as typeof _Size;
export type Vec3b = _Vec3b;
export const Vec3b = OpenCV.Vec3b as unknown as typeof _Vec3b;
export type Scalar = _Scalar;
export const Scalar = OpenCV.Scalar as unknown as typeof _Scalar;
export type RotatedRect = _RotatedRect;
export const RotatedRect = OpenCV.RotatedRect as unknown as typeof _RotatedRect;
export type TermCriteria = _TermCriteria;
export const TermCriteria =
  OpenCV.TermCriteria as unknown as typeof _TermCriteria;
export type {
  ORB,
  BFMatcher,
  KeyPoint,
  DMatch,
  KeyPointVector,
  DMatchVector,
  DMatchVectorVector,
} from './objects/Objects';
export type * from './functions/ImageProcessing/FeatureMatching';
