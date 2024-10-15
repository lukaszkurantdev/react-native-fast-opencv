import type {
  AdaptiveThresholdTypes,
  DistanceTransformMasks,
  DistanceTypes,
  FloodFillFlags,
  ThresholdTypes,
} from '../../constants/ImageProcessing';
import type { Mat, Point, Rect, Scalar } from '../../objects/Objects';

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

  /** @Fills a connected component with the given color.
   * The function cv::floodFill fills a connected component starting from the seed point with the specified color. The connectivity is determined by the color/brightness closeness of the neighbor pixels.
   * Use these functions to either mark a connected component with the specified color in-place, or build a mask and then extract the contour, or copy the region to another image, and so on.
   * @param name Function name.
   * @param image Input/output 1- or 3-channel, 8-bit, or floating-point image. It is modified by the function unless the #FLOODFILL_MASK_ONLY flag is set in the second variant of the function. See the details below.
   * @param mask Operation mask that should be a single-channel 8-bit image, 2 pixels wider and 2 pixels taller than image. Since this is both an input and output parameter, you must take responsibility of initializing it. Flood-filling cannot go across non-zero pixels in the input mask. For example, an edge detector output can be used as a mask to stop filling at edges. On output, pixels in the mask corresponding to filled pixels in the image are set to 1 or to the a value specified in flags as described below. Additionally, the function fills the border of the mask with ones to simplify internal processing. It is therefore possible to use the same mask in multiple calls to the function to make sure the filled areas do not overlap.
   * @param seedPoint Starting point.
   * @param newVal New value of the repainted domain pixels.
   * @param rect Optional output parameter set by the function to the minimum bounding rectangle of the repainted domain.
   * @param loDiff Maximal lower brightness/color difference between the currently observed pixel and one of its neighbors belonging to the component, or a seed pixel being added to the component.
   * @param upDiff Maximal upper brightness/color difference between the currently observed pixel and one of its neighbors belonging to the component, or a seed pixel being added to the component.
   * @param flags Operation flags. The first 8 bits contain a connectivity value. The default value of 4 means that only the four nearest neighbor pixels (those that share an edge) are considered. A connectivity value of 8 means that the eight nearest neighbor pixels (those that share a corner) will be considered. The next 8 bits (8-16) contain a value between 1 and 255 with which to fill the mask (the default value is 1). For example, 4 | ( 255 \<\< 8 ) will consider 4 nearest neighbours and fill the mask with a value of 255. The following additional options occupy higher bits and therefore may be further combined with the connectivity and mask fill values using bit-wise or (|), see #FloodFillFlags.
   **/
  invoke(
    name: 'floodFill',
    image: Mat,
    mask: Mat,
    seedPoint: Point,
    newVal: Scalar,
    rect: Rect,
    loDiff: Scalar,
    upDiff: Scalar,
    flags: FloodFillFlags | number
  ): { value: number };

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
