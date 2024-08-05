import { useEffect, useMemo, useState } from 'react';
import { NativeModules, Platform } from 'react-native';

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

type Vector3b = [number, number, number];

export type Rect = {
  x: number;
  y: number;
  width: number;
  height: number;
}

export interface OpenCVModel {
  clearBuffers(): void;
  frameBufferToMat(rows: number, cols: number, input: Uint8Array): string;
  cvtColor(srcMatName: string, dstMatName: string, code: number): boolean;
  inRange(
    srcMatName: string,
    from: Vector3b,
    to: Vector3b,
    dstMatName: string
  ): boolean;
  split(srcMatName: string): string[];
  findContours(srcMatName: string, mode: number, method: number): string[];
  contourArea(srcPointsGroup: string, oriented: boolean): number;
  boundingRect(srcPointsGroup: string): string;
  getRect(srcRect: string): Rect;
  createMat(): string;
}

export function useOpenCV(): OpenCVModel {
  return useMemo(() => global.__loadOpenCV(), []);
}
