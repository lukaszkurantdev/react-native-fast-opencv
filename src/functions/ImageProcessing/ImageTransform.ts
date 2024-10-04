import type { BorderTypes, DecompTypes } from '../../constants/Core';
import type { InterpolationFlags } from '../../constants/ImageTransform';
import type { Mat, PointVector, Scalar, Size } from '../../objects/Objects';

export type ImageTransform = {
  /**
   * Calculates a perspective transform from four pairs of the corresponding points.
   * @param name Function name.
   * @param src Coordinates of quadrangle vertices in the source image.
   * @param dst Coordinates of the corresponding quadrangle vertices in the destination image.
   * @param solveMethod method passed to cv::solve (DecompTypes)
   */
  invoke(
    name: 'getPerspectiveTransform',
    src: PointVector,
    dst: PointVector,
    solveMethod: DecompTypes
  ): Mat;

  /**
   * Applies a perspective transformation to an image.
   * @param name Function name.
   * @param src input image.
   * @param dst output image that has the size dsize and the same type as src .
   * @param M 3x3 transformation matrix
   * @param size size of the output image
   * @param flags combination of interpolation methods (INTER_LINEAR or INTER_NEAREST) and the optional flag WARP_INVERSE_MAP, that sets M as the inverse transformation
   * @param borderMode pixel extrapolation method (BORDER_CONSTANT or BORDER_REPLICATE).
   * @param borderValue value used in case of a constant border; by default, it equals 0.
   */
  invoke(
    name: 'warpPerspective',
    src: Mat,
    dst: Mat,
    M: Mat,
    size: Size,
    flags: InterpolationFlags,
    borderMode: BorderTypes.BORDER_CONSTANT | BorderTypes.BORDER_REPLICATE,
    borderValue: Scalar
  ): void;
};
