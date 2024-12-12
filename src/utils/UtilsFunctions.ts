import type { Mat } from '../objects/Objects';

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

export type UtilsFunctions = {
  /**
   * Clears any buffers that were allocate to back Mats on the native side.
   */
  clearBuffers(idsToKeep?: string[]): void;
  /**
   * Converts a byte array to a Mat.
   * @param rows - the number of rows in the Mat
   * @param cols - the number of columns in the Mat
   * @param channels - the number of channels in the Mat
   * @param input - the byte array to convert
   */
  frameBufferToMat(
    rows: number,
    cols: number,
    channels: number,
    input: Uint8Array
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
  matToBuffer<T extends keyof BufferType>(
    mat: Mat,
    type: T
  ): {
    cols: number;
    rows: number;
    channels: number;
    buffer: BufferType[T];
  };
};
