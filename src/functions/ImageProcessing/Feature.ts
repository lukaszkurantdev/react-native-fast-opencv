import type { HoughModes } from '../../constants/ImageProcessing';
import type { Mat } from '../../objects/Objects';

export type Feature = {
  /**
   * Finds edges in an image using the Canny algorithm
   * @param name Function name.
   * @param image 8-bit input image.
   * @param edges output edge map; single channels 8-bit image, which has the same size as image
   * @param threshold1 first threshold for the hysteresis procedure
   * @param threshold2 second threshold for the hysteresis procedure
   * @param apertureSize aperture size for the Sobel operator
   */
  invoke(
    name: 'Canny',
    image: Mat,
    edges: Mat,
    threshold1: number,
    threshold2: number
  ): void;

  /**
   * Harris corner detector
   * @param name Function name.
   * @param src Input single-channel 8-bit or floating-point image.
   * @param dst Image to store the Harris detector responses. It has the type CV_32FC1 and the same size as src
   * @param blockSize Neighborhood size
   * @param ksize Aperture parameter for the Sobel operator
   * @param k Harris detector free parameter. See the formula above
   */
  invoke(
    name: 'cornerHarris',
    src: Mat,
    dst: Mat,
    blockSize: number,
    ksize: number,
    k: number
  ): void;

  /**
   * Calculates the minimal eigenvalue of gradient matrices for corner detection
   * @param name Function name.
   * @param src Input single-channel 8-bit or floating-point image
   * @param dst Image to store the minimal eigenvalues. It has the type CV_32FC1 and the same size as src
   * @param blockSize Neighborhood size
   */
  invoke(
    name: 'cornerMinEigenVal',
    src: Mat,
    dst: Mat,
    blockSize: number
  ): void;

  /**
   * Determines strong corners on an image
   * @param name Function name.
   * @param image Input 8-bit or floating-point 32-bit, single-channel image
   * @param corners Output vector of detected corners
   * @param maxCorners Maximum number of corners to return. If there are more corners than are found, the strongest of them is returned. maxCorners <= 0 implies that no limit on the maximum is set and all detected corners are returned
   * @param qualityLevel Parameter characterizing the minimal accepted quality of image corners. The parameter value is multiplied by the best corner quality measure, which is the minimal eigenvalue (see cornerMinEigenVal ) or the Harris function response (see cornerHarris ). The corners with the quality measure less than the product are rejected. For example, if the best corner has the quality measure = 1500, and the qualityLevel=0.01 , then all the corners with the quality measure less than 15 are rejected.
   * @param minDistance Minimum possible Euclidean distance between the returned corners
   */
  invoke(
    name: 'goodFeaturesToTrack',
    image: Mat,
    corners: Mat,
    maxCorners: number,
    qualityLevel: number,
    minDistance: number
  ): void;

  /**
   * Finds circles in a grayscale image using the Hough transform
   * @param name Function name.
   * @param image 8-bit, single-channel, grayscale input image.
   * @param circles Output vector of found circles. Each vector is encoded as 3 or 4 element floating-point vector (x,y,radius) or (x,y,radius,votes)
   * @param method Detection method, see HoughModes. The available methods are HOUGH_GRADIENT and HOUGH_GRADIENT_ALT.
   * @param dp Inverse ratio of the accumulator resolution to the image resolution. For example, if dp=1 , the accumulator has the same resolution as the input image. If dp=2 , the accumulator has half as big width and height. For HOUGH_GRADIENT_ALT the recommended value is dp=1.5, unless some small very circles need to be detected
   * @param minDist Minimum distance between the centers of the detected circles. If the parameter is too small, multiple neighbor circles may be falsely detected in addition to a true one. If it is too large, some circles may be missed
   * this two parameter will be helpful to increase the accuracy of the circle detection
   * this two parameter are also available in opencv original documentation
   * @param param1 it is the higher threshold of the two passed to the Canny edge detector (the lower canny threshold is twice smaller)
   * @param param2 it is the accumulator threshold for the circle centers at the detection stage as discussed above.
   */
  invoke(
    name: 'HoughCircles',
    image: Mat,
    circles: Mat,
    method: HoughModes,
    dp: number,
    minDist: number,
    param1?: number,
    param2?: number
  ): void;

  /**
   * Finds lines in a binary image using the standard Hough transform
   * @param name Function name.
   * @param image 8-bit, single-channel binary source image. The image may be modified by the function.
   * @param lines Output vector of lines. Each line is represented by a 2 or 3 element vector (ρ,θ) or (ρ,θ,votes) . ρ is the distance from the coordinate origin (0,0) (top-left corner of the image). θ is the line rotation angle in radians ( 0∼vertical line,π/2∼horizontal line ). votes is the value of accumulator
   * @param rho Distance resolution of the accumulator in pixels
   * @param theta Angle resolution of the accumulator in radians
   * @param threshold Accumulator threshold parameter. Only those lines are returned that get enough votes ( >𝚝𝚑𝚛𝚎𝚜𝚑𝚘𝚕𝚍 ).
   */
  invoke(
    name: 'HoughLines',
    image: Mat,
    lines: Mat,
    rho: number,
    theta: number,
    threshold: number
  ): void;

  /**
   * Finds line segments in a binary image using the probabilistic Hough transform
   * @param name Function name.
   * @param image 8-bit, single-channel binary source image. The image may be modified by the function.
   * @param lines Output vector of lines. Each line is represented by a 2 or 3 element vector (ρ,θ) or (ρ,θ,votes) . ρ is the distance from the coordinate origin (0,0) (top-left corner of the image). θ is the line rotation angle in radians ( 0∼vertical line,π/2∼horizontal line ). votes is the value of accumulator
   * @param rho Distance resolution of the accumulator in pixels
   * @param theta Angle resolution of the accumulator in radians
   * @param threshold Accumulator threshold parameter. Only those lines are returned that get enough votes ( >𝚝𝚑𝚛𝚎𝚜𝚑𝚘𝚕𝚍 ).
   */
  invoke(
    name: 'HoughLinesP',
    image: Mat,
    lines: Mat,
    rho: number,
    theta: number,
    threshold: number
  ): void;
};
