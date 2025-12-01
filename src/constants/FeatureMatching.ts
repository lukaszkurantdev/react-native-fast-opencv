/**
 * ORB Score Type
 * Used in ORB_create scoreType parameter
 */
export enum ORBScoreType {
  HARRIS_SCORE = 0,
  FAST_SCORE = 1,
}

/**
 * Norm types for BFMatcher
 */
export enum NormTypes {
  NORM_INF = 1,
  NORM_L1 = 2,
  NORM_L2 = 4,
  NORM_L2SQR = 5,
  NORM_HAMMING = 6,
  NORM_HAMMING2 = 7,
  NORM_TYPE_MASK = 7,
  NORM_RELATIVE = 8,
  NORM_MINMAX = 32,
}

/**
 * Method for computing homography
 */
export enum HomographyMethod {
  DEFAULT = 0,
  LMEDS = 4,
  RANSAC = 8,
  RHO = 16,
}
