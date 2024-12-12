import type {
  OpticalFlowFlags,
  TemplateMatchModes,
} from '../../constants/ImageProcessing';
import type { Mat, Point2f, Size, TermCriteria } from '../../objects/Objects';

export type ObjectDetection = {
  /**
   * Calculates an optical flow for a sparse feature set using the iterative Lucas-Kanade method with pyramids.
   * @param name Function name
   * @param prevImg First 8-bit input image or pyramid constructed by buildOpticalFlowPyramid.
   * @param nextImg Second input image or pyramid of the same size and the same type as prevImg.
   * @param prevPts Vector of 2D points for which the flow needs to be found; point coordinates must be single-precision floating-point numbers.
   * @param nextPts Output vector of 2D points (with single-precision floating-point coordinates) containing the calculated new positions of input features in the second image; when OPTFLOW_USE_INITIAL_FLOW flag is passed, the vector must have the same size as in the input.
   * @param status Output status vector (of unsigned chars); each element of the vector is set to 1 if the flow for the corresponding features has been found, otherwise, it is set to 0.
   * @param err Output vector of errors; each element of the vector is set to an error for the corresponding feature, type of the error measure can be set in flags parameter; if the flow wasn't found then the error is not defined (use the status parameter to find such cases).
   * @param winSize Size of the search window at each pyramid level.
   * @param maxLevel 0-based maximal pyramid level number; if set to 0, pyramids are not used (single level), if set to 1, two levels are used, and so on; if pyramids are passed to input then algorithm will use as many levels as pyramids have but no more than maxLevel.
   * @param criteria Parameter, specifying the termination criteria of the iterative search algorithm (after the specified maximum number of iterations criteria.maxCount or when the search window moves by less than criteria.epsilon).
   * @param flags Operation flags:
   * * OPTFLOW_USE_INITIAL_FLOW uses initial estimations, stored in nextPts; if the flag is not set, then prevPts is copied to nextPts and is considered the initial estimate.
   * * OPTFLOW_LK_GET_MIN_EIGENVALS use minimum eigen values as an error measure (see minEigThreshold description); if the flag is not set, then L1 distance between patches around the original and a moved point, divided by number of pixels in a window, is used as a error measure.
   * @param minEigThreshold The algorithm calculates the minimum eigen value of a 2x2 normal matrix of optical flow equations (this matrix is called a spatial gradient matrix in [36]), divided by number of pixels in a window; if this value is less than minEigThreshold, then a corresponding feature is filtered out and its flow is not processed, so it allows to remove bad points and get a performance boost.
   */
  invoke(
    name: 'calcOpticalFlowPyrLK',
    prevImg: Mat,
    nextImg: Mat,
    prevPts: Mat,
    nextPts: Mat,
    status: Mat,
    err: Mat,
    winSize?: Size,
    maxLevel?: number,
    criteria?: TermCriteria,
    flags?: OpticalFlowFlags,
    minEigThreshold?: number
  ): void;

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
