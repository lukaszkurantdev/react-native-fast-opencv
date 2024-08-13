export enum ColormapTypes {
  COLORMAP_AUTUMN = 0,
  COLORMAP_BONE = 1,
  COLORMAP_JET = 2,
  COLORMAP_WINTER = 3,
  COLORMAP_RAINBOW = 4,
  COLORMAP_OCEAN = 5,
  COLORMAP_SUMMER = 6,
  COLORMAP_SPRING = 7,
  COLORMAP_COOL = 8,
  COLORMAP_HSV = 9,
  COLORMAP_PINK = 10,
  COLORMAP_HOT = 11,
  COLORMAP_PARULA = 12,
  COLORMAP_MAGMA = 13,
  COLORMAP_INFERNO = 14,
  COLORMAP_PLASMA = 15,
  COLORMAP_VIRIDIS = 16,
  COLORMAP_CIVIDIS = 17,
  COLORMAP_TWILIGHT = 18,
  COLORMAP_TWILIGHT_SHIFTED = 19,
  COLORMAP_TURBO = 20,
  COLORMAP_DEEPGREEN = 21,
}

export enum HersheyFonts {
  FONT_HERSHEY_SIMPLEX = 0,
  FONT_HERSHEY_PLAIN = 1,
  FONT_HERSHEY_DUPLEX = 2,
  FONT_HERSHEY_COMPLEX = 3,
  FONT_HERSHEY_TRIPLEX = 4,
  FONT_HERSHEY_COMPLEX_SMALL = 5,
  FONT_HERSHEY_SCRIPT_SIMPLEX = 6,
  FONT_HERSHEY_SCRIPT_COMPLEX = 7,
  FONT_ITALIC = 16,
}

export enum LineTypes {
  FILLED = -1,
  LINE_4 = 4,
  LINE_8 = 8,
  LINE_AA = 16,
}

export enum MarkerTypes {
  MARKER_CROSS = 0,
  MARKER_TILTED_CROSS = 1,
  MARKER_STAR = 2,
  MARKER_DIAMOND = 3,
  MARKER_SQUARE = 4,
  MARKER_TRIANGLE_UP = 5,
  MARKER_TRIANGLE_DOWN = 6,
}

export enum HoughModes {
  HOUGH_STANDARD = 0,
  HOUGH_PROBABILISTIC = 1,
  HOUGH_MULTI_SCALE = 2,
  HOUGH_GRADIENT = 3,
  HOUGH_GRADIENT_ALT = 4,
}

export enum LineSegmentDetectorModes {
  LSD_REFINE_NONE = 0,
  LSD_REFINE_STD = 1,
  LSD_REFINE_ADV = 2,
}

export enum MorphShapes {
  MORPH_RECT = 'MORPH_RECT',
  MORPH_CROSS = 'MORPH_CROSS',
  MORPH_ELLIPSE = 'MORPH_ELLIPSE',
}

export enum MorphTypes {
  MORPH_ERODE = 0,
  MORPH_DILATE = 1,
  MORPH_OPEN = 2,
  MORPH_CLOSE = 3,
  MORPH_GRADIENT = 4,
  MORPH_TOPHAT = 5,
  MORPH_BLACKHAT = 6,
  MORPH_HITMISS = 7,
}

export enum SpecialFilter {
  FILTER_SCHARR = 'FILTER_SCHARR',
}

export enum AdaptiveThresholdTypes {
  ADAPTIVE_THRESH_MEAN_C = 0,
  ADAPTIVE_THRESH_GAUSSIAN_C = 1,
}

export enum DistanceTransformLabelTypes {
  DIST_LABEL_CCOMP = 0,
  DIST_LABEL_PIXEL = 1,
}

export enum DistanceTransformMasks {
  DIST_MASK_3 = 3,
  DIST_MASK_5 = 5,
  DIST_MASK_PRECISE = 0,
}

export enum DistanceTypes {
  DIST_USER = -1,
  DIST_L1 = 1,
  DIST_L2 = 2,
  DIST_C = 3,
  DIST_L12 = 4,
  DIST_FAIR = 5,
  DIST_WELSCH = 6,
  DIST_HUBER = 7,
}

export enum FloodFillFlags {
  FLOODFILL_FIXED_RANGE = 65536,
  FLOODFILL_MASK_ONLY = 131072,
}

export enum GrabCutClasses {
  GC_BGD = 0,
  GC_FGD = 1,
  GC_PR_BGD = 2,
  GC_PR_FGD = 3,
}

export enum GrabCutModes {
  GC_INIT_WITH_RECT = 0,
  GC_INIT_WITH_MASK = 1,
  GC_EVAL = 2,
  GC_EVAL_FREEZE_MODEL = 3,
}

export enum ThresholdTypes {
  THRESH_BINARY = 0,
  THRESH_BINARY_INV = 1,
  THRESH_TRUNC = 2,
  THRESH_TOZERO = 3,
  THRESH_TOZERO_INV = 4,
  THRESH_MASK = 7,
  THRESH_OTSU = 8,
  THRESH_TRIANGLE = 16,
}

export enum TemplateMatchModes {
  TM_SQDIFF = 0,
  TM_SQDIFF_NORMED = 1,
  TM_CCORR = 2,
  TM_CCORR_NORMED = 3,
  TM_CCOEFF = 4,
  TM_CCOEFF_NORMED = 5,
}

export enum ConnectedComponentsAlgorithmsTypes {
  CCL_DEFAULT = -1,
  CCL_WU = 0,
  CCL_GRANA = 1,
  CCL_BOLELLI = 2,
  CCL_SAUF = 3,
  CCL_BBDT = 4,
  CCL_SPAGHETTI = 5,
}

export enum ConnectedComponentsTypes {
  CC_STAT_LEFT = 0,
  CC_STAT_TOP = 1,
  CC_STAT_WIDTH = 2,
  CC_STAT_HEIGHT = 3,
  CC_STAT_AREA = 4,
}

export enum ContourApproximationModes {
  CHAIN_APPROX_NONE = 1,
  CHAIN_APPROX_SIMPLE = 2,
  CHAIN_APPROX_TC89_L1 = 3,
  CHAIN_APPROX_TC89_KCOS = 4,
}

export enum RectanglesIntersectTypes {
  INTERSECT_NONE = 0,
  INTERSECT_PARTIAL = 1,
  INTERSECT_FULL = 2,
}

export enum RetrievalModes {
  RETR_EXTERNAL = 0,
  RETR_LIST = 1,
  RETR_CCOMP = 2,
  RETR_TREE = 3,
  RETR_FLOODFILL = 4,
}

export enum ShapeMatchModes {
  CONTOURS_MATCH_I1 = 1,
  CONTOURS_MATCH_I2 = 2,
  CONTOURS_MATCH_I3 = 3,
}
