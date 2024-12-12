import type {
  ContourApproximationModes,
  DistanceTypes,
  RetrievalModes,
  ShapeMatchModes,
} from '../../constants/ImageProcessing';
import type {
  Mat,
  MatVector,
  PointVector,
  PointVectorOfVectors,
  Rect,
  RotatedRect,
} from '../../objects/Objects';

export type Shape = {
  /**
   * Approximates a polygonal curve(s) with the specified precision
   * @param curve Input vector of a 2D point stored in std::vector or Mat
   * @param approxCurve Result of the approximation. The type should match the type of the input curve
   * @param epsilonParameter specifying the approximation accuracy. This is the maximum distance between the original curve and its approximation
   * @param closed If true, the approximated curve is closed (its first and last vertices are connected). Otherwise, it is not closed
   */
  invoke(
    name: 'approxPolyDP',
    curve: Mat | MatVector | PointVector,
    approxCurve: Mat | PointVector,
    epsilon: number,
    closed: boolean
  ): void;

  /**
   * Calculates a contour perimeter or a curve length.
   * @param curve Input vector of 2D points, stored in std::vector or Mat.
   * @param closed Flag indicating whether the curve is closed or not.
   * @returns a curve length or a closed contour perimeter.
   */
  invoke(
    name: 'arcLength',
    curve: Mat | MatVector | PointVector,
    closed: boolean
  ): { value: number };

  /**
   * Calculates the up-right bounding rectangle of a point set or non-zero pixels of gray-scale image.
   * @param array Input gray-scale image or 2D point set, stored in std::vector or Mat.
   * @returns the minimal up-right bounding rectangle for the specified point set or non-zero pixels of gray-scale image
   */
  invoke(name: 'boundingRect', array: Mat | MatVector | PointVector): Rect;

  /**
   * computes the connected components labeled image of boolean image
   * @param image the 8-bit single-channel image to be labeled
   * @param labels destination labeled image
   * @returns N, the total number of labels [0, N-1] where 0 represents the background label
   */
  invoke(
    name: 'connectedComponents',
    image: Mat,
    labels: Mat
  ): { value: number };

  /**
   * computes the connected components labeled image of boolean image and also produces a statistics output for each label
   * @param image the 8-bit single-channel image to be labeled
   * @param labels destination labeled image
   * @param stats statistics output for each label, including the background label. Statistics are accessed via stats(label, COLUMN) where COLUMN is one of ConnectedComponentsTypes, selecting the statistic. The data type is CV_32S.
   * @param centroids centroid output for each label, including the background label. Centroids are accessed via centroids(label, 0) for x and centroids(label, 1) for y. The data type CV_64F
   * @returns N, the total number of labels [0, N-1] where 0 represents the background label
   */
  invoke(
    name: 'connectedComponentsWithStats',
    image: Mat,
    labels: Mat,
    stats: Mat,
    centroids: Mat
  ): { value: number };

  /**
   * Calculates a contour area
   * @param contour Input vector of 2D points (contour vertices), stored in std::vector or Mat.
   * @param oriented Oriented area flag. If it is true, the function returns a signed area value, depending on the contour orientation (clockwise or counter-clockwise). Using this feature you can determine orientation of a contour by taking the sign of an area. By default, the parameter is false, which means that the absolute value is returned
   * @returns area and the number of non-zero pixels,
   */
  invoke(
    name: 'contourArea',
    contour: Mat | MatVector | PointVector,
    oriented?: boolean
  ): { value: number };

  /**
   * Finds the convex hull of a point set.
   * @param points Input 2D point set, stored in std::vector or Mat.
   * @param hull Output convex hull. It is either an integer vector of indices or vector of points. In the first case, the hull elements are 0-based indices of the convex hull points in the original array (since the set of convex hull points is a subset of the original point set). In the second case, hull elements are the convex hull points themselves
   */
  invoke(name: 'convexHull', points: Mat, hull: Mat): void;

  /**
   * Finds the convexity defects of a contour.
   * @param contour Input contour
   * @param convexHull Convex hull obtained using convexHull that should contain indices of the contour points that make the hull
   * @param convexityDefects  output vector of convexity defects. In C++ and the new Python/Java interface each convexity defect is represented as 4-element integer vector (a.k.a. Vec4i): (start_index, end_index, farthest_pt_index, fixpt_depth), where indices are 0-based indices in the original contour of the convexity defect beginning, end and the farthest point, and fixpt_depth is fixed-point approximation (with 8 fractional bits) of the distance between the farthest contour point and the hull. That is, to get the floating-point value of the depth will be fixpt_depth/256.0.
   */
  invoke(
    name: 'convexityDefects',
    contour: Mat,
    convexHull: Mat,
    convexityDefects: Mat
  ): void;

  /**
   * Finds contours in a binary image
   * @param image Source, an 8-bit single-channel image. Non-zero pixels are treated as 1's. Zero pixels remain 0's, so the image is treated as binary . You can use compare, inRange, threshold , adaptiveThreshold, Canny, and others to create a binary image out of a grayscale or color one. If mode equals to RETR_CCOMP or RETR_FLOODFILL, the input can also be a 32-bit integer image of labels (CV_32SC1).
   * @param contours Detected contours. Each contour is stored as a vector of points
   * @param mode Contour retrieval mode, @see RetrievalModes
   * @param method Contour approximation method, @see ContourApproximationModes
   */
  invoke(
    name: 'findContours',
    image: Mat,
    contours: MatVector | PointVectorOfVectors,
    mode: RetrievalModes,
    method: ContourApproximationModes
  ): void;

  /**
   * Fits a line to a 2D or 3D point set.
   * @param points Input vector of 2D or 3D points, stored in a Mat.
   * @param line Output line parameters. In case of 2D fitting, it should be a vector of 4 elements (like Vec4f) - (vx, vy, x0, y0), where (vx, vy) is a normalized vector collinear to the line and (x0, y0) is a point on the line. In case of 3D fitting, it should be a vector of 6 elements (like Vec6f) - (vx, vy, vz, x0, y0, z0), where (vx, vy, vz) is a normalized vector collinear to the line and (x0, y0, z0) is a point on the line
   * @param disType Distance used by the M-estimator, @see DistanceTypes
   * @param param Numerical parameter ( C ) for some types of distances. If it is 0, an optimal value is chosen.
   * @param reps Sufficient accuracy for the radius (distance between the coordinate origin and the line).
   * @param aeps Sufficient accuracy for the angle. 0.01 would be a good default value for reps and aeps.
   */
  invoke(
    name: 'fitLine',
    points: Mat,
    line: Mat,
    disType: DistanceTypes,
    param: number,
    reps: number,
    aeps: number
  ): void;

  /**
   * Tests a contour convexity.
   * @param contour
   * @returns whether the input contour is convex or not
   */
  invoke(name: 'isContourConvex', contour: Mat): { value: boolean };

  /**
   * Compares two shapes
   * @param contour1 First contour or grayscale image
   * @param contour2 Second contour or grayscale image
   * @param method Comparison method, @see ShapeMatchModes
   * @param parameter Method-specific parameter (not supported now).
   * @returns
   */
  invoke(
    name: 'matchShapes',
    contour1: Mat,
    contour2: Mat,
    method: ShapeMatchModes,
    parameter: number
  ): { value: number };

  /**
   * Finds a rotated rectangle of the minimum area enclosing the input 2D point set.
   * @param points Input vector of 2D points, stored in a Mat
   * @returns the minimum-area bounding rectangle (possibly rotated) for a specified point set
   */
  invoke(name: 'minAreaRect', points: Mat): RotatedRect;
};
