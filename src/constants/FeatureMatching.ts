/**
 * ORB score type, used for the `scoreType` parameter of `ORB_create`.
 *
 * HARRIS_SCORE ranks features using the Harris measure (better quality),
 * FAST_SCORE uses the FAST measure (slightly faster, slightly less stable).
 */
export enum ORBScoreType {
  HARRIS_SCORE = 0,
  FAST_SCORE = 1,
}
