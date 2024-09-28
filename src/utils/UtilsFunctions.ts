import type { Mat } from '../objects/Objects';

export type UtilsFunctions = {
  /**
   * Clears any buffers that were allocate to back Mats on the native side.
   */
  clearBuffers(): void;
  /**
   * Converts a byte array to a Mat.
   * @param rows - the number of rows in the Mat
   * @param cols - the number of columns in the Mat
   * @param channels - the number of channels in the Mat
   * @param input - the byte array to convert
   */
  frameBufferToMat<T extends 'uint8' | 'float32'>(
    rows: number,
    cols: number,
    channels: number,
    type: T,
    input: T extends 'uint8' ? Uint8Array : Float32Array
  ): Mat;
  /**
   * Converts a base64 string to a Mat.
   * @param data - the base64 string to convert
   */
  base64ToMat(data: string): Mat;
  /**
   * Converts a Mat to a byte array.
   * @param mat - the Mat to convert
   * @param type - the type of the buffer to return ('uint8' or 'float32')
   */
  matToBuffer<T extends 'uint8' | 'float32'>(
    mat: Mat,
    type: T
  ): {
    cols: number;
    rows: number;
    channels: number;
    buffer: T extends 'uint8' ? Uint8Array : Float32Array;
  };
};
