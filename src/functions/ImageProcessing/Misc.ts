import type {
  AdaptiveThresholdTypes,
  DistanceTransformMasks,
  DistanceTypes,
  ThresholdTypes,
} from '../../constants/ImageProcessing';
import type { Mat } from '../../objects/Objects';

export type Misc = {
  /**
   * Applies an adaptive threshold to an array
   * @param name Function name.
   * @param src Source 8-bit single-channel image.
   * @param dst Destination image of the same size and the same type as src
   * @param maxValue Non-zero value assigned to the pixels for which the condition is satisfied
   * @param adaptiveMethod Adaptive thresholding algorithm to use, @see AdaptiveThresholdTypes. The BORDER_REPLICATE | BORDER_ISOLATED is used to process boundaries
   * @param thresholdType Thresholding type that must be either THRESH_BINARY or THRESH_BINARY_INV, @see ThresholdTypes.
   * @param blockSize Size of a pixel neighborhood that is used to calculate a threshold value for the pixel: 3, 5, 7, and so on.
   * @param C Constant subtracted from the mean or weighted mean (@see the details below). Normally, it is positive but may be zero or negative as well)
   */
  invoke(
    name: 'adaptiveThreshold',
    src: Mat,
    dst: Mat,
    maxValue: number,
    adaptiveMethod: AdaptiveThresholdTypes,
    thresholdType:
      | ThresholdTypes.THRESH_BINARY
      | ThresholdTypes.THRESH_BINARY_INV,
    blockSize: number,
    C: number
  ): void;

  /**
   * Calculates the distance to the closest zero pixel for each pixel of the source image
   * @param name Function name.
   * @param src 	8-bit, single-channel (binary) source image
   * @param dst Output image with calculated distances. It is a 8-bit or 32-bit floating-point, single-channel image of the same size as src
   * @param distanceType Type of distance, @see DistanceTypes
   * @param maskSize Size of the distance transform mask, @see DistanceTransformMasks. In case of the DIST_L1 or DIST_C distance type, the parameter is forced to 3 because a 3×3 mask gives the same result as 5×5 or any larger aperture.
   */
  invoke(
    name: 'distanceTransform',
    src: Mat,
    dst: Mat,
    distanceType: DistanceTypes,
    maskSize: DistanceTransformMasks
  ): void;

  /**
   * Calculates the integral of an image
   * @param name Function name.
   * @param src input image as W×H, 8-bit or floating-point (32f or 64f).
   * @param sum integral image as (W+1)×(H+1) , 32-bit integer or floating-point (32f or 64f).
   */
  invoke(name: 'integral', src: Mat, sum: Mat): void;

  /**
   * Applies a fixed-level threshold to each array element
   * @param name Function name.
   * @param src input array (multiple-channel, 8-bit or 32-bit floating point).
   * @param dst output array of the same size and type and the same number of channels as src.
   * @param thresh threshold value
   * @param maxval maximum value to use with the THRESH_BINARY and THRESH_BINARY_INV thresholding types
   * @param type thresholding type (@see ThresholdTypes).
   */
  invoke(
    name: 'threshold',
    src: Mat,
    dst: Mat,
    thresh: number,
    maxval: number,
    type: number
  ): void;
};
