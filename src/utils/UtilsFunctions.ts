import type { Mat } from '../objects/Objects';

export type UtilsFunctions = {
  clearBuffers(): void;
  frameBufferToMat(rows: number, cols: number, input: Uint8Array): Mat;
  base64ToMat(data: string): Mat;
  matToBuffer(
    mat: Mat,
    type: 'uint8'
  ): { cols: number; rows: number; channels: number; buffer: Uint8Array };
  matToBuffer(
    mat: Mat,
    type: 'float32'
  ): { cols: number; rows: number; channels: number; buffer: Float32Array };
};
