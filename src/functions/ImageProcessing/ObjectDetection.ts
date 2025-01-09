import type { TemplateMatchModes } from '../../constants/ImageProcessing';
import type { Mat, Point2f } from '../../objects/Objects';

export type ObjectDetection = {
  /**
   * Compares a template against overlapped image regions
   * @param name Function name
   * @param image Image where the search is running. It must be 8-bit or 32-bit floating-point
   * @param templ Searched template. It must be not greater than the source image and have the same data type.
   * @param result Map of comparison results. It must be single-channel 32-bit floating-point. If image is W×H and templ is w×h , then result is (W−w+1)×(H−h+1) .
   * @param method Parameter specifying the comparison method, @see TemplateMatchModes
   * @param mask Mask of searched template. It must have the same datatype and size with templ. It is not set by default. Currently, only the TM_SQDIFF and TM_CCORR_NORMED methods are supported
   */
  invoke(
    name: 'matchTemplate',
    image: Mat,
    templ: Mat,
    result: Mat,
    method: TemplateMatchModes,
    mask: Mat
  ): void;

  /**
   * The function is used to detect translational shifts that occur between two images.
   * The operation takes advantage of the Fourier shift theorem for detecting the translational shift
   * in the frequency domain. It can be used for fast image registration as well as motion estimation.
   *
   * For more information please see http://en.wikipedia.org/wiki/Phase_correlation
   *
   * @param name Function name
   * @param src1 Source floating point array (CV_32FC1 or CV_64FC1)
   * @param src2 Source floating point array (CV_32FC1 or CV_64FC1)
   * @param window Floating point array with windowing coefficients to reduce edge effects (optional).
   */
  invoke(
    name: 'phaseCorrelate',
    src1: Mat,
    src2: Mat,
    window?: Mat
  ): { phaseShift: Point2f; response: number };
};
