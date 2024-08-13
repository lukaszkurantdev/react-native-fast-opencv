import type { Mat } from '../objects/Objects';

export type UtilsFunctions = {
  clearBuffers(): void;
  frameBufferToMat(rows: number, cols: number, input: Uint8Array): Mat;
  base64ToMat(data: string): Mat;
};
