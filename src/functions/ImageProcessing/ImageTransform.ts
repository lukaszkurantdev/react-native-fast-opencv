import type { BorderTypes, DecompTypes } from '../../constants/Core';
import type { InterpolationFlags } from '../../constants/ImageTransform';
import type {
  Mat,
  Point2f,
  PointVector,
  Scalar,
  Size,
} from '../../objects/Objects';

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
   * Applies an affine transformation to an image.
   * @param name Function name.
   * @param src input image.
   * @param dst output image that has the size dsize and the same type as src
   * @param M transformation matrix
   * @param dsize size of the output image
   */
  invoke(name: 'warpAffine', src: Mat, dst: Mat, M: Mat, dsize: Size): Mat;

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

  /**
   * Remaps an image to polar or semilog-polar coordinates space.
   * @param name Function name.
   * @param src source image.
   * @param dst destination image. It will have same type as src.
   * @param dsize the destination image size.
   * @param center the transformation center.
   * @param maxRadius the radius of the bounding circle to transform. It determines the inverse magnitude scale parameter too.
   * @param flags a combination of interpolation methods, InterpolationFlags + WarpPolarMode.
   */
  invoke(
    name: 'warpPolar',
    src: Mat,
    dst: Mat,
    dsize: Size,
    center: Point2f,
    maxRadius: number,
    flags: number
  ): void;
};
