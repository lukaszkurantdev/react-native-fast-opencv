import { NativeModules, Platform } from 'react-native';
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
import type { UtilsFunctions } from './utils/UtilsFunctions';
import type { Objects } from './objects/Objects';
import type { ImageTransform } from './functions/ImageProcessing/ImageTransform';

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

if (!isTurboModuleEnabled) {
  const result = FastOpencv.install?.() as boolean;

  if (result !== true) {
    console.error('Failed to install Fast OpenCV bindings!');
  }
}

declare global {
  var __loadOpenCV: () => OpenCVModel;
}

export const OpenCV = global.__loadOpenCV();

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
  Objects &
  UtilsFunctions;

export * from './objects/ObjectType';
export type * from './objects/Objects';
export * from './constants/ColorConversionsCodes';
export * from './constants/DataTypes';
export * from './constants/ImageProcessing';
export * from './constants/ImageTransform';
export * from './constants/Core';
export * from './constants/FeatureMatching';
export type * from './functions/ImageProcessing/FeatureMatching';
