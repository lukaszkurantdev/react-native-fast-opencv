import type {
  BorderTypes,
  CmpTypes,
  CovarFlags,
  DecompTypes,
  DftFlags,
  GemmFlags,
  NormTypes,
  ReduceTypes,
  RotateFlags,
  SortFlags,
} from '../constants/Core';
import type { DataTypes } from '../constants/DataTypes';
import type { InterpolationFlags } from '../constants/ImageTransform';
import type {
  Mat,
  MatVector,
  Point,
  Point2f,
  PointVector,
  Rect,
  Scalar,
  Size,
} from '../objects/Objects';

export type Core = {
  /**
   * Calculates the per-element absolute difference between two arrays or between an array and a scalar.
   * @param name Function name.
   * @param src1 first input array.
   * @param src2 second input array.
   * @param dst output array that has the same size and type as input arrays.
   */
  invoke(name: 'absdiff', src1: Mat, src2: Mat, dst: Mat): void;

  /**
   * @param name Function name.
   * @param src1 first input array.
   * @param src2 second input array.
   * @param dst output array that has the same size and type as input arrays.
   * @param mask optional operation mask - 8-bit single channel array, that specifies elements of the output array to be changed.
   * @param dtype optional depth of the output array.
   */
  invoke(name: 'add', src1: Mat, src2: Mat, dst: Mat): void;
  invoke(name: 'add', src1: Mat, src2: Mat, dst: Mat, mask: Mat): void;
  invoke(
    name: 'add',
    src1: Mat,
    src2: Mat,
    dst: Mat,
    mask: Mat,
    dtype: DataTypes
  ): void;

  /**
   * @param name Function name.
   * @param src1 first input array.
   * @param alpha weight of the first array elements.
   * @param src2 second input array of the same size and channel number as src1.
   * @param beta weight of the second array elements.
   * @param gamma scalar added to each sum.
   * @param dst output array that has the same size and number of channels as the input arrays.
   * @param dtype optional depth of the output array; when both input arrays have the same depth, dtype can be set to -1, which will be equivalent to src1.depth().
   */
  invoke(
    name: 'addWeighted',
    src1: Mat,
    alpha: number,
    src2: Mat,
    beta: number,
    gamma: number,
    dst: Mat,
    dtype?: DataTypes
  ): void;

  /**
   * naive nearest neighbor finder
   * @todo document when it's updated in opencv documentation
   */
  invoke(
    name: 'batchDistance',
    src1: Mat,
    src2: Mat,
    dist: Mat,
    dtype: number | DataTypes,
    nidx: Mat,
    normType: NormTypes,
    K: number,
    mask: Mat,
    update: number,
    crosscheck: boolean
  ): void;

  /**
   * computes bitwise conjunction of the two arrays (dst = src1 & src2) Calculates the per-element bit-wise conjunction of two arrays or an array and a scalar.
   * @param name Function name.
   * @param src1 first input array or a scalar.
   * @param src2 second input array or a scalar.
   * @param dst output array that has the same size and type as the input arrays.
   * @param mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.
   */
  invoke(name: 'bitwise_and', src1: Mat, src2: Mat, dst: Mat, mask?: Mat): void;
  /**
   * Inverts every bit of an array.
   * @param name Function name.
   * @param src input array.
   * @param dst output array that has the same size and type as the input array.
   * @param mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.
   */
  invoke(name: 'bitwise_not', src: Mat, dst: Mat, mask?: Mat): void;
  /**
   * Calculates the per-element bit-wise disjunction of two arrays or an array and a scalar.
   * @param name Function name.
   * @param src1 first input array or a scalar.
   * @param src2 second input array or a scalar.
   * @param dst output array that has the same size and type as the input arrays.
   * @param mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.
   */
  invoke(name: 'bitwise_or', src1: Mat, src2: Mat, dst: Mat, mask?: Mat): void;
  /**
   * Calculates the per-element bit-wise "exclusive or" operation on two arrays or an array and a scalar.
   * @param name Function name.
   * @param src1 first input array or a scalar.
   * @param src2 second input array or a scalar.
   * @param dst output array that has the same size and type as the input arrays.
   * @param mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.
   */
  invoke(name: 'bitwise_xor', src1: Mat, src2: Mat, dst: Mat, mask?: Mat): void;

  /**
   * Computes the source location of an extrapolated pixel.
   * @param p 0-based coordinate of the extrapolated pixel along one of the axes, likely <0 or >= len
   * @param len Length of the array along the corresponding axis.
   * @param borderType Border type, one of the BorderTypes, except for BORDER_TRANSPARENT and BORDER_ISOLATED . When borderType==BORDER_CONSTANT , the function always returns -1, regardless of p and len
   */
  invoke(
    name: 'borderInterpolate',
    p: number,
    len: number,
    borderType: BorderTypes
  ): { value: number };

  /**
   * Calculates the covariance matrix of a set of vectors.
   * @param name Function name.
   * @param samples samples stored as separate matrices
   * @param nsamples number of samples
   * @param covar output covariance matrix of the type ctype and square size.
   * @param mean input or output (depending on the flags) array as the average value of the input vectors.
   * @param flags operation flags as a combination of CovarFlags
   * @param ctype type of the matrix
   */
  invoke(
    name: 'calcCovarMatrix',
    samples: MatVector,
    nsamples: number,
    covar: Mat,
    mean: Mat,
    flags: CovarFlags,
    ctype: DataTypes
  ): void;

  /**
   * Calculates the magnitude and angle of 2D vectors.
   * @param name Function name.
   * @param x array of x-coordinates; this must be a single-precision or double-precision floating-point array
   * @param y array of y-coordinates, that must have the same size and same type as x.
   * @param magnitude output array of magnitudes of the same size and type as x
   * @param angle output array of angles that has the same size and type as x; the angles are measured in radians (from 0 to 2*Pi) or in degrees (0 to 360 degrees).
   * @param angleInDegrees flag, indicating whether the angles are measured in radians (which is by default), or in degrees.
   */
  invoke(
    name: 'cartToPolar',
    x: Mat,
    y: Mat,
    magnitude: Mat,
    angle: Mat,
    angleInDegrees?: boolean
  ): void;
  invoke(
    name: 'cartToPolar',
    x: MatVector,
    y: MatVector,
    magnitude: MatVector,
    angle: MatVector,
    angleInDegrees?: boolean
  ): void;

  /**
   * Checks every element of an input array for invalid values.
   * @param name Function name.
   * @param a input array.
   * @param quiet a flag, indicating whether the functions quietly return false when the array elements are out of range or they throw an exception
   * @param pos output parameter, when not NULL, must be a pointer to array of src.dims elements.
   * @param minVal inclusive lower boundary of valid values range.
   * @param maxVal exclusive upper boundary of valid values range.
   */
  invoke(
    name: 'checkRange',
    a: MatVector | Mat,
    quiet: boolean,
    pos: Point,
    minVal: number,
    maxVal: number
  ): void;

  /**
   * Performs the per-element comparison of two arrays or an array and scalar value
   * @param name Function name.
   * @param src1 first input array or a scalar; when it is an array, it must have a single channel
   * @param src2 second input array or a scalar; when it is an array, it must have a single channel
   * @param dst output array of type ref CV_8U that has the same size and the same number of channels as the input arrays
   * @param cmpopa flag, that specifies correspondence between the arrays (cv.CmpTypes)
   */
  invoke(
    name: 'compare',
    src1: Mat,
    src2: Mat,
    dst: Mat,
    cmpop: CmpTypes
  ): void;

  /**
   * @param name Function name.
   * Copies the lower or the upper half of a square matrix to its another half.
   * @param m input-output floating-point square matrix
   * @param lowerToUpper operation flag; if true, the lower half is copied to the upper half. Otherwise, the upper half is copied to the lower half.
   */
  invoke(name: 'completeSymm', m: MatVector | Mat, lowerToUpper: boolean): void;

  /**
   * Converts an array to half precision floating number.\
   * @param name Function name.
   * @param src input array
   * @param dst output array
   */
  invoke(name: 'convertFp16', src: Mat, dst: Mat): void;

  /**
   * Scales, calculates absolute values, and converts the result to 8-bit.
   * @param name Function name.
   * @param src input array
   * @param dst output array
   * @param alpha optional scale factor
   * @param beta optional delta added to the scaled values
   */
  invoke(name: 'convertScaleAbs', src: Mat, dst: Mat, alpha?: number): void;
  invoke(
    name: 'convertScaleAbs',
    src: Mat,
    dst: Mat,
    alpha: number,
    beta?: number
  ): void;
  invoke(
    name: 'convertScaleAbs',
    src: Mat,
    dst: Mat,
    alpha: number,
    beta: number
  ): void;

  /**
   * Forms a border around an image.
   * @param name Function name.
   * @param src Source image
   * @param dst Destination image of the same type as src and the size Size(src.cols+left+right, src.rows+top+bottom)
   * @param top the top pixels
   * @param bottom the bottom pixels
   * @param left the left pixels
   * @param right Parameter specifying how many pixels in each direction from the source image rectangle to extrapolate. For example, top=1, bottom=1, left=1, right=1 mean that 1 pixel-wide border needs to be built
   * @param borderType Border type. See borderInterpolate for details
   * @param value Border value if borderType==BORDER_CONSTANT
   */
  invoke(
    name: 'copyMakeBorder',
    src: Mat,
    dst: Mat,
    top: number,
    bottom: number,
    left: number,
    right: number,
    borderType: BorderTypes,
    value: Scalar
  ): void;

  /**
   * This is an overloaded member function, provided for convenience (python) Copies the matrix to another one.
   * @param name Function name.
   * @param src source matrix
   * @param dst Destination matrix. If it does not have a proper size or type before the operation, it is reallocated
   * @param mask Operation mask of the same size as *this. Its non-zero elements indicate which matrix elements need to be copied. The mask has to be of type CV_8U and can have 1 or multiple channels
   */
  invoke(name: 'copyTo', src: Mat, dst: Mat, mask: Mat): void;

  /**
   * Counts non-zero array elements.
   * @param name Function name.
   * @param src single-channel array
   * @returns the number of non-zero elements in src
   */
  invoke(name: 'countNonZero', src: MatVector | Mat): { value: number };

  /**
   * This functions allows to crop Mat to selected size using Rect.
   * @param name Function name.
   * @param src Source matrix
   * @param dst Destination matrix. If it does not have a proper size or type before the operation, it is reallocated
   * @param roi Rectangle as ROI
   */
  invoke(name: 'crop', src: Mat, dst: Mat, roi: Rect): void;

  /**
   * Performs a forward or inverse discrete Cosine transform of 1D or 2D array.
   * @param name Function name.
   * @param src input floating-point array
   * @param dst output array of the same size and type as src
   * @param flags transformation flags as a combination of cv.DftFlags (DCT_*)
   */
  invoke(name: 'dct', src: Mat, dst: Mat, flags: DftFlags): void;

  /**
   * Returns the determinant of a square floating-point matrix.
   * @param name Function name.
   * @param src input matrix that must have CV_32FC1 or CV_64FC1 type and square size.
   * @returns the determinant of the specified matrix
   */
  invoke(name: 'determinant', src: Mat): { value: number };

  /**
   * Performs a forward or inverse Discrete Fourier transform of a 1D or 2D floating-point array.
   * @param name Function name.
   * @param src input array that could be real or complex
   * @param dst output array whose size and type depends on the flags
   * @param flags transformation flags, representing a combination of the DftFlags
   * @param nonzeroRows when the parameter is not zero, the function assumes that only the first nonzeroRows rows of
   * the input array (DFT_INVERSE is not set) or only the first nonzeroRows of the output array (DFT_INVERSE is set)
   * contain non-zeros, thus, the function can handle the rest of the rows more efficiently and save some time; this
   * technique is very useful for calculating array cross-correlation or convolution using DFT.
   */
  invoke(
    name: 'dft',
    src: Mat,
    dst: Mat,
    flags: DftFlags,
    nonzeroRows: number
  ): void;

  /**
   * @param name Function name.
   * @param src1 first input array.
   * @param src2 second input array of the same size and type as src1.
   * @param dst output array of the same size and type as src2.
   * @param scale scalar factor
   * @param dtype optional depth of the output array; if -1, dst will have depth src2.depth(), but in case of an array-by-array division, you can only pass -1 when src1.depth()==src2.depth().
   */
  invoke(
    name: 'divide',
    src1: Mat,
    src2: Mat,
    dst: Mat,
    scale: number,
    dtype?: number
  ): void;

  /**
   * Calculates eigenvalues and eigenvectors of a symmetric matrix
   * @param name Function name.
   * @param src input matrix that must have CV_32FC1 or CV_64FC1 type, square size and be symmetrical (src ^T^ == src)
   * @param eigenvalues output vector of eigenvalues of the same type as src; the eigenvalues are stored in the descending order
   * @param eigenvectors output matrix of eigenvectors; it has the same size and type as src; the eigenvectors are stored as subsequent matrix rows, in the same order as the corresponding eigenvalues
   */
  invoke(name: 'eigen', src: Mat, eigenvalues: Mat, eigenvectors: Mat): void;

  /**
   * Calculates eigenvalues and eigenvectors of a non-symmetric matrix (real eigenvalues only)
   * @param name Function name.
   * @param src input matrix (CV_32FC1 or CV_64FC1 type)
   * @param eigenvalues output vector of eigenvalues (type is the same type as src)
   * @param eigenvectors output matrix of eigenvectors (type is the same type as src). The eigenvectors are stored as subsequent matrix rows, in the same order as the corresponding eigenvalues
   */
  invoke(
    name: 'eigenNonSymmetric',
    src: Mat,
    eigenvalues: Mat,
    eigenvectors: Mat
  ): void;

  /**
   * Calculates the exponent of every array element.
   * @param name Function name.
   * @param src input array
   * @param dst output array of the same size and type as src
   */
  invoke(name: 'exp', src: Mat, dst: Mat): void;

  /**
   * Extracts a single channel from src (coi is 0-based index)
   * @param name Function name.
   * @param src input array
   * @param dst output array
   * @param coi index of channel to extract
   */
  invoke(name: 'extractChannel', src: Mat, dst: Mat, coi: number): void;

  /**
   * Returns the list of locations of non-zero pixels
   * @param name Function name.
   * @param src single-channel array
   * @param idx the output array, type of cv.Mat or Array<Point>, corresponding to non-zero indices in the input
   */
  invoke(name: 'findNonZero', src: Mat, idx: Mat | PointVector): void;

  /**
   * Flips a 2D array around vertical, horizontal, or both axes
   * @param name Function name.
   * @param src input array
   * @param dst output array of the same size and type as src
   * @param flipCode a flag to specify how to flip the array; 0 means flipping around the x-axis and positive value (for example, 1) means flipping around y-axis. Negative value (for example, -1) means flipping around both axes
   */
  invoke(name: 'flip', src: Mat, dst: Mat, flipCode: number): void;

  /**
   * Performs generalized matrix multiplication
   * @param name Function name.
   * @param src1 first multiplied input matrix that could be real(CV_32FC1, CV_64FC1) or complex(CV_32FC2, CV_64FC2)
   * @param src2 second multiplied input matrix of the same type as src1
   * @param alpha weight of the matrix product
   * @param src3 third optional delta matrix added to the matrix product; it should have the same type as src1 and src2.
   * @param beta weight of src3
   * @param dst output matrix; it has the proper size and the same type as input matrices
   * @param flags operation flags (cv.GemmFlags)
   */
  invoke(
    name: 'gemm',
    src1: Mat,
    src2: Mat,
    alpha: number,
    src3: Mat,
    beta: number,
    dst: Mat,
    flags: GemmFlags
  ): void;

  /**
   * Calculates the optimal DFT size for a given vector size.
   * @param name Function name.
   * @param vecsize vector size
   * @returns the optimal DFT size for a given vector size.
   */
  invoke(name: 'getOptimalDFTSize', vecsize: number): { value: number };

  /**
   * Calculates rotation matrix.
   * @param name Function name.
   * @param center center point
   * @param angle angle value
   * @param scale scale value
   * @param dst output matrix
   */
  invoke(
    name: 'getRotationMatrix2D',
    center: Point2f,
    angle: number,
    scale: number,
    dst: Mat
  ): void;

  /**
   * Applies horizontal concatenation to given matrices
   * @param name Function name.
   * @param src input array or vector of matrices. all of the matrices must have the same number of rows and the same depth
   * @param dst output array. It has the same number of rows and depth as the src, and the sum of cols of the src
   */

  invoke(name: 'hconcat', srcs: MatVector, dst: Mat): void;

  /**
   * Calculates the inverse Discrete Fourier Transform of a 1D or 2D array
   * @param name Function name.
   * @param src input floating-point real or complex array
   * @param dst output array whose size and type depend on the flags
   * @param flags operation flags (see dft and DftFlags).
   * @param nonzeroRows number of dst rows to process
   */
  invoke(
    name: 'idft',
    src: Mat,
    dst: Mat,
    flags: DftFlags,
    nonzeroRows: number
  ): void;

  /**
   * Checks if array elements lie between the elements of two other arrays.
   * @param name Function name.
   * @param src first input array
   * @param lowerb inclusive lower boundary scalar
   * @param upperb inclusive upper boundary scalar
   * @param dst output array of the same size as src and CV_8U type
   */
  invoke(
    name: 'inRange',
    src: Mat,
    lowerb: Scalar,
    upperb: Scalar,
    dst: Mat
  ): void;

  /**
   * Inserts a single channel to dst (coi is 0-based index)
   * @param name Function name.
   * @param src input array
   * @param dst output array
   * @param coi 0-based index
   */
  invoke(name: 'insertChannel', src: Mat, dst: Mat, coi: number): void;

  /**
   * Finds the inverse or pseudo-inverse of a matrix.
   * @param name Function name.
   * @param src input floating-point M x N matrix
   * @param dst output matrix of N x M size and the same type as src
   * @param flags inversion method (cv.DecompTypes)
   */
  invoke(name: 'invert', src: Mat, dst: Mat, flags: DecompTypes): void;

  /**
   * Calculates the natural logarithm of every array element
   * @param name Function name.
   * @param src input array
   * @param dst output array of the same size and type as src
   */
  invoke(name: 'log', src: Mat, dst: Mat): void;

  /**
   * Performs a look-up table transform of an array
   * @param name Function name.
   * @param src input array of 8-bit elements
   * @param lut look-up table of 256 elements; in case of multi-channel input array, the table should either have a single channel (in this case the same table is used for all channels) or the same number of channels as in the input array
   * @param dst output array of the same size and number of channels as src, and the same depth as lut
   */
  invoke(name: 'LUT', src: Mat, lut: Mat, dst: Mat): void;

  /**
   * Calculates the magnitude of 2D vectors
   * @param name Function name.
   * @param x floating-point array of x-coordinates of the vectors
   * @param y floating-point array of y-coordinates of the vectors; it must have the same size as x.
   * @param magnitude output array of the same size and type as x
   */
  invoke(name: 'magnitude', x: Mat, y: Mat, magnitude: Mat): void;
  invoke(name: 'magnitude', x: MatVector, y: MatVector, magnitude: Mat): void;

  /**
   * Calculates the Mahalanobis distance between two vectors
   * @param name Function name.
   * @param v1 first 1D input vector
   * @param v2 second 1D input vector
   * @param icovar inverse covariance matrix
   */
  invoke(name: 'Mahalanobis', v1: Mat, v2: Mat, icovar: Mat): void;
  invoke(name: 'Mahalanobis', v1: MatVector, v2: MatVector, icovar: Mat): void;

  /**
   * Calculates per-element maximum of two arrays or an array and a scalar
   * @param name Function name.
   * @param src1 first input array
   * @param src2 second input array of the same size and type as src1
   * @param dst output array of the same size and type as src1
   */
  invoke(name: 'max', src1: Mat, src2: Mat, dst: Mat): void;

  /**
   * Calculates an average (mean) of array elements
   * @param name Function name.
   * @param src input array that should have from 1 to 4 channels so that the result can be stored in Scalar
   * @param mask optional operation mask
   * @returns a Scalar which contains the average of each channel
   */
  invoke(name: 'mean', src: Mat, mask?: Mat): Scalar;

  /**
   * Calculates a mean and standard deviation of array elements
   * @param name Function name.
   * @param src input array that should have from 1 to 4 channels so that the results can be stored in Scalar
   * @param mean output parameter: calculated mean value
   * @param stddev output parameter: calculated standard deviation
   * @param mask optional operation mask
   */
  invoke(
    name: 'meanStdDev',
    src: Mat,
    mean: Mat,
    stddev: Mat,
    mask?: Mat
  ): void;

  /**
   * This is an overloaded member function, provided for convenience.
   * @param name Function name.
   * @param mv input vector of matrices to be merged; all the matrices in mv must have the same size and the same depth
   * @param dst output array of the same size and the same depth as mv[0]; The number of channels will be the total number of channels in the matrix array
   */
  invoke(name: 'merge', mv: MatVector, dst: Mat): void;

  /**
   * Calculates per-element minimum of two arrays or an array and a scalar
   * @param name Function name.
   * @param src1 first input array
   * @param src2 second input array of the same size and type as src1
   * @param dst output array of the same size and type as src1
   */
  invoke(name: 'min', src1: Mat, src2: Mat, dst: Mat): void;

  /**
   * Finds the global minimum and maximum in an array
   * @param name Function name.
   * @param src input single-channel array
   * @param mask optional mask used to select a sub-array
   */
  invoke(
    name: 'minMaxLoc',
    src: Mat,
    mask?: Mat
  ): {
    minVal: number;
    maxVal: number;
    minX: number;
    minY: number;
    maxX: number;
    maxY: number;
  };

  /**
   * Performs the per-element multiplication of two Fourier spectrums
   * @param name Function name.
   * @param a first input array
   * @param b second input array of the same size and type as src1
   * @param c output array of the same size and type as src1 .
   * @param flags operation flags; currently, the only supported flag is cv.DFT_ROWS, which indicates that each row of src1 and src2 is an independent 1D Fourier spectrum. If you do not want to use this flag, then simply add a 0 as value.
   * @param conjB optional flag that conjugates the second input array before the multiplication (true) or not (false).
   */
  invoke(
    name: 'mulSpectrums',
    a: Mat,
    b: Mat,
    c: Mat,
    flags: DftFlags,
    conjB?: boolean
  ): void;

  /**
   * Calculates the per-element scaled product of two arrays
   * @param name Function name.
   * @param src1 first input array
   * @param src2 second input array of the same size and the same type as src1
   * @param dst output array of the same size and type as src1
   * @param scale optional scale factor
   * @param dtype optional depth of the output array
   */
  invoke(
    name: 'multiply',
    src1: Mat,
    src2: Mat,
    dst: Mat,
    scale: number,
    dtype?: DataTypes
  ): void;

  /**
   * Calculates the product of a matrix and its transposition
   * @param name Function name.
   * @param src input single-channel matrix. Note that unlike gemm, the function can multiply not only floating-point matrices
   * @param dst output square matrix
   * @param aTa Flag specifying the multiplication ordering. See the description below
   * @param delta Optional delta matrix subtracted from src before the multiplication. When the matrix is empty ( delta=noArray() ), it is assumed to be zero, that is, nothing is subtracted. If it has the same size as src , it is simply subtracted. Otherwise, it is "repeated" (see repeat ) to cover the full src and then subtracted. Type of the delta matrix, when it is not empty, must be the same as the type of created output matrix. See the dtype parameter description below
   * @param scale Optional scale factor for the matrix product.
   * @param dtype Optional type of the output matrix. When it is negative, the output matrix will have the same type as src
   */
  invoke(
    name: 'mulTransposed',
    src: Mat,
    dst: Mat,
    aTa: boolean,
    delta: Mat,
    scale: number,
    dtype?: DataTypes
  ): void;

  /**
   * Calculates the absolute norm of an array
   * @param name Function name.
   * @param src first input array
   * @param normType type of the norm (see cv.NormTypes).
   * @param mask optional operation mask; it must have the same size as src1 and CV_8UC1 type.
   * @returns the absolute norm of an array
   */
  invoke(
    name: 'norm',
    src: Mat,
    normType: NormTypes,
    mask?: Mat
  ): { norm: number };

  /**
   * Normalizes the norm or value range of an array.
   * @param name Function name.
   * @param src input array
   * @param dst output array of the same size as src
   * @param alpha norm value to normalize to or the lower range boundary in case of the range normalization
   * @param normType normalization type (see cv::NormTypes).
   */
  invoke(
    name: 'normalize',
    src: Mat,
    dst: Mat,
    alpha: number,
    normType: NormTypes
  ): void;

  /**
   * Merges several arrays to make a single multi-channel array.
   * @param name Function name.
   * @param channels input vector of matrices to be merged; all the matrices in mv must have the same size and the same depth.
   * @param dst output array of the same size and the same depth as mv[0]; The number of channels will be the total number of channels in the matrix array.
   */
  invoke(name: 'merge', channels: MatVector, dst: Mat): void;

  /**
   * converts NaNs to the given number
   * @param name Function name.
   * @param a input/output matrix (CV_32F type).
   * @param val value to convert the NaNs
   */
  invoke(name: 'patchNaNs', a: Mat | MatVector, val: number): void;

  /**
   * Performs the perspective matrix transformation of vectors
   * @param name Function name.
   * @param src input two-channel or three-channel floating-point array; each element is a 2D/3D vector to be transformed
   * @param dst output array of the same size and type as src
   * @param m 3x3 or 4x4 floating-point transformation matrix.
   */
  invoke(name: 'perspectiveTransform', src: Mat, dst: Mat, m: Mat): void;

  /**
   * Calculates the rotation angle of 2D vectors
   * @param name Function name.
   * @param x input floating-point array of x-coordinates of 2D vectors
   * @param y input array of y-coordinates of 2D vectors; it must have the same size and the same type as x
   * @param angle output array of vector angles; it has the same size and same type as x
   * @param angleInDegrees when true, the function calculates the angle in degrees, otherwise, they are measured in radians
   */
  invoke(
    name: 'phase',
    x: Mat,
    y: Mat,
    angle: Mat,
    angleInDegrees: boolean
  ): void;
  invoke(
    name: 'phase',
    x: MatVector,
    y: MatVector,
    angle: Mat,
    angleInDegrees: boolean
  ): void;

  /**
   * Raises every array element to a power
   * @param name Function name.
   * @param src input array
   * @param power exponent of power
   * @param dst output array of the same size and type as src
   */
  invoke(name: 'pow', src: Mat, power: number, dst: Mat): void;

  /**
   * Computes the Peak Signal-to-Noise Ratio (PSNR) image quality metric
   * @param name Function name.
   * @param src1 first input array
   * @param src2 second input array of the same size as src1
   * @param R the maximum pixel value (255 by default)
   * @returns the Peak Signal-to-Noise Ratio (PSNR) image quality metric in decibels (dB)
   */
  invoke(name: 'PSNR', src1: Mat, src2: Mat, R: number): { psnr: number };

  /**
   * Reduces a matrix to a vector.
   * @param name Function name.
   * @param src input 2D matrix
   * @param dst output vector. Its size and type is defined by dim and dtype parameters
   * @param dim dimension index along which the matrix is reduced. 0 means that the matrix is reduced to a single row. 1 means that the matrix is reduced to a single column
   * @param rtype reduction operation that could be one of ReduceTypes
   * @param dtype when negative, the output vector will have the same type as the input matrix, otherwise, its type will be CV_MAKE_TYPE(CV_MAT_DEPTH(dtype), src.channels())
   */
  invoke(
    name: 'reduce',
    src: Mat,
    dst: Mat,
    dim: number,
    rtype: ReduceTypes,
    dtype: DataTypes
  ): void;

  /**
   * Fills the output array with repeated copies of the input array
   * @param name Function name.
   * @param src input array to replicate
   * @param ny Flag to specify how many times the src is repeated along the vertical axis
   * @param nx Flag to specify how many times the src is repeated along the horizontal axis
   * @param dst output array of the same type as src.
   */
  invoke(name: 'repeat', src: Mat, ny: number, nx: number, dst: Mat): void;

  /**
   * The function resize resizes the image src down to or up to the specified size. Note that the
   * initial dst type or size are not taken into account. Instead, the size and type are derived from
   * the `src`,`dsize`,`fx`, and `fy`.
   * @param name Function name.
   * @param src input image.
   * @param dst output image; it has the size dsize (when it is non-zero) or the size computed from src.size(), fx, and fy; the type of dst is the same as of src.
   * @param dsize output image size
   * @param fx scale factor along the horizontal axis
   * @param fy scale factor along the vertical axis
   * @param interpolation interpolation method, see #InterpolationFlags
   */
  invoke(
    name: 'resize',
    src: Mat,
    dst: Mat,
    dsize: Size,
    fx: number,
    fy: number,
    interpolation: InterpolationFlags
  ): void;

  /**
   * Rotates matrix.
   * @param name Function name.
   * @param src input array to replicate
   * @param dst output array of the same type as src
   * @param code rotate flag
   */
  invoke(name: 'rotate', src: Mat, dst: Mat, code: RotateFlags): void;

  /**
   * Calculates the sum of a scaled array and another array
   * @param name Function name.
   * @param src1 first input array.
   * @param alpha scale factor for the first array
   * @param src2 second input array of the same size and type as src1
   * @param dst output array of the same size and type as src1
   */
  invoke(name: 'scaleAdd', src1: Mat, alpha: number, src2: Mat, dst: Mat): void;

  /**
   * Solves one or more linear systems or least-squares problems
   * @param name Function name.
   * @param src1 input matrix on the left-hand side of the system
   * @param src2 input matrix on the right-hand side of the system
   * @param dst output solution
   * @param flags solution (matrix inversion) method (DecompTypes)
   */
  invoke(
    name: 'solve',
    src1: Mat,
    src2: Mat,
    dst: Mat,
    flags: DecompTypes
  ): { resolved: boolean };

  /**
   * Finds the real roots of a cubic equation
   * @param name Function name.
   * @param coeffs equation coefficients, an array of 3 or 4 elements
   * @param roots output array of real roots that has 1 or 3 elements
   */
  invoke(name: 'solveCubic', coeffs: Mat, roots: Mat): { value: boolean };

  /**
   * Finds the real or complex roots of a polynomial equation
   * @param name Function name.
   * @param src array of polynomial coefficients
   * @param dst output (complex) array of roots
   * @param maxIters maximum number of iterations the algorithm does
   */
  invoke(
    name: 'solvePoly',
    src: Mat,
    dst: Mat,
    maxIters: number
  ): { value: number };

  /**
   * Sorts each row or each column of a matrix.
   * @param name Function name.
   * @param src input single-channel array
   * @param dst output array of the same size and type as src.
   * @param flags operation flags, a combination of SortFlags
   */
  invoke(name: 'sort', src: Mat, dst: Mat, flags: SortFlags): void;

  /**
   * Sorts each row or each column of a matrix
   * @param name Function name.
   * @param src input single-channel array
   * @param dst output array of the same size and type as src.
   * @param flags operation flags, a combination of SortFlags
   */
  invoke(name: 'sortIdx', src: Mat, dst: Mat, flags: SortFlags): void;

  /**
   * Divides a multi-channel array into several single-channel arrays
   * @param name Function name.
   * @param src input multi-channel array.
   * @param dst output vector of arrays; the arrays themselves are reallocated, if needed.
   */
  invoke(name: 'split', src: Mat, dst: MatVector): void;

  /**
   * Calculates a square root of array elements
   * @param name Function name.
   * @param src input floating-point array.
   * @param dst output array of the same size and type as src
   */
  invoke(name: 'sqrt', src: Mat, dst: Mat): void;

  /**
   * @param name Function name.
   * @param src1 first input array or a scalar
   * @param src2 second input array or a scalar
   * @param dst output array of the same size and the same number of channels as the input array
   * @param mask optional operation mask; this is an 8-bit single channel array that specifies elements of the output array to be changed
   * @param dtype optional depth of the output array
   */
  invoke(
    name: 'subtract',
    src1: Mat,
    src2: Mat,
    dst: Mat,
    mask: Mat,
    dtype: DataTypes
  ): void;
  invoke(name: 'subtract', src1: Mat, src2: Mat, dst: Mat, mask: Mat): void;
  invoke(name: 'subtract', src1: Mat, src2: Mat, dst: Mat): void;

  /**
   * Calculates the sum of array elements
   * @param name Function name.
   * @param src input array that must have from 1 to 4 channels
   */
  invoke(name: 'sum', src: MatVector | Mat): Scalar;

  /**
   * Returns the trace of a matrix
   * @param name Function name.
   * @param mtx input matrix
   */
  invoke(name: 'trace', mtx: Mat): Scalar;

  /**
   * Performs the matrix transformation of every array element
   * @param name Function name.
   * @param src input array that must have as many channels (1 to 4) as m.cols or m.cols-1.
   * @param dst output array of the same size and depth as src; it has as many channels as m.rows
   * @param m transformation 2x2 or 2x3 floating-point matrix
   */
  invoke(name: 'transform', src: Mat, dst: Mat, m: Mat): void;

  /**
   * Transposes a matrix
   * @param name Function name.
   * @param src input array.
   * @param dst output array of the same type as src
   */
  invoke(name: 'transpose', src: Mat, dst: Mat): void;

  /**
   * Applies vertical concatenation to given matrices
   * @param name Function name.
   * @param src input array or vector of matrices. all of the matrices must have the same number of cols and the same depth
   * @param dst output array. It has the same number of cols and depth as the src, and the sum of rows of the src. same depth
   */
  invoke(name: 'vconcat', src: MatVector, dst: Mat): void;

  /**
   * Converts an array to another data type with optional scaling.
   * @param name Function name.
   * @param src input matrix.
   * @param dst output matrix; if it does not have a proper size or type before the operation, it is reallocated.
   * @param rtype desired output matrix type or, rather, the depth since the number of channels are the same as the input has; if rtype is negative, the output matrix will have the same type as the input.
   * @param alpha optional scale factor.
   * @param beta optional delta added to the scaled values.
   */
  invoke(
    name: 'convertTo',
    src: Mat,
    dst: Mat,
    rtype: DataTypes,
    alpha?: number,
    beta?: number
  ): void;
};
