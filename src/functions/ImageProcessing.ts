export type ImageProcessing = {
  // /**
  //  * Draws a arrow segment pointing from the first point to the second one.
  //  * @param img Image
  //  * @param pt1 The point the arrow starts from.
  //  * @param pt2 The point the arrow points to.
  //  * @param color Line color
  //  * @param thickness Line thickness
  //  * @param line_type Type of the line. See LineTypes
  //  * @param shift Number of fractional bits in the point coordinates.
  //  * @param tipLength The length of the arrow tip in relation to the arrow length
  //  */
  // arrowedLine(
  //   img: Mat,
  //   pt1: Point,
  //   pt2: Point,
  //   color: Scalar,
  //   thickness: number,
  //   line_type: LineTypes,
  //   shift: number,
  //   tipLength: number
  // ): void;
  // arrowedLine(
  //   img: Mat,
  //   pt1: Point,
  //   pt2: Point,
  //   color: Scalar,
  //   thickness: number,
  //   line_type: LineTypes,
  //   shift: number
  // ): void;
  // arrowedLine(
  //   img: Mat,
  //   pt1: Point,
  //   pt2: Point,
  //   color: Scalar,
  //   thickness: number,
  //   line_type: LineTypes
  // ): void;
  // arrowedLine(
  //   img: Mat,
  //   pt1: Point,
  //   pt2: Point,
  //   color: Scalar,
  //   thickness: number
  // ): void;
  // arrowedLine(img: Mat, pt1: Point, pt2: Point, color: Scalar): void;
  // /**
  //  * Draws a circle.
  //  * @param img Image where the circle is drawn.
  //  * @param center Center of the circle.
  //  * @param radius Radius of the circle.
  //  * @param color Circle color.
  //  * @param thickness Thickness of the circle outline, if positive. Negative values, like FILLED, mean that a filled circle is to be drawn
  //  * @param line_type Type of the circle boundary. See LineTypes
  //  * @param shift Number of fractional bits in the coordinates of the center and in the radius value.
  //  */
  // circle(
  //   img: Mat,
  //   center: Point,
  //   radius: number,
  //   color: Scalar,
  //   thickness: number,
  //   line_type: LineTypes,
  //   shift: number
  // ): void;
  // circle(
  //   img: Mat,
  //   center: Point,
  //   radius: number,
  //   color: Scalar,
  //   thickness: number,
  //   line_type: LineTypes
  // ): void;
  // circle(
  //   img: Mat,
  //   center: Point,
  //   radius: number,
  //   color: Scalar,
  //   thickness: number
  // ): void;
  // circle(img: Mat, center: Point, radius: number, color: Scalar): void;
  // /**
  //  * Clips the line against the image rectangle.
  //  * The function cv::clipLine calculates a part of the line segment that is entirely within the specified rectangle. it returns false if the line segment is completely outside the rectangle. Otherwise, it returns true .
  //  * @param imgSize Image size
  //  * @param pt1 First line point.
  //  * @param pt2 Second line point.
  //  */
  // clipLine(imgSize: Size, pt1: Point, pt2: Point): boolean;
  // /**
  //  * Clips the line against the image rectangle.
  //  * The function cv::clipLine calculates a part of the line segment that is entirely within the specified rectangle. it returns false if the line segment is completely outside the rectangle. Otherwise, it returns true .
  //  * @param imgRect Image rectangle
  //  * @param pt1 First line point.
  //  * @param pt2 Second line point.
  //  */
  // clipLine(imgRect: Rect, pt1: Point, pt2: Point): boolean;
  // /**
  //  * Draws contours outlines or filled contours.
  //  * The function draws contour outlines in the image if 𝚝𝚑𝚒𝚌𝚔𝚗𝚎𝚜𝚜≥0 or fills the area bounded by the contours if 𝚝𝚑𝚒𝚌𝚔𝚗𝚎𝚜𝚜<0.
  //  * @param image Destination image.
  //  * @param contours All the input contours. Each contour is stored as a point vector
  //  * @param contourIdx Parameter indicating a contour to draw. If it is negative, all the contours are drawn.
  //  * @param color Color of the contours.
  //  * @param thickness Thickness of lines the contours are drawn with. If it is negative (for example, thickness=FILLED ), the contour interiors are drawn
  //  * @param lineType Line connectivity. See LineTypes
  //  * @param hierarchy Optional information about hierarchy. It is only needed if you want to draw only some of the contours (see maxLevel ).
  //  * @param maxLevel Maximal level for drawn contours. If it is 0, only the specified contour is drawn. If it is 1, the function draws the contour(s) and all the nested contours. If it is 2, the function draws the contours, all the nested contours, all the nested-to-nested contours, and so on. This parameter is only taken into account when there is hierarchy available.
  //  * @param offset Optional contour shift parameter. Shift all the drawn contours by the specified 𝚘𝚏𝚏𝚜𝚎𝚝=(dx,dy) .
  //  */
  // drawContours(
  //   image: Mat,
  //   contours: MatVector,
  //   contourIdx: number,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes,
  //   hierarchy: Mat,
  //   maxLevel: number,
  //   offset: Point
  // ): void;
  // drawContours(
  //   image: Mat,
  //   contours: MatVector,
  //   contourIdx: number,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes,
  //   hierarchy: Mat,
  //   maxLevel: number
  // ): void;
  // drawContours(
  //   image: Mat,
  //   contours: MatVector,
  //   contourIdx: number,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes,
  //   hierarchy: Mat
  // ): void;
  // drawContours(
  //   image: Mat,
  //   contours: MatVector,
  //   contourIdx: number,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes
  // ): void;
  // drawContours(
  //   image: Mat,
  //   contours: MatVector,
  //   contourIdx: number,
  //   color: Scalar,
  //   thickness: number
  // ): void;
  // drawContours(
  //   image: Mat,
  //   contours: MatVector,
  //   contourIdx: number,
  //   color: Scalar
  // ): void;
  // /**
  //  * Draws a marker on a predefined position in an image.
  //  * @param img Image
  //  * @param position The point where the crosshair is positioned
  //  * @param color Line color
  //  * @param markerType The specific type of marker you want to use, see MarkerTypes
  //  * @param markerSize Line thickness
  //  * @param thickness Type of the line, See LineTypes
  //  * @param line_type The length of the marker axis [default = 20 pixels]
  //  */
  // drawMarker(
  //   img: Mat,
  //   position: Point,
  //   color: Scalar,
  //   markerType: MarkerTypes,
  //   markerSize: number,
  //   thickness: number,
  //   line_type: LineTypes
  // ): void;
  // drawMarker(
  //   img: Mat,
  //   position: Point,
  //   color: Scalar,
  //   markerType: MarkerTypes,
  //   markerSize: number,
  //   thickness: number
  // ): void;
  // drawMarker(
  //   img: Mat,
  //   position: Point,
  //   color: Scalar,
  //   markerType: MarkerTypes,
  //   markerSize: number
  // ): void;
  // drawMarker(
  //   img: Mat,
  //   position: Point,
  //   color: Scalar,
  //   markerType: MarkerTypes
  // ): void;
  // drawMarker(img: Mat, position: Point, color: Scalar): void;
  // /**
  //  * Draws a simple or thick elliptic arc or fills an ellipse sector.
  //  * @param img Image
  //  * @param center Center of the ellipse
  //  * @param axes Half of the size of the ellipse main axes
  //  * @param angle Ellipse rotation angle in degrees
  //  * @param startAngle Starting angle of the elliptic arc in degrees
  //  * @param endAngle Ending angle of the elliptic arc in degrees
  //  * @param color Ellipse color.
  //  * @param thickness Thickness of the ellipse arc outline, if positive. Otherwise, this indicates that a filled ellipse sector is to be drawn
  //  * @param lineType Type of the ellipse boundary. See LineTypes
  //  * @param shift Number of fractional bits in the coordinates of the center and values of axes.
  //  */
  // ellipse(
  //   img: Mat,
  //   center: Point,
  //   axes: Size,
  //   angle: number,
  //   startAngle: number,
  //   endAngle: number,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes,
  //   shift: number
  // ): void;
  // ellipse(
  //   img: Mat,
  //   center: Point,
  //   axes: Size,
  //   angle: number,
  //   startAngle: number,
  //   endAngle: number,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes
  // ): void;
  // ellipse(
  //   img: Mat,
  //   center: Point,
  //   axes: Size,
  //   angle: number,
  //   startAngle: number,
  //   endAngle: number,
  //   color: Scalar,
  //   thickness: number
  // ): void;
  // ellipse(
  //   img: Mat,
  //   center: Point,
  //   axes: Size,
  //   angle: number,
  //   startAngle: number,
  //   endAngle: number,
  //   color: Scalar
  // ): void;
  // /**
  //  * Draws a simple or thick elliptic arc or fills an ellipse sector.
  //  * @param img Image
  //  * @param box Alternative ellipse representation via RotatedRect. This means that the function draws an ellipse inscribed in the rotated rectangle
  //  * @param color Ellipse color
  //  * @param thickness Thickness of the ellipse arc outline, if positive. Otherwise, this indicates that a filled ellipse sector is to be drawn.
  //  * @param lineType Type of the ellipse boundary. See LineTypes
  //  */
  // ellipse(
  //   img: Mat,
  //   box: RotatedRect,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes
  // ): void;
  // ellipse(img: Mat, box: RotatedRect, color: Scalar, thickness: number): void;
  // ellipse(img: Mat, box: RotatedRect, color: Scalar): void;
  // /**
  //  * Approximates an elliptic arc with a polyline.
  //  * @param center Center of the arc.
  //  * @param axes Half of the size of the ellipse main axes. See ellipse for details.
  //  * @param angle Rotation angle of the ellipse in degrees. See ellipse for details.
  //  * @param arcStart Starting angle of the elliptic arc in degrees
  //  * @param arcEnd Ending angle of the elliptic arc in degrees
  //  * @param delta Angle between the subsequent polyline vertices. It defines the approximation accuracy
  //  * @param pts Output vector of polyline vertices
  //  */
  // ellipse2Poly(
  //   center: Point,
  //   angle: number,
  //   axes: Size,
  //   arcStart: number,
  //   arcEnd: number,
  //   delta: number,
  //   pts: MatVector
  // ): void;
  // /**
  //  * Fills a convex polygon.
  //  * @param img Image
  //  * @param pts Polygon vertices.
  //  * @param color Polygon color
  //  * @param lineType Type of the polygon boundaries. See LineTypes
  //  * @param shift Number of fractional bits in the vertex coordinates
  //  */
  // fillConvexPoly(
  //   img: Mat,
  //   pts: MatVector,
  //   color: Scalar,
  //   lineType: LineTypes,
  //   shift: number
  // ): void;
  // fillConvexPoly(
  //   img: Mat,
  //   pts: MatVector,
  //   color: Scalar,
  //   lineType: LineTypes
  // ): void;
  // fillConvexPoly(img: Mat, pts: MatVector, color: Scalar): void;
  // /**
  //  * Fills the area bounded by one or more polygons
  //  * @param img Image
  //  * @param pts Array of polygons where each polygon is represented as an array of points
  //  * @param color Polygon colo
  //  * @param lineType Type of the polygon boundaries. See LineTypes
  //  * @param shift Number of fractional bits in the vertex coordinates
  //  * @param offset Optional offset of all points of the contours
  //  */
  // fillPoly(
  //   img: Mat,
  //   pts: MatVector,
  //   color: Scalar,
  //   lineType: LineTypes,
  //   shift: number,
  //   offset: Point
  // ): void;
  // fillPoly(
  //   img: Mat,
  //   pts: MatVector,
  //   color: Scalar,
  //   lineType: LineTypes,
  //   shift: number
  // ): void;
  // fillPoly(img: Mat, pts: MatVector, color: Scalar, lineType: LineTypes): void;
  // fillPoly(img: Mat, pts: MatVector, color: Scalar): void;
  // /**
  //  * Calculates the font-specific size to use to achieve a given height in pixels.
  //  * @param fontFace Font to use, see HersheyFonts.
  //  * @param pixelHeight Pixel height to compute the fontScale for
  //  * @param thickness Thickness of lines used to render the text.
  //  * @returns The fontSize to use for cv::putText
  //  */
  // getFontScaleFromHeight(
  //   fontFace: HersheyFonts,
  //   pixelHeight: number,
  //   thickness: number
  // ): number;
  // getFontScaleFromHeight(fontFace: HersheyFonts, pixelHeight: number): number;
  // /**
  //  * Calculates the width and height of a text string.
  //  * @param text Input text string
  //  * @param fontFace Font to use, see HersheyFonts.
  //  * @param fontScale Font scale factor that is multiplied by the font-specific base size
  //  * @param thickness Thickness of lines used to render the text
  //  * @param baseLine 	y-coordinate of the baseline relative to the bottom-most text point.
  //  * @returns The size of a box that contains the specified text.
  //  */
  // getTextSize(
  //   text: string,
  //   fontFace: HersheyFonts,
  //   fontScale: number,
  //   thickness: number,
  //   baseLine: number
  // ): Size;
  // /**
  //  * Draws a line segment connecting two points.
  //  * @param img Image
  //  * @param pt1 First point of the line segment
  //  * @param pt2 Second point of the line segment
  //  * @param color Line color
  //  * @param thickness Line thickness
  //  * @param lineType Type of the line. See LineTypes.
  //  * @param shift Number of fractional bits in the point coordinates
  //  */
  // line(
  //   img: Mat,
  //   pt1: Point,
  //   pt2: Point,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes,
  //   shift: number
  // ): void;
  // line(
  //   img: Mat,
  //   pt1: Point,
  //   pt2: Point,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes
  // ): void;
  // line(
  //   img: Mat,
  //   pt1: Point,
  //   pt2: Point,
  //   color: Scalar,
  //   thickness: number
  // ): void;
  // line(img: Mat, pt1: Point, pt2: Point, color: Scalar): void;
  // /**
  //  * Draws several polygonal curves
  //  * @param img Image
  //  * @param pts Array of polygonal curves.
  //  * @param isClosed Flag indicating whether the drawn polylines are closed or not. If they are closed, the function draws a line from the last vertex of each curve to its first vertex
  //  * @param color Polyline color
  //  * @param thickness Thickness of the polyline edges
  //  * @param lineType Type of the line segments. See LineTypes
  //  * @param shift Number of fractional bits in the vertex coordinates
  //  */
  // polylines(
  //   img: Mat,
  //   pts: MatVector,
  //   isClosed: boolean,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes,
  //   shift: number
  // ): void;
  // polylines(
  //   img: Mat,
  //   pts: MatVector,
  //   isClosed: boolean,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes
  // ): void;
  // polylines(
  //   img: Mat,
  //   pts: NDArray<Point>,
  //   isClosed: boolean,
  //   color: Scalar,
  //   thickness: number
  // ): void;
  // polylines(img: Mat, pts: MatVector, isClosed: boolean, color: Scalar): void;
  // /**
  //  * Draws a text string.
  //  * @param img Image
  //  * @param text Text string to be drawn
  //  * @param org Bottom-left corner of the text string in the image
  //  * @param fontFace Font type, see HersheyFonts.
  //  * @param fontScale Font scale factor that is multiplied by the font-specific base size
  //  * @param color Text color
  //  * @param thickness Thickness of the lines used to draw a text
  //  * @param lineType Line type. See LineTypes
  //  * @param bottomLeftOrigin When true, the image data origin is at the bottom-left corner. Otherwise, it is at the top-left corner
  //  */
  // putText(
  //   img: Mat,
  //   text: string,
  //   org: Point,
  //   fontFace: HersheyFonts,
  //   fontScale: number,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes,
  //   bottomLeftOrigin: boolean
  // ): void;
  // putText(
  //   img: Mat,
  //   text: string,
  //   org: Point,
  //   fontFace: HersheyFonts,
  //   fontScale: number,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes
  // ): void;
  // putText(
  //   img: Mat,
  //   text: string,
  //   org: Point,
  //   fontFace: HersheyFonts,
  //   fontScale: number,
  //   color: Scalar,
  //   thickness: number
  // ): void;
  // putText(
  //   img: Mat,
  //   text: string,
  //   org: Point,
  //   fontFace: HersheyFonts,
  //   fontScale: number,
  //   color: Scalar
  // ): void;
  // /**
  //  * Draws a simple, thick, or filled up-right rectangle.
  //  * @param img Image
  //  * @param pt1 Vertex of the rectangle
  //  * @param pt2 Vertex of the rectangle opposite to pt1
  //  * @param color Rectangle color or brightness (grayscale image).
  //  * @param thickness Thickness of lines that make up the rectangle. Negative values, like FILLED, mean that the function has to draw a filled rectangle
  //  * @param lineType Type of the line. See LineTypes
  //  * @param shift Number of fractional bits in the point coordinates.
  //  */
  // rectangle(
  //   img: Mat,
  //   pt1: Point,
  //   pt2: Point,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes,
  //   shift: number
  // ): void;
  // rectangle(
  //   img: Mat,
  //   pt1: Point,
  //   pt2: Point,
  //   color: Scalar,
  //   thickness: number,
  //   lineType: LineTypes
  // ): void;
  // rectangle(
  //   img: Mat,
  //   pt1: Point,
  //   pt2: Point,
  //   color: Scalar | number[],
  //   thickness: number
  // ): void;
  // rectangle(img: Mat, pt1: Point, pt2: Point, color: Scalar | number[]): void;
  // /**
  //  * Finds edges in an image using the Canny algorithm
  //  * @param image 8-bit input image.
  //  * @param edges output edge map; single channels 8-bit image, which has the same size as image
  //  * @param threshold1 first threshold for the hysteresis procedure
  //  * @param threshold2 second threshold for the hysteresis procedure
  //  * @param apertureSize aperture size for the Sobel operator
  //  */
  // Canny(image: Mat, edges: Mat, threshold1: number, threshold2: number): void;
  // /**
  //  * Finds edges in an image using the Canny algorithm
  //  * @param dx 16-bit x derivative of input image (CV_16SC1 or CV_16SC3).
  //  * @param dy 16-bit y derivative of input image (same type as dx).
  //  * @param edges output edge map; single channels 8-bit image, which has the same size as image
  //  * @param threshold1 first threshold for the hysteresis procedure
  //  * @param threshold2 second threshold for the hysteresis procedure
  //  */
  // Canny1(
  //   dx: Mat,
  //   dy: Mat,
  //   edges: Mat,
  //   threshold1: number,
  //   threshold2: number
  // ): void;
  // /**
  //  * Harris corner detector
  //  * @param src Input single-channel 8-bit or floating-point image.
  //  * @param dst Image to store the Harris detector responses. It has the type CV_32FC1 and the same size as src
  //  * @param blockSize Neighborhood size
  //  * @param ksize Aperture parameter for the Sobel operator
  //  * @param k Harris detector free parameter. See the formula above
  //  */
  // cornerHarris(
  //   src: Mat,
  //   dst: Mat,
  //   blockSize: number,
  //   ksize: number,
  //   k: number
  // ): void;
  // /**
  //  * Calculates the minimal eigenvalue of gradient matrices for corner detection
  //  * @param src Input single-channel 8-bit or floating-point image
  //  * @param dst Image to store the minimal eigenvalues. It has the type CV_32FC1 and the same size as src
  //  * @param blockSize Neighborhood size
  //  */
  // cornerMinEigenVal(src: Mat, dst: Mat, blockSize: number): void;
  // /**
  //  * Determines strong corners on an image
  //  * @param image Input 8-bit or floating-point 32-bit, single-channel image
  //  * @param corners Output vector of detected corners
  //  * @param maxCorners Maximum number of corners to return. If there are more corners than are found, the strongest of them is returned. maxCorners <= 0 implies that no limit on the maximum is set and all detected corners are returned
  //  * @param qualityLevel Parameter characterizing the minimal accepted quality of image corners. The parameter value is multiplied by the best corner quality measure, which is the minimal eigenvalue (see cornerMinEigenVal ) or the Harris function response (see cornerHarris ). The corners with the quality measure less than the product are rejected. For example, if the best corner has the quality measure = 1500, and the qualityLevel=0.01 , then all the corners with the quality measure less than 15 are rejected.
  //  * @param minDistance Minimum possible Euclidean distance between the returned corners
  //  */
  // goodFeaturesToTrack(
  //   image: Mat,
  //   corners: Mat,
  //   maxCorners: number,
  //   qualityLevel: number,
  //   minDistance: number
  // ): void;
  // /**
  //  *Determines strong corners on an image
  //  * @param image Input 8-bit or floating-point 32-bit, single-channel image
  //  * @param corners Output vector of detected corners
  //  * @param maxCorners Maximum number of corners to return. If there are more corners than are found, the strongest of them is returned. maxCorners <= 0 implies that no limit on the maximum is set and all detected corners are returned
  //  * @param qualityLevel Parameter characterizing the minimal accepted quality of image corners. The parameter value is multiplied by the best corner quality measure, which is the minimal eigenvalue (see cornerMinEigenVal ) or the Harris function response (see cornerHarris ). The corners with the quality measure less than the product are rejected. For example, if the best corner has the quality measure = 1500, and the qualityLevel=0.01 , then all the corners with the quality measure less than 15 are rejected
  //  * @param minDistance Minimum possible Euclidean distance between the returned corners
  //  * @param mask Region of interest. If the image is not empty (it needs to have the type CV_8UC1 and the same size as image ), it specifies the region in which the corners are detected
  //  * @param blockSize Size of an average block for computing a derivative covariation matrix over each pixel neighborhood
  //  * @param gradientSize Aperture parameter for the Sobel operator used for derivatives computation
  //  */
  // goodFeaturesToTrack1(
  //   image: Mat,
  //   corners: Mat,
  //   maxCorners: number,
  //   qualityLevel: number,
  //   minDistance: number,
  //   mask: Mat,
  //   blockSize: number,
  //   gradientSize?: number | 3
  // ): void;
  // /**
  //  * Finds circles in a grayscale image using the Hough transform
  //  * @param image 8-bit, single-channel, grayscale input image.
  //  * @param circles Output vector of found circles. Each vector is encoded as 3 or 4 element floating-point vector (x,y,radius) or (x,y,radius,votes)
  //  * @param method Detection method, see HoughModes. The available methods are HOUGH_GRADIENT and HOUGH_GRADIENT_ALT.
  //  * @param dp Inverse ratio of the accumulator resolution to the image resolution. For example, if dp=1 , the accumulator has the same resolution as the input image. If dp=2 , the accumulator has half as big width and height. For HOUGH_GRADIENT_ALT the recommended value is dp=1.5, unless some small very circles need to be detected
  //  * @param minDist Minimum distance between the centers of the detected circles. If the parameter is too small, multiple neighbor circles may be falsely detected in addition to a true one. If it is too large, some circles may be missed
  //  * this two parameter will be helpful to increase the accuracy of the circle detection
  //  * this two parameter are also available in opencv original documentation
  //  * @param param1 it is the higher threshold of the two passed to the Canny edge detector (the lower canny threshold is twice smaller)
  //  * @param param2 it is the accumulator threshold for the circle centers at the detection stage as discussed above.
  //  */
  // HoughCircles(
  //   image: Mat,
  //   circles: Mat,
  //   method: HoughModes,
  //   dp: number,
  //   minDist: number,
  //   param1?: number,
  //   param2?: number
  // ): void;
  // /**
  //  * Finds lines in a binary image using the standard Hough transform
  //  * @param image 8-bit, single-channel binary source image. The image may be modified by the function.
  //  * @param lines Output vector of lines. Each line is represented by a 2 or 3 element vector (ρ,θ) or (ρ,θ,votes) . ρ is the distance from the coordinate origin (0,0) (top-left corner of the image). θ is the line rotation angle in radians ( 0∼vertical line,π/2∼horizontal line ). votes is the value of accumulator
  //  * @param rho Distance resolution of the accumulator in pixels
  //  * @param theta Angle resolution of the accumulator in radians
  //  * @param threshold Accumulator threshold parameter. Only those lines are returned that get enough votes ( >𝚝𝚑𝚛𝚎𝚜𝚑𝚘𝚕𝚍 ).
  //  */
  // HoughLines(
  //   image: Mat,
  //   lines: Mat,
  //   rho: number,
  //   theta: number,
  //   threshold: number
  // ): void;
  // /**
  //  * Finds line segments in a binary image using the probabilistic Hough transform
  //  * @param image 8-bit, single-channel binary source image. The image may be modified by the function.
  //  * @param lines Output vector of lines. Each line is represented by a 2 or 3 element vector (ρ,θ) or (ρ,θ,votes) . ρ is the distance from the coordinate origin (0,0) (top-left corner of the image). θ is the line rotation angle in radians ( 0∼vertical line,π/2∼horizontal line ). votes is the value of accumulator
  //  * @param rho Distance resolution of the accumulator in pixels
  //  * @param theta Angle resolution of the accumulator in radians
  //  * @param threshold Accumulator threshold parameter. Only those lines are returned that get enough votes ( >𝚝𝚑𝚛𝚎𝚜𝚑𝚘𝚕𝚍 ).
  //  */
  // HoughLinesP(
  //   image: Mat,
  //   lines: Mat,
  //   rho: number,
  //   theta: number,
  //   threshold: number
  // ): void;
  // /**
  //  * Applies the bilateral filter to an image.
  //  * @param src Source 8-bit or floating-point, 1-channel or 3-channel image.
  //  * @param dst Destination image of the same size and type as src .
  //  * @param d Diameter of each pixel neighborhood that is used during filtering. If it is non-positive, it is computed from sigmaSpace.
  //  * @param sigmaColor Filter sigma in the color space. A larger value of the parameter means that farther colors within the pixel neighborhood (see sigmaSpace) will be mixed together, resulting in larger areas of semi-equal color.
  //  * @param sigmaSpace Filter sigma in the coordinate space. A larger value of the parameter means that farther pixels will influence each other as long as their colors are close enough (see sigmaColor ). When d>0, it specifies the neighborhood size regardless of sigmaSpace. Otherwise, d is proportional to sigmaSpace.
  //  * @param borderType border mode used to extrapolate pixels outside of the image, see BorderTypes
  //  */
  // bilateralFilter(
  //   src: Mat,
  //   dst: Mat,
  //   d: number,
  //   sigmaColor: number,
  //   sigmaSpace: number,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  *
  //  * @param src input image; it can have any number of channels, which are processed independently, but the depth should be CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
  //  * @param dst output image of the same size and type as src.
  //  * @param ksize blurring kernel size.
  //  * @param anchor anchor point; default value Point(-1,-1) means that the anchor is at the kernel center.
  //  * @param borderType border mode used to extrapolate pixels outside of the image, see BorderTypes. BORDER_WRAP is not supported.
  //  */
  // blur(
  //   src: Mat,
  //   dst: Mat,
  //   ksize: Size,
  //   anchor: Point,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  * Blurs an image using the box filter.
  //  * @param src input image.
  //  * @param dst output image of the same size and type as src.
  //  * @param ddepth the output image depth (-1 to use src.depth()).
  //  * @param ksize blurring kernel size.
  //  * @param anchor anchor point; default value Point(-1,-1) means that the anchor is at the kernel center.
  //  * @param normalize flag, specifying whether the kernel is normalized by its area or not.
  //  * @param borderType border mode used to extrapolate pixels outside of the image, see BorderTypes. BORDER_WRAP is not supported.
  //  */
  // boxFilter(
  //   src: Mat,
  //   dst: Mat,
  //   ddepth: number | DataTypes,
  //   ksize: Size,
  //   anchor: Point,
  //   normalize: boolean,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  * Constructs the Gaussian pyramid for an image.
  //  * @param src Source image. Check pyrDown for the list of supported types.
  //  * @param dst Destination vector of maxlevel+1 images of the same type as src. dst[0] will be the same as src. dst[1] is the next pyramid layer, a smoothed and down-sized src, and so on.
  //  * @param maxlevel 0-based index of the last (the smallest) pyramid layer. It must be non-negative.
  //  * @param borderType Pixel extrapolation method, see BorderTypes (BORDER_CONSTANT isn't supported)
  //  */
  // buildPyramid(
  //   src: Mat,
  //   dst: Mat,
  //   maxlevel: number,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  * Dilates an image by using a specific structuring element.
  //  * @param src input image; the number of channels can be arbitrary, but the depth should be one of CV_8U, CV_16U, CV_16S, CV_32F or CV_64F
  //  * @param dst output image of the same size and type as src.
  //  * @param kernel structuring element used for dilation; if elemenat=Mat(), a 3 x 3 rectangular structuring element is used. Kernel can be created using getStructuringElement
  //  * @param anchor position of the anchor within the element; default value (-1, -1) means that the anchor is at the element center.
  //  * @param iterations number of times dilation is applied.
  //  * @param borderType pixel extrapolation method, see BorderTypes. BORDER_WRAP is not suported.
  //  * @param borderValue border value in case of a constant border
  //  */
  // dilate(
  //   src: Mat,
  //   dst: Mat,
  //   kernel: Mat,
  //   anchor: Point,
  //   iterations: number,
  //   borderType: BorderTypes,
  //   borderValue: Scalar
  // ): void;
  // /**
  //  * Erodes an image by using a specific structuring element.
  //  * @param src input image; the number of channels can be arbitrary, but the depth should be one of CV_8U, CV_16U, CV_16S, CV_32F or CV_64F
  //  * @param dst output image of the same size and type as src.
  //  * @param kernel structuring element used for dilation; if elemenat=Mat(), a 3 x 3 rectangular structuring element is used. Kernel can be created using getStructuringElement
  //  * @param anchor position of the anchor within the element; default value (-1, -1) means that the anchor is at the element center.
  //  * @param iterations number of times dilation is applied.
  //  * @param borderType pixel extrapolation method, see BorderTypes. BORDER_WRAP is not suported.
  //  * @param borderValue border value in case of a constant border
  //  */
  // erode(
  //   src: Mat,
  //   dst: Mat,
  //   kernel: Mat,
  //   anchor: Point,
  //   iterations: number,
  //   borderType: BorderTypes,
  //   borderValue: Scalar
  // ): void;
  // /**
  //  * Convolves an image with the kernel.
  //  * @param src input image.
  //  * @param dst output image of the same size and the same number of channels as src.
  //  * @param ddepth desired depth of the destination image
  //  * @param kernel convolution kernel (or rather a correlation kernel), a single-channel floating point matrix; if you want to apply different kernels to different channels, split the image into separate color planes using split and process them individually.
  //  * @param anchor anchor of the kernel that indicates the relative position of a filtered point within the kernel; the anchor should lie within the kernel; default value (-1,-1) means that the anchor is at the kernel center.
  //  * @param delat optional value added to the filtered pixels before storing them in dst.
  //  * @param borderType pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.
  //  */
  // filter2D(
  //   src: Mat,
  //   dst: Mat,
  //   ddepth: number | DataTypes,
  //   kernel: MatVector | Mat,
  //   anchor: Point,
  //   delat: number,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  * Blurs an image using a Gaussian filter.
  //  * @param src input image; the image can have any number of channels, which are processed independently, but the depth should be CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
  //  * @param dst output image of the same size and type as src.
  //  * @param ksize Gaussian kernel size. ksize.width and ksize.height can differ but they both must be positive and odd. Or, they can be zero's and then they are computed from sigma.
  //  * @param sigmaX Gaussian kernel standard deviation in X direction.
  //  * @param sigmaY Gaussian kernel standard deviation in Y direction; if sigmaY is zero, it is set to be equal to sigmaX, if both sigmas are zeros, they are computed from ksize.width and ksize.height, respectively (see getGaussianKernel for details); to fully control the result regardless of possible future modifications of all this semantics, it is recommended to specify all of ksize, sigmaX, and sigmaY.
  //  * @param borderType pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.
  //  */
  // GaussianBlur(
  //   src: Mat,
  //   dst: Mat,
  //   ksize: number | Size,
  //   sigmaX: number,
  //   sigmaY: number,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  * Returns filter coefficients for computing spatial image derivatives.
  //  * @param kx Output matrix of row filter coefficients. It has the type ktype .
  //  * @param ky Output matrix of column filter coefficients. It has the type ktype .
  //  * @param dx Derivative order in respect of x.
  //  * @param dy Derivative order in respect of y.
  //  * @param ksize Aperture size. It can be FILTER_SCHARR, 1, 3, 5, or 7.
  //  * @param normalize Flag indicating whether to normalize (scale down) the filter coefficients or not. Theoretically, the coefficients should have the denominator =2ksize∗2−dx−dy−2. If you are going to filter floating-point images, you are likely to use the normalized kernels. But if you compute derivatives of an 8-bit image, store the results in a 16-bit image, and wish to preserve all the fractional bits, you may want to set normalize=false .
  //  * @param ktype Type of filter coefficients. It can be CV_32f or CV_64F .
  //  */
  // getDerivKernels(
  //   kx: MatVector | Mat,
  //   ky: MatVector | Mat,
  //   dx: number,
  //   dy: number,
  //   ksize: 1 | 3 | 5 | 7 | SpecialFilter.FILTER_SCHARR,
  //   normalize: boolean,
  //   ktype: DataTypes.CV_32F | DataTypes.CV_64F
  // ): void;
  // /**
  //  *
  //  * @param ksize Size of the filter returned.
  //  * @param sigma Standard deviation of the gaussian envelope.
  //  * @param theta Orientation of the normal to the parallel stripes of a Gabor function.
  //  * @param lambd Wavelength of the sinusoidal factor.
  //  * @param gamma Spatial aspect ratio.
  //  * @param psi Phase offset.
  //  * @param ktype Type of filter coefficients. It can be CV_32F or CV_64F .
  //  */
  // getGaborKernel(
  //   ksize: Size,
  //   sigma: number,
  //   theta: number,
  //   lambd: number,
  //   gamma: number,
  //   psi: number,
  //   ktype: DataTypes.CV_32F | DataTypes.CV_64F
  // ): Mat;
  // /**
  //  * Returns Gaussian filter coefficients.
  //  * @param ksize Aperture size. It should be odd ( 𝚔𝚜𝚒𝚣𝚎mod2=1 ) and positive.
  //  * @param sigma Gaussian standard deviation. If it is non-positive, it is computed from ksize as sigma = 0.3*((ksize-1)*0.5 - 1) + 0.8.
  //  * @param ktype Type of filter coefficients. It can be CV_32F or CV_64F .
  //  */
  // getGaussianKernel(
  //   ksize: number,
  //   sigma: number,
  //   ktype: DataTypes.CV_32F | DataTypes.CV_64F
  // ): Mat;
  // /**
  //  * Returns a structuring element of the specified size and shape for morphological operations.
  //  * @param shape Element shape that could be one of MorphShapes
  //  * @param ksize Size of the structuring element.
  //  * @param anchor Anchor position within the element. The default value (−1,−1) means that the anchor is at the center. Note that only the shape of a cross-shaped element depends on the anchor position. In other cases the anchor just regulates how much the result of the morphological operation is shifted.
  //  */
  // getStructuringElement(shape: MorphShapes, ksize: Size, anchor: Point): Mat;
  // /**
  //  * Calculates the Laplacian of an image.
  //  * @param src Source image.
  //  * @param dst Destination image of the same size and the same number of channels as src .
  //  * @param ddepth Desired depth of the destination image.
  //  * @param ksize Aperture size used to compute the second-derivative filters. See getDerivKernels for details. The size must be positive and odd.
  //  * @param scale Optional scale factor for the computed Laplacian values. By default, no scaling is applied. See getDerivKernels for details.
  //  * @param delta Optional delta value that is added to the results prior to storing them in dst
  //  * @param borderType Pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.
  //  */
  // Laplacian(
  //   src: Mat,
  //   dst: Mat,
  //   ddepth: number | DataTypes,
  //   ksize: number,
  //   scale: number,
  //   delta: number,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  * Blurs an image using the median filter.
  //  * The function smoothes an image using the median filter with the 𝚔𝚜𝚒𝚣𝚎×𝚔𝚜𝚒𝚣𝚎 aperture. Each channel of a multi-channel image is processed independently. In-place operation is supported.
  //  * @param src input 1-, 3-, or 4-channel image; when ksize is 3 or 5, the image depth should be CV_8U, CV_16U, or CV_32F, for larger aperture sizes, it can only be CV_8U.
  //  * @param dst destination array of the same size and type as src.
  //  * @param ksize aperture linear size; it must be odd and greater than 1, for example: 3, 5, 7 ...
  //  */
  // medianBlur(src: Mat, dst: Mat, ksize: number): void;
  // /**
  //  * returns "magic" border value for erosion and dilation. It is automatically transformed to Scalar::all(-DBL_MAX) for dilation.
  //  */
  // morphologyDefaultBorderValue(): Scalar;
  // /**
  //  * Performs advanced morphological transformations.
  //  * The function cv::morphologyEx can perform advanced morphological transformations using an erosion and dilation as basic operations.
  //  * Any of the operations can be done in-place. In case of multi-channel images, each channel is processed independently.
  //  * @param src Source image. The number of channels can be arbitrary. The depth should be one of CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
  //  * @param dst Destination image of the same size and type as source image.
  //  * @param op Type of a morphological operation, see MorphTypes
  //  * @param kernel Structuring element. It can be created using getStructuringElement.
  //  * @param anchor Anchor position with the kernel. Negative values mean that the anchor is at the kernel center.
  //  * @param iterations Number of times erosion and dilation are applied.
  //  * @param borderType Pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.
  //  * @param borderValue Border value in case of a constant border. The default value has a special meaning.
  //  */
  // morphologyEx(
  //   src: Mat,
  //   dst: Mat,
  //   op: MorphTypes,
  //   kernel: Mat,
  //   anchor: Point,
  //   iterations: number,
  //   borderType: BorderTypes,
  //   borderValue: Scalar
  // ): void;
  // /**
  //  * Blurs an image and downsamples it.
  //  * @param src input image.
  //  * @param dst output image; it has the specified size and the same type as src.
  //  * @param dstsize size of the output image.
  //  * @param borderType Pixel extrapolation method, see BorderTypes (BORDER_CONSTANT isn't supported)
  //  */
  // pyrDown(src: Mat, dst: Mat, dstsize: Size, borderType: BorderTypes): void;
  // /**
  //  * Performs initial step of meanshift segmentation of an image.
  //  * @param src The source 8-bit, 3-channel image.
  //  * @param dst The destination image of the same format and the same size as the source
  //  * @param sp The spatial window radius
  //  * @param sr The color window radius
  //  * @param maxLevel Maximum level of the pyramid for the segmentation
  //  * @param termcrit Termination criteria: when to stop meanshift iterations
  //  */
  // pyrMeanShiftFiltering(
  //   src: Mat,
  //   dst: Mat,
  //   sp: number,
  //   sr: number,
  //   maxLevel: number,
  //   termcrit: TermCriteria
  // ): void;
  // /**
  //  * Upsamples an image and then blurs it.
  //  * @param src input image
  //  * @param dst output image. It has the specified size and the same type as src
  //  * @param dstsize size of the output image
  //  * @param borderType Pixel extrapolation method, see BorderTypes (only BORDER_DEFAULT is supported)
  //  */
  // pyrUp(src: Mat, dst: Mat, dstsize: Size, borderType: BorderTypes): void;
  // /**
  //  * Calculates the first x- or y- image derivative using Scharr operator.
  //  * @param src input image.
  //  * @param dst output image of the same size and the same number of channels as src.
  //  * @param ddepth output image depth, @see https://docs.opencv.org/master/d4/d86/group__imgproc__filter.html#filter_depths
  //  * @param dx order of the derivative x.
  //  * @param dy order of the derivative y.
  //  * @param scale optional scale factor for the computed derivative values; by default, no scaling is applied (see getDerivKernels for details).
  //  * @param delta optional delta value that is added to the results prior to storing them in dst.
  //  * @param borderType pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.
  //  */
  // Scharr(
  //   src: Mat,
  //   dst: Mat,
  //   ddepth: number | DataTypes,
  //   dx: number,
  //   dy: number,
  //   scale: number,
  //   delta: number,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  * Applies a separable linear filter to an image.
  //  *
  //  * Depth combinations
  //  * when ddepth=-1, the output image will have the same depth as the source.
  //  *
  //  *    --------------------------------------------------------
  //  *    | Input depth (src.depth()) |	Output depth (ddepth)    |
  //  *    |=======================================================
  //  *    | CV_8U	                  |  -1/CV_16S/CV_32F/CV_64F |
  //  *    | CV_16U/CV_16S	          |  -1/CV_32F/CV_64F        |
  //  *    | CV_32F	                  |  -1/CV_32F/CV_64F        |
  //  *    | CV_64F	                  |  -1/CV_64F               |
  //  *    --------------------------------------------------------
  //  *
  //  * @param src Source image.
  //  * @param dst Destination image of the same size and the same number of channels as src .
  //  * @param ddepth Destination image depth, @see https://docs.opencv.org/master/d4/d86/group__imgproc__filter.html#filter_depths
  //  * @param kernelX Coefficients for filtering each row.
  //  * @param kernelY Coefficients for filtering each column.
  //  * @param anchor Anchor position within the kernel. The default value (−1,−1) means that the anchor is at the kernel center
  //  * @param delta Value added to the filtered results before storing them
  //  * @param borderType Pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.
  //  */
  // sepFilter2D(
  //   src: Mat,
  //   dst: Mat,
  //   ddepth: number | DataTypes,
  //   kernelX: MatVector | Mat,
  //   kernelY: MatVector | Mat,
  //   anchor: Point,
  //   delta: number,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  * Calculates the first, second, third, or mixed image derivatives using an extended Sobel operator.
  //  * Depth combinations
  //  * when ddepth=-1, the output image will have the same depth as the source.
  //  *
  //  *    --------------------------------------------------------
  //  *    | Input depth (src.depth()) |	Output depth (ddepth)    |
  //  *    |=======================================================
  //  *    | CV_8U	                  |  -1/CV_16S/CV_32F/CV_64F |
  //  *    | CV_16U/CV_16S	          |  -1/CV_32F/CV_64F        |
  //  *    | CV_32F	                  |  -1/CV_32F/CV_64F        |
  //  *    | CV_64F	                  |  -1/CV_64F               |
  //  *    -------------------------------------------------------
  //  * @param src input image.
  //  * @param dst output image of the same size and the same number of channels as src .
  //  * @param ddepth output image depth, @see https://docs.opencv.org/master/d4/d86/group__imgproc__filter.html#filter_depths in the case of 8-bit input images it will result in truncated derivatives.
  //  * @param dx order of the derivative x.
  //  * @param dy order of the derivative y.
  //  * @param ksize size of the extended Sobel kernel; it must be 1, 3, 5, or 7.
  //  * @param scale optional scale factor for the computed derivative values; by default, no scaling is applied (see getDerivKernels for details).
  //  * @param delta optional scale factor for the computed derivative values; by default, no scaling is applied (see getDerivKernels for details).
  //  * @param borderType optional delta value that is added to the results prior to storing them in dst.
  //  */
  // Sobel(
  //   src: Mat,
  //   dst: Mat,
  //   ddepth: number | DataTypes,
  //   dx: number,
  //   dy: number,
  //   ksize: number,
  //   scale: number,
  //   delta: number,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  * Calculates the first order image derivative in both x and y using a Sobel operator.
  //  * @param src input image.
  //  * @param dx output image with first-order derivative in x.
  //  * @param dy output image with first-order derivative in y.
  //  * @param ksize size of Sobel kernel. It must be 3.
  //  * @param borderType pixel extrapolation method, see BorderTypes. Only BORDER_DEFAULT=BORDER_REFLECT_101 and BORDER_REPLICATE are supported.
  //  */
  // spatialGradient(
  //   src: Mat,
  //   dx: MatVector | Mat,
  //   dy: MatVector | Mat,
  //   ksize: number,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  * Calculates the normalized sum of squares of the pixel values overlapping the filter.
  //  * @param src input image
  //  * @param dst output image of the same size and type as _src
  //  * @param ddepth output image depth, @see https://docs.opencv.org/master/d4/d86/group__imgproc__filter.html#filter_depths in the case of 8-bit input images it will result in truncated derivatives.
  //  * @param ksize kernel size
  //  * @param anchor kernel anchor point. The default value of Point(-1, -1) denotes that the anchor is at the kernel center
  //  * @param normalize flag, specifying whether the kernel is to be normalized by it's area or not
  //  * @param borderType border mode used to extrapolate pixels outside of the image, see BorderTypes. BORDER_WRAP is not supported
  //  */
  // sqrBoxFilter(
  //   src: Mat,
  //   dst: Mat,
  //   ddepth: number | DataTypes,
  //   ksize: Size,
  //   anchor: Point,
  //   normalize: boolean,
  //   borderType: BorderTypes
  // ): void;
  // /**
  //  * Applies an adaptive threshold to an array
  //  * @param src Source 8-bit single-channel image.
  //  * @param dst Destination image of the same size and the same type as src
  //  * @param maxValue Non-zero value assigned to the pixels for which the condition is satisfied
  //  * @param adaptiveMethod Adaptive thresholding algorithm to use, @see AdaptiveThresholdTypes. The BORDER_REPLICATE | BORDER_ISOLATED is used to process boundaries
  //  * @param thresholdType Thresholding type that must be either THRESH_BINARY or THRESH_BINARY_INV, @see ThresholdTypes.
  //  * @param blockSize Size of a pixel neighborhood that is used to calculate a threshold value for the pixel: 3, 5, 7, and so on.
  //  * @param C Constant subtracted from the mean or weighted mean (@see the details below). Normally, it is positive but may be zero or negative as well)
  //  */
  // adaptiveThreshold(
  //   src: Mat,
  //   dst: Mat,
  //   maxValue: number,
  //   adaptiveMethod: AdaptiveThresholdTypes,
  //   thresholdType:
  //     | ThresholdTypes.THRESH_BINARY
  //     | ThresholdTypes.THRESH_BINARY_INV,
  //   blockSize: number,
  //   C: number
  // ): void;
  // /**
  //  * Calculates the distance to the closest zero pixel for each pixel of the source image
  //  * @param src 	8-bit, single-channel (binary) source image
  //  * @param dst Output image with calculated distances. It is a 8-bit or 32-bit floating-point, single-channel image of the same size as src
  //  * @param distanceType Type of distance, @see DistanceTypes
  //  * @param maskSize Size of the distance transform mask, @see DistanceTransformMasks. In case of the DIST_L1 or DIST_C distance type, the parameter is forced to 3 because a 3×3 mask gives the same result as 5×5 or any larger aperture.
  //  */
  // distanceTransform(
  //   src: Mat,
  //   dst: Mat,
  //   distanceType: DistanceTypes,
  //   maskSize: DistanceTransformMasks
  // ): void;
  // /**
  //  * Fills a connected component with the given color
  //  * @param image Input/output 1- or 3-channel, 8-bit, or floating-point image. It is modified by the function unless the FLOODFILL_MASK_ONLY flag is set in the second variant of the function. See the details below
  //  * @param seedPoint Starting point
  //  * @param newVal New value of the repainted domain pixels
  //  * @param rect Optional output parameter set by the function to the minimum bounding rectangle of the repainted domain
  //  */
  // floodFill(image: Mat, seedPoint: Point, newVal: Scalar, rect: Rect): void;
  // /**
  //  * Calculates the integral of an image
  //  * @param src input image as W×H, 8-bit or floating-point (32f or 64f).
  //  * @param sum integral image as (W+1)×(H+1) , 32-bit integer or floating-point (32f or 64f).
  //  */
  // integral(src: Mat, sum: Mat): void;
  // /**
  //  * Applies a fixed-level threshold to each array element
  //  * @param src input array (multiple-channel, 8-bit or 32-bit floating point).
  //  * @param dst output array of the same size and type and the same number of channels as src.
  //  * @param thresh threshold value
  //  * @param maxval maximum value to use with the THRESH_BINARY and THRESH_BINARY_INV thresholding types
  //  * @param type thresholding type (@see ThresholdTypes).
  //  */
  // threshold(
  //   src: Mat,
  //   dst: Mat,
  //   thresh: number,
  //   maxval: number,
  //   type: number
  // ): void;
  // /**
  //  * Compares a template against overlapped image regions
  //  * @param image Image where the search is running. It must be 8-bit or 32-bit floating-point
  //  * @param templ Searched template. It must be not greater than the source image and have the same data type.
  //  * @param result Map of comparison results. It must be single-channel 32-bit floating-point. If image is W×H and templ is w×h , then result is (W−w+1)×(H−h+1) .
  //  * @param method Parameter specifying the comparison method, @see TemplateMatchModes
  //  * @param mask Mask of searched template. It must have the same datatype and size with templ. It is not set by default. Currently, only the TM_SQDIFF and TM_CCORR_NORMED methods are supported
  //  */
  // matchTemplate(
  //   image: Mat,
  //   templ: Mat,
  //   result: Mat,
  //   method: TemplateMatchModes,
  //   mask: Mat
  // ): void;
  // /**
  //  * Runs the GrabCut algorithm
  //  * @param img Input 8-bit 3-channel image
  //  * @param mask Input/output 8-bit single-channel mask. The mask is initialized by the function when mode is set to GC_INIT_WITH_RECT. Its elements may have one of the GrabCutClasses.
  //  * @param rect ROI containing a segmented object. The pixels outside of the ROI are marked as "obvious background".
  //  * @param bgdModel Temporary array for the background model. Do not modify it while you are processing the same image.
  //  * @param fgdModel Temporary arrays for the foreground model. Do not modify it while you are processing the same image
  //  * @param iterCount Number of iterations the algorithm should make before returning the result
  //  */
  // grabCut(
  //   img: Mat,
  //   mask: Mat,
  //   rect: Rect,
  //   bgdModel: Mat,
  //   fgdModel: Mat,
  //   iterCount: number,
  //   mode: GrabCutModes
  // ): void;
  // /**
  //  * Performs a marker-based image segmentation using the watershed algorithm
  //  * @param image Input 8-bit 3-channel image
  //  * @param markers Input/output 32-bit single-channel image (map) of markers. It should have the same size as image
  //  */
  // watershed(image: Mat, markers: Mat): void;
};
