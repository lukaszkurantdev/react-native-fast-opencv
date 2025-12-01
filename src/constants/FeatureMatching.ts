/**
 * ORB Score Type
 * Used in ORB_create scoreType parameter
 */
export enum ORBScoreType {
  HARRIS_SCORE = 0,
  FAST_SCORE = 1,
}

/**
 * Method for computing homography
 * Used in findHomography method parameter
 */
export enum HomographyMethod {
  DEFAULT = 0,
  LMEDS = 4,
  RANSAC = 8,
  RHO = 16,
}

// Note: NormTypes (NORM_HAMMING, etc.) are already exported from Core.ts
