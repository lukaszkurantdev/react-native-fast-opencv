import type { Mat } from '../../objects/Objects';

/**
 * ORB feature detector object
 */
export type ORB = { id: string; type: 'orb' };

/**
 * Brute-Force matcher object
 */
export type BFMatcher = { id: string; type: 'bfmatcher' };

/**
 * Vector of keypoints detected by feature detector
 */
export type KeyPointVector = { id: string; type: 'keypoint_vector' };

/**
 * Vector of descriptor matches
 */
export type DMatchVector = { id: string; type: 'dmatch_vector' };

/**
 * Vector of vector of descriptor matches (for knnMatch)
 */
export type DMatchVectorVector = { id: string; type: 'dmatch_vector_vector' };

/**
 * KeyPoint structure as returned by toJSValue
 */
export interface KeyPoint {
  x: number;
  y: number;
  size: number;
  angle: number;
  response: number;
  octave: number;
  classId: number;
}

/**
 * DMatch structure as returned by toJSValue
 */
export interface DMatch {
  queryIdx: number;
  trainIdx: number;
  imgIdx: number;
  distance: number;
}

/**
 * Result from findHomography
 */
export interface FindHomographyResult {
  homography: Mat;
  mask: Mat;
}

/**
 * Result from detectAndCompute
 */
export interface DetectAndComputeResult {
  keypoints: KeyPointVector;
  descriptors: Mat;
}

export type FeatureMatching = {
  /**
   * Creates ORB (Oriented FAST and Rotated BRIEF) feature detector
   * @param name Function name
   * @param nfeatures The maximum number of features to retain
   * @param scaleFactor Pyramid decimation ratio, greater than 1
   * @param nlevels The number of pyramid levels
   * @param edgeThreshold Size of the border where features are not detected
   * @param firstLevel The level of pyramid to put source image to
   * @param WTA_K The number of points that produce each element of the oriented BRIEF descriptor
   * @param scoreType HARRIS_SCORE (0) or FAST_SCORE (1)
   * @param patchSize Size of the patch used by the oriented BRIEF descriptor
   * @param fastThreshold The FAST threshold
   */
  invoke(
    name: 'ORB_create',
    nfeatures?: number,
    scaleFactor?: number,
    nlevels?: number,
    edgeThreshold?: number,
    firstLevel?: number,
    WTA_K?: number,
    scoreType?: number,
    patchSize?: number,
    fastThreshold?: number
  ): ORB;

  /**
   * Detects keypoints and computes descriptors
   * @param name Function name
   * @param detector The feature detector (ORB)
   * @param image Input image
   * @param mask Optional mask specifying where to look for keypoints
   */
  invoke(
    name: 'detectAndCompute',
    detector: ORB,
    image: Mat,
    mask?: Mat
  ): DetectAndComputeResult;

  /**
   * Creates Brute-Force descriptor matcher
   * @param name Function name
   * @param normType NORM_L1=1, NORM_L2=2, NORM_HAMMING=4, NORM_HAMMING2=5. Use NORM_HAMMING for ORB
   * @param crossCheck If true, returns only pairs (i,j) where descriptor i matches j and j matches i
   */
  invoke(
    name: 'BFMatcher_create',
    normType?: number,
    crossCheck?: boolean
  ): BFMatcher;

  /**
   * Finds the best match for each descriptor from a query set
   * @param name Function name
   * @param matcher The descriptor matcher (BFMatcher)
   * @param queryDescriptors Query descriptors
   * @param trainDescriptors Train descriptors
   */
  invoke(
    name: 'matchBF',
    matcher: BFMatcher,
    queryDescriptors: Mat,
    trainDescriptors: Mat
  ): DMatchVector;

  /**
   * Finds k best matches for each descriptor from a query set
   * @param name Function name
   * @param matcher The descriptor matcher (BFMatcher)
   * @param queryDescriptors Query descriptors
   * @param trainDescriptors Train descriptors
   * @param k Count of best matches found per each query descriptor
   */
  invoke(
    name: 'knnMatchBF',
    matcher: BFMatcher,
    queryDescriptors: Mat,
    trainDescriptors: Mat,
    k: number
  ): DMatchVectorVector;

  /**
   * Computes a perspective transformation from 4 matched point pairs
   * Uses getPerspectiveTransform internally (calib3d::findHomography not available)
   * The caller should pre-filter to the 4 best matching points
   * @param name Function name
   * @param srcPoints Source points (Point2fVector with at least 4 points)
   * @param dstPoints Destination points (Point2fVector with at least 4 points)
   */
  invoke(
    name: 'findHomographyFromMatches',
    srcPoints: Mat,
    dstPoints: Mat
  ): Mat;
};
