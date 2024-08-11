import type { BorderTypes, CovarFlags, NormTypes } from '../constants/Core';
import type { DataTypes } from '../constants/DataTypes';
import type { Mat, MatVector } from '../objects/Objects';

export type Core = {
  /**
   * Calculates the per-element absolute difference between two arrays or between an array and a scalar.
   * @param src1 first input array.
   * @param src2 second input array.
   * @param dst output array that has the same size and type as input arrays.
   */
  absdiff(src1: Mat, src2: Mat, dst: Mat): void;

  /**
   *
   * @param src1 first input array.
   * @param src2 second input array.
   * @param dst output array that has the same size and type as input arrays.
   * @param mask optional operation mask - 8-bit single channel array, that specifies elements of the output array to be changed.
   * @param dtype optional depth of the output array.
   */
  add(src1: Mat, src2: Mat, dst: Mat): void;
  add(src1: Mat, src2: Mat, dst: Mat, mask: Mat): void;
  add(src1: Mat, src2: Mat, dst: Mat, mask: Mat, dtype: DataTypes): void;

  /**
   *
   * @param src1 first input array.
   * @param alpha weight of the first array elements.
   * @param src2 second input array of the same size and channel number as src1.
   * @param beta weight of the second array elements.
   * @param gamma scalar added to each sum.
   * @param dst output array that has the same size and number of channels as the input arrays.
   * @param dtype optional depth of the output array; when both input arrays have the same depth, dtype can be set to -1, which will be equivalent to src1.depth().
   */
  addWeighted(
    src1: Mat,
    alpha: number,
    src2: Mat,
    beta: number,
    gamma: number,
    dst: Mat,
    dtype?: DataTypes
  ): void;

  /**
   * naive nearest neighbor finder
   * @todo document when it's updated in opencv documentation
   */
  batchDistance(
    src1: Mat,
    src2: Mat,
    dist: Mat,
    dtype: number | DataTypes,
    nidx: Mat,
    normType: NormTypes,
    K: number,
    mask: Mat,
    update: number,
    crosscheck: boolean
  ): void;

  /**
   * computes bitwise conjunction of the two arrays (dst = src1 & src2) Calculates the per-element bit-wise conjunction of two arrays or an array and a scalar.
   * @param src1 first input array or a scalar.
   * @param src2 second input array or a scalar.
   * @param dst output array that has the same size and type as the input arrays.
   * @param mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.
   */
  bitwise_and(src1: Mat, src2: Mat, dst: Mat, mask?: Mat): void;
  /**
   * Inverts every bit of an array.
   * @param src input array.
   * @param dst output array that has the same size and type as the input array.
   * @param mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.
   */
  bitwise_not(src: Mat, dst: Mat, mask?: Mat): void;
  /**
   * Calculates the per-element bit-wise disjunction of two arrays or an array and a scalar.
   * @param src1 first input array or a scalar.
   * @param src2 second input array or a scalar.
   * @param dst output array that has the same size and type as the input arrays.
   * @param mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.
   */
  bitwise_or(src1: Mat, src2: Mat, dst: Mat, mask?: Mat): void;
  /**
   * Calculates the per-element bit-wise "exclusive or" operation on two arrays or an array and a scalar.
   * @param src1 first input array or a scalar.
   * @param src2 second input array or a scalar.
   * @param dst output array that has the same size and type as the input arrays.
   * @param mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.
   */
  bitwise_xor(src1: Mat, src2: Mat, dst: Mat, mask?: Mat): void;

  /**
   * Computes the source location of an extrapolated pixel.
   * @param p 0-based coordinate of the extrapolated pixel along one of the axes, likely <0 or >= len
   * @param len Length of the array along the corresponding axis.
   * @param borderType Border type, one of the BorderTypes, except for BORDER_TRANSPARENT and BORDER_ISOLATED . When borderType==BORDER_CONSTANT , the function always returns -1, regardless of p and len
   */
  borderInterpolate(p: number, len: number, borderType: BorderTypes): number;

  /**
   * Calculates the covariance matrix of a set of vectors.
   * @param samples samples stored as separate matrices
   * @param nsamples number of samples
   * @param covar output covariance matrix of the type ctype and square size.
   * @param mean input or output (depending on the flags) array as the average value of the input vectors.
   * @param flags operation flags as a combination of CovarFlags
   * @param ctype type of the matrix
   */
  calcCovarMatrix(
    samples: MatVector,
    nsamples: number,
    covar: Mat,
    mean: Mat,
    flags: CovarFlags,
    ctype: DataTypes
  ): void;
};
