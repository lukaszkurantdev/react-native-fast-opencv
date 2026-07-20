import type { NormTypes } from '../../constants/Core';
import type { ORBScoreType } from '../../constants/FeatureMatching';
import type {
  BFMatcher,
  DMatchVector,
  DMatchVectorVector,
  KeyPointVector,
  Mat,
  ORB,
  Point2fVector,
} from '../../objects/Objects';

export type FeatureMatching = {
  /**
   * Creates an ORB (Oriented FAST and Rotated BRIEF) feature detector.
   * All parameters are optional and default to OpenCV's defaults.
   * @param nfeatures The maximum number of features to retain
   * @param scaleFactor Pyramid decimation ratio, greater than 1
   * @param nlevels The number of pyramid levels
   * @param edgeThreshold Size of the border where features are not detected
   * @param firstLevel The level of pyramid to put the source image to
   * @param WTA_K The number of points that produce each element of the oriented BRIEF descriptor
   * @param scoreType HARRIS_SCORE or FAST_SCORE
   * @param patchSize Size of the patch used by the oriented BRIEF descriptor
   * @param fastThreshold The FAST threshold
   */
  ORB_create(
    nfeatures?: number,
    scaleFactor?: number,
    nlevels?: number,
    edgeThreshold?: number,
    firstLevel?: number,
    WTA_K?: number,
    scoreType?: ORBScoreType,
    patchSize?: number,
    fastThreshold?: number
  ): ORB;

  /**
   * Detects keypoints and computes descriptors.
   * @param detector The feature detector (ORB)
   * @param image Input image
   * @param mask Optional mask specifying where to look for keypoints
   * @returns The detected keypoints and the computed descriptors (as a Mat)
   */
  detectAndCompute(
    detector: ORB,
    image: Mat,
    mask?: Mat
  ): { keypoints: KeyPointVector; descriptors: Mat };

  /**
   * Creates a Brute-Force descriptor matcher.
   * @param normType Norm used for distance. Use `NormTypes.NORM_HAMMING` for ORB descriptors
   * @param crossCheck If true, returns only mutually-best pairs (i,j)
   */
  BFMatcher_create(normType?: NormTypes, crossCheck?: boolean): BFMatcher;

  /**
   * Finds the best match for each query descriptor.
   * @param matcher The descriptor matcher (BFMatcher)
   * @param queryDescriptors Query descriptors
   * @param trainDescriptors Train descriptors
   */
  matchBF(
    matcher: BFMatcher,
    queryDescriptors: Mat,
    trainDescriptors: Mat
  ): DMatchVector;

  /**
   * Finds the k best matches for each query descriptor.
   * @param matcher The descriptor matcher (BFMatcher)
   * @param queryDescriptors Query descriptors
   * @param trainDescriptors Train descriptors
   * @param k Count of best matches found per query descriptor
   */
  knnMatchBF(
    matcher: BFMatcher,
    queryDescriptors: Mat,
    trainDescriptors: Mat,
    k: number
  ): DMatchVectorVector;

  /**
   * Computes a perspective transform from exactly 4 matched point pairs.
   *
   * Uses `getPerspectiveTransform` internally because `findHomography`
   * (calib3d) is not available in the iOS OpenCV pod. The caller should
   * pre-filter the matches down to the 4 best point pairs; only the first 4
   * points of each vector are used.
   * @param srcPoints Source points (at least 4)
   * @param dstPoints Destination points (at least 4)
   * @returns The 3x3 perspective transform matrix
   */
  findHomographyFromMatches(
    srcPoints: Point2fVector,
    dstPoints: Point2fVector
  ): Mat;
};
