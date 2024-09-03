# Available OpenCV functions

## Core

### absdiff
Calculates the per-element absolute difference between two arrays or between an array and a scalar.
- src1 first input array.
- src2 second input array.
- dst output array that has the same size and type as input arrays.

```js
invoke(name: 'absdiff', src1: Mat, src2: Mat, dst: Mat): void;
```

### add

- src1 first input array.
- src2 second input array.
- dst output array that has the same size and type as input arrays.
- mask optional operation mask - 8-bit single channel array, that specifies elements of the output array to be changed.
- dtype optional depth of the output array.

```js
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
```



### addWeighted

- src1 first input array.
- alpha weight of the first array elements.
- src2 second input array of the same size and channel number as src1.
- beta weight of the second array elements.
- gamma scalar added to each sum.
- dst output array that has the same size and number of channels as the input arrays.
- dtype optional depth of the output array; when both input arrays have the same depth, dtype can be set to -1, which will be equivalent to src1.depth().

```js
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
```

### batchDistance

naive nearest neighbor finder

```js
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
```

### bitwise_and

computes bitwise conjunction of the two arrays (dst = src1 & src2) Calculates the per-element bit-wise conjunction of two arrays or an array and a scalar.

- src1 first input array or a scalar.
- src2 second input array or a scalar.
- dst output array that has the same size and type as the input arrays.
- mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.

```js
invoke(name: 'bitwise_and', src1: Mat, src2: Mat, dst: Mat, mask?: Mat): void;
```

### bitwise_not

Inverts every bit of an array.

- src input array.
- dst output array that has the same size and type as the input array.
- mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.

```js
invoke(name: 'bitwise_not', src: Mat, dst: Mat, mask?: Mat): void;
```

### bitwise_or

Calculates the per-element bit-wise disjunction of two arrays or an array and a scalar.

- src1 first input array or a scalar.
- src2 second input array or a scalar.
- dst output array that has the same size and type as the input arrays.
- mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.

```js
invoke(name: 'bitwise_or', src1: Mat, src2: Mat, dst: Mat, mask?: Mat): void;
```

### bitwise_xor

Calculates the per-element bit-wise "exclusive or" operation on two arrays or an array and a scalar.

- src1 first input array or a scalar.
- src2 second input array or a scalar.
- dst output array that has the same size and type as the input arrays.
- mask optional operation mask, 8-bit single channel array, that specifies elements of the output array to be changed.

```js
invoke(name: 'bitwise_xor', src1: Mat, src2: Mat, dst: Mat, mask?: Mat): void;
```

### borderInterpolate

Computes the source location of an extrapolated pixel.
- p 0-based coordinate of the extrapolated pixel along one of the axes, likely <0 or >= len
- len Length of the array along the corresponding axis.
- borderType Border type, one of the BorderTypes, except for BORDER_TRANSPARENT and BORDER_ISOLATED . When borderType==BORDER_CONSTANT , the function always returns -1, regardless of p and len

```js
invoke(
  name: 'borderInterpolate',
  p: number,
  len: number,
  borderType: BorderTypes
): { value: number };
```

### calcCovarMatrix

Calculates the covariance matrix of a set of vectors.

- samples samples stored as separate matrices
- nsamples number of samples
- covar output covariance matrix of the type ctype and square size.
- mean input or output (depending on the flags) array as the average value of the input vectors.
- flags operation flags as a combination of CovarFlags
- ctype type of the matrix

```js
invoke(
  name: 'calcCovarMatrix',
  samples: MatVector,
  nsamples: number,
  covar: Mat,
  mean: Mat,
  flags: CovarFlags,
  ctype: DataTypes
): void;
```

### cartToPolar

Calculates the magnitude and angle of 2D vectors.

- x array of x-coordinates; this must be a single-precision or double-precision floating-point array
- y array of y-coordinates, that must have the same size and same type as x.
- magnitude output array of magnitudes of the same size and type as x
- angle output array of angles that has the same size and type as x; the angles are measured in radians (from 0 to 2*Pi) or in degrees (0 to 360 degrees).
- angleInDegrees flag, indicating whether the angles are measured in radians (which is by default), or in degrees.

```js
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
```

### checkRange

Checks every element of an input array for invalid values.

- a input array.
- quiet a flag, indicating whether the functions quietly return false when the array elements are out of range or they throw an exception
- pos output parameter, when not NULL, must be a pointer to array of src.dims elements.
- minVal inclusive lower boundary of valid values range.
- maxVal exclusive upper boundary of valid values range.

```js
invoke(
  name: 'checkRange',
  a: MatVector | Mat,
  quiet: boolean,
  pos: Point,
  minVal: number,
  maxVal: number
): void;
```

### compare

Performs the per-element comparison of two arrays or an array and scalar value

- src1 first input array or a scalar; when it is an array, it must have a single channel
- src2 second input array or a scalar; when it is an array, it must have a single channel
- dst output array of type ref CV_8U that has the same size and the same number of channels as the input arrays
- cmpopa flag, that specifies correspondence between the arrays (cv.CmpTypes)

```js
invoke(
  name: 'compare',
  src1: Mat,
  src2: Mat,
  dst: Mat,
  cmpop: CmpTypes
): void;
```

### completeSymm

Copies the lower or the upper half of a square matrix to its another half.
- m input-output floating-point square matrix
- lowerToUpper operation flag; if true, the lower half is copied to the upper half. Otherwise, the upper half is copied to the lower half.

```js
invoke(name: 'completeSymm', m: MatVector | Mat, lowerToUpper: boolean): void;
```

### convertFp16

Converts an array to half precision floating number.

- src input array
- dst output array

```js
invoke(name: 'convertFp16', src: Mat, dst: Mat): void;
```

### convertScaleAbs

Scales, calculates absolute values, and converts the result to 8-bit.

- src input array
- dst output array
- alpha optional scale factor
- beta optional delta added to the scaled values

```js
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
```

### convertTo

Converts an array to another data type with optional scaling.

- src input array
- dst output array of the same type as src
- rtype  desired output matrix type or, rather, the depth since the number of channels are the same as the input has; if rtype is negative, the output matrix will have the same type as the input.

```js
invoke(name: 'convertTo', src: Mat, dst: Mat, rtype: DataTypes): void;
```

### copyMakeBorder

Forms a border around an image.

- src Source image
- dst Destination image of the same type as src and the size Size(src.cols+left+right, src.rows+top+bottom)
- top the top pixels
- bottom the bottom pixels
- left the left pixels
- right Parameter specifying how many pixels in each direction from the source image rectangle to extrapolate. For example, top=1, bottom=1, left=1, right=1 mean that 1 pixel-wide border needs to be built
- borderType Border type. See borderInterpolate for details
- value Border value if borderType==BORDER_CONSTANT

```js
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
```

### copyTo

This is an overloaded member function, provided for convenience (python) Copies the matrix to another one.

- src source matrix
- dst Destination matrix. If it does not have a proper size or type before the operation, it is reallocated
- mask Operation mask of the same size as *this. Its non-zero elements indicate which matrix elements need to be copied. The mask has to be of type CV_8U and can have 1 or multiple channels

```js
invoke(name: 'copyTo', src: Mat, dst: Mat, mask: Mat): void;
```

### countNonZero

Counts non-zero array elements.

- src single-channel array
@returns the number of non-zero elements in src

```js
invoke(name: 'countNonZero', src: MatVector | Mat): { value: number };
```

### dct

Performs a forward or inverse discrete Cosine transform of 1D or 2D array.

- src input floating-point array
- dst output array of the same size and type as src
- flags transformation flags as a combination of cv.DftFlags (DCT_*)

```js
invoke(name: 'dct', src: Mat, dst: Mat, flags: DftFlags): void;
```

### determinant

Returns the determinant of a square floating-point matrix.

- src input matrix that must have CV_32FC1 or CV_64FC1 type and square size.
@returns the determinant of the specified matrix

```js
invoke(name: 'determinant', src: Mat): { value: number };
```

### dft

Performs a forward or inverse Discrete Fourier transform of a 1D or 2D floating-point array.

- src input array that could be real or complex
- dst output array whose size and type depends on the flags
- flags transformation flags, representing a combination of the DftFlags
- nonzeroRows when the parameter is not zero, the function assumes that only the first nonzeroRows rows of
the input array (DFT_INVERSE is not set) or only the first nonzeroRows of the output array (DFT_INVERSE is set)
contain non-zeros, thus, the function can handle the rest of the rows more efficiently and save some time; this
technique is very useful for calculating array cross-correlation or convolution using DFT.

```js
invoke(
  name: 'dft',
  src: Mat,
  dst: Mat,
  flags: DftFlags,
  nonzeroRows: number
): void;
```

### divide

- src1 first input array.
- src2 second input array of the same size and type as src1.
- dst output array of the same size and type as src2.
- scale scalar factor
- dtype optional depth of the output array; if -1, dst will have depth src2.depth(), but in case of an array-by-array division, you can only pass -1 when src1.depth()==src2.depth().

```js
invoke(
  name: 'divide',
  src1: Mat,
  src2: Mat,
  dst: Mat,
  scale: number,
  dtype?: number
): void;
```

### eigen

Calculates eigenvalues and eigenvectors of a symmetric matrix

- src input matrix that must have CV_32FC1 or CV_64FC1 type, square size and be symmetrical (src ^T^ == src)
- eigenvalues output vector of eigenvalues of the same type as src; the eigenvalues are stored in the descending order
- eigenvectors output matrix of eigenvectors; it has the same size and type as src; the eigenvectors are stored as subsequent matrix rows, in the same order as the corresponding eigenvalues

```js
invoke(name: 'eigen', src: Mat, eigenvalues: Mat, eigenvectors: Mat): void;
```

### eigenNonSymmetric

Calculates eigenvalues and eigenvectors of a non-symmetric matrix (real eigenvalues only)

- src input matrix (CV_32FC1 or CV_64FC1 type)
- eigenvalues output vector of eigenvalues (type is the same type as src)
- eigenvectors output matrix of eigenvectors (type is the same type as src). The eigenvectors are stored as subsequent matrix rows, in the same order as the corresponding eigenvalues

```js
invoke(
  name: 'eigenNonSymmetric',
  src: Mat,
  eigenvalues: Mat,
  eigenvectors: Mat
): void;
```

### exp

Calculates the exponent of every array element.

- src input array
- dst output array of the same size and type as src

```js
invoke(name: 'exp', src: Mat, dst: Mat): void;
```

### extractChannel

Extracts a single channel from src (coi is 0-based index)

- src input array
- dst output array
- coi index of channel to extract

```js
invoke(name: 'extractChannel', src: Mat, dst: Mat, coi: number): void;
```

### findNonZero

Returns the list of locations of non-zero pixels

- src single-channel array
- idx the output array, type of cv.Mat or Array<Point>, corresponding to non-zero indices in the input

```js
invoke(name: 'findNonZero', src: Mat, idx: Mat | PointVector): void;
```

### flip

Flips a 2D array around vertical, horizontal, or both axes

- src input array
- dst output array of the same size and type as src
- flipCode a flag to specify how to flip the array; 0 means flipping around the x-axis and positive value (for example, 1) means flipping around y-axis. Negative value (for example, -1) means flipping around both axes

```js
invoke(name: 'flip', src: Mat, dst: Mat, flipCode: number): void;
```

### gemm

Performs generalized matrix multiplication

- src1 first multiplied input matrix that could be real(CV_32FC1, CV_64FC1) or complex(CV_32FC2, CV_64FC2)
- src2 second multiplied input matrix of the same type as src1
- alpha weight of the matrix product
- src3 third optional delta matrix added to the matrix product; it should have the same type as src1 and src2.
- beta weight of src3
- dst output matrix; it has the proper size and the same type as input matrices
- flags operation flags (cv.GemmFlags)

```js
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
```

### getOptimalDFTSize

Calculates the optimal DFT size for a given vector size.

- vecsize vector size
@returns the optimal DFT size for a given vector size.

```js
invoke(name: 'getOptimalDFTSize', vecsize: number): { value: number };
```

### hconcat

Applies horizontal concatenation to given matrices

- src input array or vector of matrices. all of the matrices must have the same number of rows and the same depth
- dst output array. It has the same number of rows and depth as the src, and the sum of cols of the src

```js
invoke(name: 'hconcat', srcs: MatVector, dst: Mat): void;
```

### idft

Calculates the inverse Discrete Fourier Transform of a 1D or 2D array

- src input floating-point real or complex array
- dst output array whose size and type depend on the flags
- flags operation flags (see dft and DftFlags).
- nonzeroRows number of dst rows to process

```js
invoke(
  name: 'idft',
  src: Mat,
  dst: Mat,
  flags: DftFlags,
  nonzeroRows: number
): void;
```

### inRange

Checks if array elements lie between the elements of two other arrays.

- src first input array
- lowerb inclusive lower boundary scalar
- upperb inclusive upper boundary scalar
- dst output array of the same size as src and CV_8U type

```js
invoke(
  name: 'inRange',
  src: Mat,
  lowerb: Scalar,
  upperb: Scalar,
  dst: Mat
): void;
```

### insertChannel

Inserts a single channel to dst (coi is 0-based index)

- src input array
- dst output array
- coi 0-based index

```js
invoke(name: 'insertChannel', src: Mat, dst: Mat, coi: number): void;
```

### invert

Finds the inverse or pseudo-inverse of a matrix.

- src input floating-point M x N matrix
- dst output matrix of N x M size and the same type as src
- flags inversion method (cv.DecompTypes)

```js
invoke(name: 'invert', src: Mat, dst: Mat, flags: DecompTypes): void;
```

### log

Calculates the natural logarithm of every array element

- src input array
- dst output array of the same size and type as src

```js
invoke(name: 'log', src: Mat, dst: Mat): void;
```

### LUT

Performs a look-up table transform of an array

- src input array of 8-bit elements
- lut look-up table of 256 elements; in case of multi-channel input array, the table should either have a single channel (in this case the same table is used for all channels) or the same number of channels as in the input array
- dst output array of the same size and number of channels as src, and the same depth as lut

```js
invoke(name: 'LUT', src: Mat, lut: Mat, dst: Mat): void;
```

### magnitude

Calculates the magnitude of 2D vectors

- x floating-point array of x-coordinates of the vectors
- y floating-point array of y-coordinates of the vectors; it must have the same size as x.
- magnitude output array of the same size and type as x

```js
invoke(name: 'magnitude', x: Mat, y: Mat, magnitude: Mat): void;
invoke(name: 'magnitude', x: MatVector, y: MatVector, magnitude: Mat): void;
```

### Mahalanobis

Calculates the Mahalanobis distance between two vectors

- v1 first 1D input vector
- v2 second 1D input vector
- icovar inverse covariance matrix

```js
invoke(name: 'Mahalanobis', v1: Mat, v2: Mat, icovar: Mat): void;
invoke(name: 'Mahalanobis', v1: MatVector, v2: MatVector, icovar: Mat): void;
```

### max

Calculates per-element maximum of two arrays or an array and a scalar

- src1 first input array
- src2 second input array of the same size and type as src1
- dst output array of the same size and type as src1

```js
invoke(name: 'max', src1: Mat, src2: Mat, dst: Mat): void;
```

### mean

Calculates an average (mean) of array elements

- src input array that should have from 1 to 4 channels so that the result can be stored in Scalar
- mask optional operation mask
@returns a Scalar which contains the average of each channel

```js
invoke(name: 'mean', src: Mat, mask?: Mat): Scalar;
```

### meanStdDev

Calculates a mean and standard deviation of array elements

- src input array that should have from 1 to 4 channels so that the results can be stored in Scalar
- mean output parameter: calculated mean value
- stddev output parameter: calculated standard deviation
- mask optional operation mask

```js
invoke(
  name: 'meanStdDev',
  src: Mat,
  mean: Mat,
  stddev: Mat,
  mask?: Mat
): void;
```

### merge

This is an overloaded member function, provided for convenience.

- mv input vector of matrices to be merged; all the matrices in mv must have the same size and the same depth
- dst output array of the same size and the same depth as mv[0]; The number of channels will be the total number of channels in the matrix array

```js
invoke(name: 'merge', mv: MatVector, dst: Mat): void;
```

### min

Calculates per-element minimum of two arrays or an array and a scalar

- src1 first input array
- src2 second input array of the same size and type as src1
- dst output array of the same size and type as src1

```js
invoke(name: 'min', src1: Mat, src2: Mat, dst: Mat): void;
```

### minMaxLoc

Finds the global minimum and maximum in an array

- src input single-channel array
- mask optional mask used to select a sub-array

```js
invoke(
  name: 'minMaxLoc',
  src: Mat,
  mask?: Mat
): { minVal: number; maxVal: number };
```


### mulSpectrums

Performs the per-element multiplication of two Fourier spectrums

- a first input array
- b second input array of the same size and type as src1
- c output array of the same size and type as src1 .
- flags operation flags; currently, the only supported flag is cv.DFT_ROWS, which indicates that each row of src1 and src2 is an independent 1D Fourier spectrum. If you do not want to use this flag, then simply add a 0 as value.
- conjB optional flag that conjugates the second input array before the multiplication (true) or not (false).

```js
invoke(
  name: 'mulSpectrums',
  a: Mat,
  b: Mat,
  c: Mat,
  flags: DftFlags,
  conjB?: boolean
): void;
```

### multiply

Calculates the per-element scaled product of two arrays

- src1 first input array
- src2 second input array of the same size and the same type as src1
- dst output array of the same size and type as src1
- scale optional scale factor
- dtype optional depth of the output array

```js
invoke(
  name: 'multiply',
  src1: Mat,
  src2: Mat,
  dst: Mat,
  scale: number,
  dtype?: DataTypes
): void;
```

### mulTransposed

Calculates the product of a matrix and its transposition

- src input single-channel matrix. Note that unlike gemm, the function can multiply not only floating-point matrices
- dst output square matrix
- aTa Flag specifying the multiplication ordering. See the description below
- delta Optional delta matrix subtracted from src before the multiplication. When the matrix is empty ( delta=noArray() ), it is assumed to be zero, that is, nothing is subtracted. If it has the same size as src , it is simply subtracted. Otherwise, it is "repeated" (see repeat ) to cover the full src and then subtracted. Type of the delta matrix, when it is not empty, must be the same as the type of created output matrix. See the dtype parameter description below
- scale Optional scale factor for the matrix product.
- dtype Optional type of the output matrix. When it is negative, the output matrix will have the same type as src

```js
invoke(
  name: 'mulTransposed',
  src: Mat,
  dst: Mat,
  aTa: boolean,
  delta: Mat,
  scale: number,
  dtype?: DataTypes
): void;
```

### norm

Calculates the absolute norm of an array

- src first input array
- normType type of the norm (see cv.NormTypes).
- mask optional operation mask; it must have the same size as src1 and CV_8UC1 type.
@returns the absolute norm of an array

```js
invoke(
  name: 'norm',
  src: Mat,
  normType: NormTypes,
  mask?: Mat
): { norm: number };
```

### normalize

Normalizes the norm or value range of an array.

- src input array
- dst output array of the same size as src
- alpha norm value to normalize to or the lower range boundary in case of the range normalization
- normType normalization type (see cv::NormTypes).

```js
invoke(
  name: 'normalize',
  src: Mat,
  dst: Mat,
  alpha: number,
  normType: NormTypes
): void;
```

### patchNaNs

converts NaNs to the given number

- a input/output matrix (CV_32F type).
- val value to convert the NaNs

```js
invoke(name: 'patchNaNs', a: Mat | MatVector, val: number): void;
```

### perspectiveTransform

Performs the perspective matrix transformation of vectors

- src input two-channel or three-channel floating-point array; each element is a 2D/3D vector to be transformed
- dst output array of the same size and type as src
- m 3x3 or 4x4 floating-point transformation matrix.

```js
invoke(name: 'perspectiveTransform', src: Mat, dst: Mat, m: Mat): void;
```

### phase

Calculates the rotation angle of 2D vectors

- x input floating-point array of x-coordinates of 2D vectors
- y input array of y-coordinates of 2D vectors; it must have the same size and the same type as x
- angle output array of vector angles; it has the same size and same type as x
- angleInDegrees when true, the function calculates the angle in degrees, otherwise, they are measured in radians

```js
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
```

### pow

Raises every array element to a power

- src input array
- power exponent of power
- dst output array of the same size and type as src

```js
invoke(name: 'pow', src: Mat, power: number, dst: Mat): void;
```

### PSNR

Computes the Peak Signal-to-Noise Ratio (PSNR) image quality metric

- src1 first input array
- src2 second input array of the same size as src1
- R the maximum pixel value (255 by default)
@returns the Peak Signal-to-Noise Ratio (PSNR) image quality metric in decibels (dB)

```js
invoke(name: 'PSNR', src1: Mat, src2: Mat, R: number): number;
```

### reduce

Reduces a matrix to a vector.

- src input 2D matrix
- dst output vector. Its size and type is defined by dim and dtype parameters
- dim dimension index along which the matrix is reduced. 0 means that the matrix is reduced to a single row. 1 means that the matrix is reduced to a single column
- rtype reduction operation that could be one of ReduceTypes
- dtype when negative, the output vector will have the same type as the input matrix, otherwise, its type will be CV_MAKE_TYPE(CV_MAT_DEPTH(dtype), src.channels())

```js
invoke(
  name: 'reduce',
  src: Mat,
  dst: Mat,
  dim: number,
  rtype: ReduceTypes,
  dtype: DataTypes
): void;
```

### repeat

Fills the output array with repeated copies of the input array

- src input array to replicate
- ny Flag to specify how many times the src is repeated along the vertical axis
- nx Flag to specify how many times the src is repeated along the horizontal axis
- dst output array of the same type as src.

```js
invoke(name: 'repeat', src: Mat, ny: number, nx: number, dst: Mat): void;
```

### scaleAdd

Calculates the sum of a scaled array and another array

- src1 first input array.
- alpha scale factor for the first array
- src2 second input array of the same size and type as src1
- dst output array of the same size and type as src1

```js
invoke(name: 'scaleAdd', src1: Mat, alpha: number, src2: Mat, dst: Mat): void;
```

### solve

Solves one or more linear systems or least-squares problems

- src1 input matrix on the left-hand side of the system
- src2 input matrix on the right-hand side of the system
- dst output solution
- flags solution (matrix inversion) method (DecompTypes)

```js
invoke(
  name: 'solve',
  src1: Mat,
  src2: Mat,
  dst: Mat,
  flags: DecompTypes
): { resolved: boolean };
```

### solveCubic

Finds the real roots of a cubic equation

- coeffs equation coefficients, an array of 3 or 4 elements
- roots output array of real roots that has 1 or 3 elements

```js
invoke(name: 'solveCubic', coeffs: Mat, roots: Mat): { value: boolean };
```

### solvePoly

Finds the real or complex roots of a polynomial equation

- src array of polynomial coefficients
- dst output (complex) array of roots
- maxIters maximum number of iterations the algorithm does

```js
invoke(name: 'solvePoly', src: Mat, dst: Mat, maxIters: number): number;
```

### sort

Sorts each row or each column of a matrix.

- src input single-channel array
- dst output array of the same size and type as src.
- flags operation flags, a combination of SortFlags

```js
invoke(name: 'sort', src: Mat, dst: Mat, flags: SortFlags): void;
```

### sortIdx

Sorts each row or each column of a matrix

- src input single-channel array
- dst output array of the same size and type as src.
- flags operation flags, a combination of SortFlags

```js
invoke(name: 'sortIdx', src: Mat, dst: Mat, flags: SortFlags): void;
```

### split

Divides a multi-channel array into several single-channel arrays

- src input multi-channel array.
- dst output vector of arrays; the arrays themselves are reallocated, if needed.

```js
invoke(name: 'split', src: Mat, dst: MatVector): void;
```

### sqrt

Calculates a square root of array elements

- src input floating-point array.
- dst output array of the same size and type as src

```js
invoke(name: 'sqrt', src: Mat, dst: Mat): void;
```

### subtract

- src1 first input array or a scalar
- src2 second input array or a scalar
- dst output array of the same size and the same number of channels as the input array
- mask optional operation mask; this is an 8-bit single channel array that specifies elements of the output array to be changed
- dtype optional depth of the output array

```js
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
```

### sum

Calculates the sum of array elements

- src input array that must have from 1 to 4 channels

```js
invoke(name: 'sum', src: MatVector | Mat): Scalar;
```

### trace

Returns the trace of a matrix

- mtx input matrix

```js
invoke(name: 'trace', mtx: Mat): Scalar;
```

### transform

Performs the matrix transformation of every array element

- src input array that must have as many channels (1 to 4) as m.cols or m.cols-1.
- dst output array of the same size and depth as src; it has as many channels as m.rows
- m transformation 2x2 or 2x3 floating-point matrix

```js
invoke(name: 'transform', src: Mat, dst: Mat, m: Mat): void;
```

### transpose

Transposes a matrix

- src input array.
- dst output array of the same type as src

```js
invoke(name: 'transpose', src: Mat, dst: Mat): void;
```

### vconcat

Applies vertical concatenation to given matrices

- src input array or vector of matrices. all of the matrices must have the same number of cols and the same depth
- dst output array. It has the same number of cols and depth as the src, and the sum of rows of the src. same depth

```js
invoke(name: 'vconcat', src: MatVector, dst: Mat): void;
```



## ColorConversion

### cvtColor
Converts an image from one color space to another.

- src input image: 8-bit unsigned, 16-bit unsigned ( CV_16UC... ), or single-precision floating-point.
- dst output image of the same size and depth as src.
- code color space conversion code.
- dstCn number of channels in the destination image; if the parameter is 0, the number of the channels is derived automatically from src and code.

```js
invoke(
  name: 'cvtColor',
  src: Mat,
  dst: Mat,
  code: ColorConversionCodes,
  dstCn?: number
): void;
```

### cvtColorTwoPlane

Converts an image from one color space to another where the source image is stored in two planes. This function only supports YUV420 to RGB conversion as of now.

- src1 8-bit image (CV_8U) of the Y plane.
- src2 image containing interleaved U/V plane.
- dst output image.
- code Specifies the type of conversion

```js
invoke(
  name: 'cvtColorTwoPlane',
  src1: Mat,
  src2: Mat,
  dst: Mat,
  code:
    | ColorConversionCodes.COLOR_YUV2BGR_NV12
    | ColorConversionCodes.COLOR_YUV2RGB_NV12
    | ColorConversionCodes.COLOR_YUV2BGRA_NV12
    | ColorConversionCodes.COLOR_YUV2RGBA_NV12
    | ColorConversionCodes.COLOR_YUV2BGR_NV21
    | ColorConversionCodes.COLOR_YUV2RGB_NV21
    | ColorConversionCodes.COLOR_YUV2BGRA_NV21
    | ColorConversionCodes.COLOR_YUV2RGBA_NV21
): void;
```

### demosaicing

main function for all demosaicing processes

- src input image: 8-bit unsigned or 16-bit unsigned.
- dst output image of the same size and depth as src.
- code Color space conversion code (see the description below).
- dstCn number of channels in the destination image

```js
invoke(
  name: 'demosaicing',
  src: Mat,
  dst: Mat,
  code:
    | ColorConversionCodes.COLOR_BayerBG2BGR
    | ColorConversionCodes.COLOR_BayerGB2BGR
    | ColorConversionCodes.COLOR_BayerRG2BGR
    | ColorConversionCodes.COLOR_BayerGR2BGR
    | ColorConversionCodes.COLOR_BayerBG2GRAY
    | ColorConversionCodes.COLOR_BayerGB2GRAY
    | ColorConversionCodes.COLOR_BayerRG2GRAY
    | ColorConversionCodes.COLOR_BayerGR2GRAY
    | ColorConversionCodes.COLOR_BayerBG2BGR_VNG
    | ColorConversionCodes.COLOR_BayerGB2BGR_VNG
    | ColorConversionCodes.COLOR_BayerRG2BGR_VNG
    | ColorConversionCodes.COLOR_BayerGR2BGR_VNG
    | ColorConversionCodes.COLOR_BayerBG2BGR_EA
    | ColorConversionCodes.COLOR_BayerGB2BGR_EA
    | ColorConversionCodes.COLOR_BayerRG2BGR_EA
    | ColorConversionCodes.COLOR_BayerGR2BGR_EA
    | ColorConversionCodes.COLOR_BayerBG2BGRA
    | ColorConversionCodes.COLOR_BayerGB2BGRA
    | ColorConversionCodes.COLOR_BayerRG2BGRA
    | ColorConversionCodes.COLOR_BayerGR2BGRA,
  dstCn?: number
): void;
```

## Imgproc – ColorMap

### applyColorMap

```js
invoke(
  name: 'applyColorMap',
  src: Mat,
  dst: Mat,
  colormap: ColormapTypes
): void;
```

## Imgproc – Drawing


### arrowedLine
Draws a arrow segment pointing from the first point to the second one.
- img Image
- pt1 The point the arrow starts from.
- pt2 The point the arrow points to.
- color Line color
- thickness Line thickness
- line_type Type of the line. See LineTypes

```js
invoke(
  name: 'arrowedLine',
  img: Mat,
  pt1: Point,
  pt2: Point,
  color: Scalar,
  thickness: number,
  line_type: LineTypes
): void;
```

### circle
Draws a circle.
- img Image where the circle is drawn.
- center Center of the circle.
- radius Radius of the circle.
- color Circle color.
- thickness Thickness of the circle outline, if positive. Negative values, like FILLED, mean that a filled circle is to be drawn

```js
invoke(
  name: 'circle',
  img: Mat,
  center: Point,
  radius: number,
  color: Scalar,
  thickness: number,
  line_type: LineTypes
): void;
```

### clipLine
Clips the line against the image rectangle. The function cv::clipLine calculates a part of the line segment that is entirely within the specified rectangle. it returns false if the line segment is completely outside the rectangle. Otherwise, it returns true .
- imgSize Image size
- pt1 First line point.
- pt2 Second line point.

```js
invoke(
  name: 'clipLine',
  imgSize: Size,
  pt1: Point,
  pt2: Point
): { value: boolean };
```

### drawContours
Draws contours outlines or filled contours. The function draws contour outlines in the image if 𝚝𝚑𝚒𝚌𝚔𝚗𝚎𝚜𝚜≥0 or fills the area bounded by the contours if 𝚝𝚑𝚒𝚌𝚔𝚗𝚎𝚜𝚜<0.
- image Destination image.
- contours All the input contours. Each contour is stored as a point vector
- contourIdx Parameter indicating a contour to draw. If it is negative, all the contours are drawn.
- color Color of the contours.
- thickness Thickness of lines the contours are drawn with. If it is negative (for example, thickness=FILLED ), the contour interiors are drawn
- lineType Line connectivity. See LineTypes

```js
invoke(
  name: 'drawContours',
  image: Mat,
  contours: MatVector,
  contourIdx: number,
  color: Scalar,
  thickness: number,
  lineType: LineTypes
): void;
```

### drawMarker
Draws a marker on a predefined position in an image.
- img Image
- position The point where the crosshair is positioned
- color Line color
- markerType The specific type of marker you want to use, see MarkerTypes
- markerSize Line thickness
- thickness Type of the line, See LineTypes
- line_type The length of the marker axis [default = 20 pixels]

```js
invoke(
  name: 'drawMarker',
  img: Mat,
  position: Point,
  color: Scalar,
  markerType: MarkerTypes,
  markerSize: number,
  thickness: number,
  line_type: LineTypes
): void;
```

### ellipse
Draws a simple or thick elliptic arc or fills an ellipse sector.
- img Image
- center Center of the ellipse
- axes Half of the size of the ellipse main axes
- angle Ellipse rotation angle in degrees
- startAngle Starting angle of the elliptic arc in degrees
- endAngle Ending angle of the elliptic arc in degrees
- color Ellipse color.
- thickness Thickness of the ellipse arc outline, if positive. Otherwise, this indicates that a filled ellipse sector is to be drawn
- lineType Type of the ellipse boundary. See LineTypes

```js
invoke(
  name: 'ellipse',
  img: Mat,
  center: Point,
  axes: Size,
  angle: number,
  startAngle: number,
  endAngle: number,
  color: Scalar,
  thickness: number,
  lineType: LineTypes
): void;
```

### fillConvexPoly
Fills a convex polygon.
- img Image
- pts Polygon vertices.
- color Polygon color
- lineType Type of the polygon boundaries. See LineTypes

```js
invoke(
  name: 'fillConvexPoly',
  img: Mat,
  pts: MatVector,
  color: Scalar,
  lineType: LineTypes
): void;
```

### fillPoly
Fills the area bounded by one or more polygons
- img Image
- pts Array of polygons where each polygon is represented as an array of points
- color Polygon colo
- lineType Type of the polygon boundaries. See LineTypes

```js
invoke(
  name: 'fillPoly',
  img: Mat,
  pts: MatVector,
  color: Scalar,
  lineType: LineTypes
): void;
```

### line
Draws a line segment connecting two points.
- img Image
- pt1 First point of the line segment
- pt2 Second point of the line segment
- color Line color
- thickness Line thickness
- lineType Type of the line. See LineTypes.

```js
invoke(
  name: 'line',
  img: Mat,
  pt1: Point,
  pt2: Point,
  color: Scalar,
  thickness: number,
  lineType: LineTypes
): void;
```

### polylines
Draws several polygonal curves
- img Image
- pts Array of polygonal curves.
- isClosed Flag indicating whether the drawn polylines are closed or not. If they are closed, the function draws a line from the last vertex of each curve to its first vertex
- color Polyline color
- thickness Thickness of the polyline edges
- lineType Type of the line segments. See LineTypes

```js
invoke(
  name: 'polylines',
  img: Mat,
  pts: MatVector,
  isClosed: boolean,
  color: Scalar,
  thickness: number,
  lineType: LineTypes
): void;
```

### rectangle
Draws a simple, thick, or filled up-right rectangle.
- img Image
- pt1 Vertex of the rectangle
- pt2 Vertex of the rectangle opposite to pt1
- color Rectangle color or brightness (grayscale image).
- thickness Thickness of lines that make up the rectangle. Negative values, like FILLED, mean that the function has to draw a filled rectangle
- lineType Type of the line. See LineTypes

```js
invoke(
  name: 'rectangle',
  img: Mat,
  pt1: Point,
  pt2: Point,
  color: Scalar,
  thickness: number,
  lineType: LineTypes
): void;
```

## Imgproc – Feature


### Canny
Finds edges in an image using the Canny algorithm
- name Function name.
- image 8-bit input image.
- edges output edge map; single channels 8-bit image, which has the same size as image
- threshold1 first threshold for the hysteresis procedure
- threshold2 second threshold for the hysteresis procedure
- apertureSize aperture size for the Sobel operator

```js
invoke(
  name: 'Canny',
  image: Mat,
  edges: Mat,
  threshold1: number,
  threshold2: number
): void;
```

### cornerHarris
Harris corner detector
- name Function name.
- src Input single-channel 8-bit or floating-point image.
- dst Image to store the Harris detector responses. It has the type CV_32FC1 and the same size as src
- blockSize Neighborhood size
- ksize Aperture parameter for the Sobel operator
- k Harris detector free parameter. See the formula above

```js
invoke(
  name: 'cornerHarris',
  src: Mat,
  dst: Mat,
  blockSize: number,
  ksize: number,
  k: number
): void;
```

### cornerMinEigenVal
Calculates the minimal eigenvalue of gradient matrices for corner detection
- name Function name.
- src Input single-channel 8-bit or floating-point image
- dst Image to store the minimal eigenvalues. It has the type CV_32FC1 and the same size as src
- blockSize Neighborhood size

```js
invoke(
  name: 'cornerMinEigenVal',
  src: Mat,
  dst: Mat,
  blockSize: number
): void;
```

### goodFeaturesToTrack
Determines strong corners on an image
- name Function name.
- image Input 8-bit or floating-point 32-bit, single-channel image
- corners Output vector of detected corners
- maxCorners Maximum number of corners to return. If there are more corners than are found, the strongest of them is returned. maxCorners <= 0 implies that no limit on the maximum is set and all detected corners are returned
- qualityLevel Parameter characterizing the minimal accepted quality of image corners. The parameter value is multiplied by the best corner quality measure, which is the minimal eigenvalue (see cornerMinEigenVal ) or the Harris function response (see cornerHarris ). The corners with the quality measure less than the product are rejected. For example, if the best corner has the quality measure = 1500, and the qualityLevel=0.01 , then all the corners with the quality measure less than 15 are rejected.
- minDistance Minimum possible Euclidean distance between the returned corners

```js
invoke(
  name: 'goodFeaturesToTrack',
  image: Mat,
  corners: Mat,
  maxCorners: number,
  qualityLevel: number,
  minDistance: number
): void;
```

### HoughCircles
Finds circles in a grayscale image using the Hough transform
- name Function name.
- image 8-bit, single-channel, grayscale input image.
- circles Output vector of found circles. Each vector is encoded as 3 or 4 element floating-point vector (x,y,radius) or (x,y,radius,votes)
- method Detection method, see HoughModes. The available methods are HOUGH_GRADIENT and HOUGH_GRADIENT_ALT.
- dp Inverse ratio of the accumulator resolution to the image resolution. For example, if dp=1 , the accumulator has the same resolution as the input image. If dp=2 , the accumulator has half as big width and height. For HOUGH_GRADIENT_ALT the recommended value is dp=1.5, unless some small very circles need to be detected
- minDist Minimum distance between the centers of the detected circles. If the parameter is too small, multiple neighbor circles may be falsely detected in addition to a true one. If it is too large, some circles may be missed this two parameter will be helpful to increase the accuracy of the circle detection this two parameter are also available in opencv original documentation
- param1 it is the higher threshold of the two passed to the Canny edge detector (the lower canny threshold is twice smaller)
- param2 it is the accumulator threshold for the circle centers at the detection stage as discussed above.

```js
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
```

### HoughLines
Finds lines in a binary image using the standard Hough transform
- name Function name.
- image 8-bit, single-channel binary source image. The image may be modified by the function.
- lines Output vector of lines. Each line is represented by a 2 or 3 element vector (ρ,θ) or (ρ,θ,votes) . ρ is the distance from the coordinate origin (0,0) (top-left corner of the image). θ is the line rotation angle in radians ( 0∼vertical line,π/2∼horizontal line ). votes is the value of accumulator
- rho Distance resolution of the accumulator in pixels
- theta Angle resolution of the accumulator in radians
- threshold Accumulator threshold parameter. Only those lines are returned that get enough votes ( >𝚝𝚑𝚛𝚎𝚜𝚑𝚘𝚕𝚍 ).

```js
invoke(
  name: 'HoughLines',
  image: Mat,
  lines: Mat,
  rho: number,
  theta: number,
  threshold: number
): void;
```

### HoughLinesP
Finds line segments in a binary image using the probabilistic Hough transform
- name Function name.
- image 8-bit, single-channel binary source image. The image may be modified by the function.
- lines Output vector of lines. Each line is represented by a 2 or 3 element vector (ρ,θ) or (ρ,θ,votes) . ρ is the distance from the coordinate origin (0,0) (top-left corner of the image). θ is the line rotation angle in radians ( 0∼vertical line,π/2∼horizontal line ). votes is the value of accumulator
- rho Distance resolution of the accumulator in pixels
- theta Angle resolution of the accumulator in radians
- threshold Accumulator threshold parameter. Only those lines are returned that get enough votes ( >𝚝𝚑𝚛𝚎𝚜𝚑𝚘𝚕𝚍 ).

```js
invoke(
  name: 'HoughLinesP',
  image: Mat,
  lines: Mat,
  rho: number,
  theta: number,
  threshold: number
): void;
```


## Imgproc – Image Filtering


### bilateralFilter
Applies the bilateral filter to an image.
- src Source 8-bit or floating-point, 1-channel or 3-channel image.
- dst Destination image of the same size and type as src .
- d Diameter of each pixel neighborhood that is used during filtering. If it is non-positive, it is computed from sigmaSpace.
- sigmaColor Filter sigma in the color space. A larger value of the parameter means that farther colors within the pixel neighborhood (see sigmaSpace) will be mixed together, resulting in larger areas of semi-equal color.
- sigmaSpace Filter sigma in the coordinate space. A larger value of the parameter means that farther pixels will influence each other as long as their colors are close enough (see sigmaColor ). When d>0, it specifies the neighborhood size regardless of sigmaSpace. Otherwise, d is proportional to sigmaSpace.
- borderType border mode used to extrapolate pixels outside of the image, see BorderTypes

```js
invoke(
  name: 'bilateralFilter',
  src: Mat,
  dst: Mat,
  d: number,
  sigmaColor: number,
  sigmaSpace: number,
  borderType: BorderTypes
): void;
```

### blur
- src input image; it can have any number of channels, which are processed independently, but the depth should be CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
- dst output image of the same size and type as src.
- ksize blurring kernel size.
- anchor anchor point; default value Point(-1,-1) means that the anchor is at the kernel center.
- borderType border mode used to extrapolate pixels outside of the image, see BorderTypes. BORDER_WRAP is not supported.

```js
invoke(
  name: 'blur',
  src: Mat,
  dst: Mat,
  ksize: Size,
  anchor: Point,
  borderType: BorderTypes
): void;
```

### boxFilter
Blurs an image using the box filter.
- src input image.
- dst output image of the same size and type as src.
- ddepth the output image depth (-1 to use src.depth()).
- ksize blurring kernel size.
- anchor anchor point; default value Point(-1,-1) means that the anchor is at the kernel center.
- normalize flag, specifying whether the kernel is normalized by its area or not.
- borderType border mode used to extrapolate pixels outside of the image, see BorderTypes. BORDER_WRAP is not supported.

```js
invoke(
  name: 'boxFilter',
  src: Mat,
  dst: Mat,
  ddepth: DataTypes,
  ksize: Size,
  anchor: Point,
  normalize: boolean,
  borderType: BorderTypes
): void;
```

### buildPyramid
Constructs the Gaussian pyramid for an image.
- src Source image. Check pyrDown for the list of supported types.
- dst Destination vector of maxlevel+1 images of the same type as src. dst[0] will be the same as src. dst[1] is the next pyramid layer, a smoothed and down-sized src, and so on.
- maxlevel 0-based index of the last (the smallest) pyramid layer. It must be non-negative.
- borderType Pixel extrapolation method, see BorderTypes (BORDER_CONSTANT isn't supported)

```js
invoke(
  name: 'buildPyramid',
  src: Mat,
  dst: Mat,
  maxlevel: number,
  borderType: BorderTypes
): void;
```

### dilate
Dilates an image by using a specific structuring element.
- src input image; the number of channels can be arbitrary, but the depth should be one of CV_8U, CV_16U, CV_16S, CV_32F or CV_64F
- dst output image of the same size and type as src.
- kernel structuring element used for dilation; if elemenat=Mat(), a 3 x 3 rectangular structuring element is used. Kernel can be created using getStructuringElement
- anchor position of the anchor within the element; default value (-1, -1) means that the anchor is at the element center.
- iterations number of times dilation is applied.
- borderType pixel extrapolation method, see BorderTypes. BORDER_WRAP is not suported.
- borderValue border value in case of a constant border

```js
invoke(
  name: 'dilate',
  src: Mat,
  dst: Mat,
  kernel: Mat,
  anchor: Point,
  iterations: number,
  borderType: BorderTypes,
  borderValue: Scalar
): void;
```

### erode
Erodes an image by using a specific structuring element.
- src input image; the number of channels can be arbitrary, but the depth should be one of CV_8U, CV_16U, CV_16S, CV_32F or CV_64F
- dst output image of the same size and type as src.
- kernel structuring element used for dilation; if elemenat=Mat(), a 3 x 3 rectangular structuring element is used. Kernel can be created using getStructuringElement
- anchor position of the anchor within the element; default value (-1, -1) means that the anchor is at the element center.
- iterations number of times dilation is applied.
- borderType pixel extrapolation method, see BorderTypes. BORDER_WRAP is not suported.
- borderValue border value in case of a constant border

```js
invoke(
  name: 'erode',
  src: Mat,
  dst: Mat,
  kernel: Mat,
  anchor: Point,
  iterations: number,
  borderType: BorderTypes,
  borderValue: Scalar
): void;
```

### filter2D
Convolves an image with the kernel.
- src input image.
- dst output image of the same size and the same number of channels as src.
- ddepth desired depth of the destination image
- kernel convolution kernel (or rather a correlation kernel), a single-channel floating point matrix; if you want to apply different kernels to different channels, split the image into separate color planes using split and process them individually.
- anchor anchor of the kernel that indicates the relative position of a filtered point within the kernel; the anchor should lie within the kernel; default value (-1,-1) means that the anchor is at the kernel center.
- delat optional value added to the filtered pixels before storing them in dst.
- borderType pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.

```js
invoke(
  name: 'filter2D',
  src: Mat,
  dst: Mat,
  ddepth: DataTypes,
  kernel: Mat,
  anchor: Point,
  delat: number,
  borderType: BorderTypes
): void;
```

### GaussianBlur
Blurs an image using a Gaussian filter.
- src input image; the image can have any number of channels, which are processed independently, but the depth should be CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
- dst output image of the same size and type as src.
- ksize Gaussian kernel size. ksize.width and ksize.height can differ but they both must be positive and odd. Or, they can be zero's and then they are computed from sigma.
- sigmaX Gaussian kernel standard deviation in X direction.
- sigmaY Gaussian kernel standard deviation in Y direction; if sigmaY is zero, it is set to be equal to sigmaX, if both sigmas are zeros, they are computed from ksize.width and ksize.height, respectively (see getGaussianKernel for details); to fully control the result regardless of possible future modifications of all this semantics, it is recommended to specify all of ksize, sigmaX, and sigmaY.
- borderType pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.

```js
invoke(
  name: 'GaussianBlur',
  src: Mat,
  dst: Mat,
  ksize: Size,
  sigmaX: number,
  sigmaY: number,
  borderType: BorderTypes
): void;
```

### getGaborKernel

- ksize Size of the filter returned.
- sigma Standard deviation of the gaussian envelope.
- theta Orientation of the normal to the parallel stripes of a Gabor function.
- lambd Wavelength of the sinusoidal factor.
- gamma Spatial aspect ratio.
- psi Phase offset.
- ktype Type of filter coefficients. It can be CV_32F or CV_64F .

```js
invoke(
  name: 'getGaborKernel',
  ksize: Size,
  sigma: number,
  theta: number,
  lambd: number,
  gamma: number,
  psi: number,
  ktype: DataTypes.CV_32F | DataTypes.CV_64F
): Mat;
```

### getGaussianKernel
Returns Gaussian filter coefficients.
- ksize Aperture size. It should be odd ( 𝚔𝚜𝚒𝚣𝚎mod2=1 ) and positive.
- sigma Gaussian standard deviation. If it is non-positive, it is computed from ksize as sigma = 0.3*((ksize-1)*0.5 - 1) + 0.8.
- ktype Type of filter coefficients. It can be CV_32F or CV_64F .

```js
invoke(
  name: 'getGaussianKernel',
  ksize: number,
  sigma: number,
  ktype: DataTypes.CV_32F | DataTypes.CV_64F
): Mat;
```

### Laplacian
Calculates the Laplacian of an image.
- name Function name.
- src Source image.
- dst Destination image of the same size and the same number of channels as src .
- ddepth Desired depth of the destination image.
- ksize Aperture size used to compute the second-derivative filters. See getDerivKernels for details. The size must be positive and odd.
- scale Optional scale factor for the computed Laplacian values. By default, no scaling is applied. See getDerivKernels for details.
- delta Optional delta value that is added to the results prior to storing them in dst
- borderType Pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.

```js
invoke(
  name: 'Laplacian',
  src: Mat,
  dst: Mat,
  ddepth: DataTypes,
  ksize: number,
  scale: number,
  delta: number,
  borderType: BorderTypes
): void;
```

### medianBlur
Blurs an image using the median filter.
The function smoothes an image using the median filter with the 𝚔𝚜𝚒𝚣𝚎×𝚔𝚜𝚒𝚣𝚎 aperture. Each channel of a multi-channel image is processed independently. In-place operation is supported.
- name Function name.
- src input 1-, 3-, or 4-channel image; when ksize is 3 or 5, the image depth should be CV_8U, CV_16U, or CV_32F, for larger aperture sizes, it can only be CV_8U.
- dst destination array of the same size and type as src.
- ksize aperture linear size; it must be odd and greater than 1, for example: 3, 5, 7 ...

```js
invoke(name: 'medianBlur', src: Mat, dst: Mat, ksize: number): void;
```

### morphologyEx
Performs advanced morphological transformations.
The function cv::morphologyEx can perform advanced morphological transformations using an erosion and dilation as basic operations.
Any of the operations can be done in-place. In case of multi-channel images, each channel is processed independently.
- name Function name.
- src Source image. The number of channels can be arbitrary. The depth should be one of CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
- dst Destination image of the same size and type as source image.
- op Type of a morphological operation, see MorphTypes
- kernel Structuring element. It can be created using getStructuringElement.
- anchor Anchor position with the kernel. Negative values mean that the anchor is at the kernel center.
- iterations Number of times erosion and dilation are applied.
- borderType Pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.
- borderValue Border value in case of a constant border. The default value has a special meaning.

```js
invoke(
  name: 'morphologyEx',
  src: Mat,
  dst: Mat,
  op: MorphTypes,
  kernel: Mat,
  anchor: Point,
  iterations: number,
  borderType: BorderTypes,
  borderValue: Scalar
): void;
```


## Imgproc – Misc


### adaptiveThreshold
Applies an adaptive threshold to an array
- name Function name.
- src Source 8-bit single-channel image.
- dst Destination image of the same size and the same type as src
- maxValue Non-zero value assigned to the pixels for which the condition is satisfied
- adaptiveMethod Adaptive thresholding algorithm to use, @see AdaptiveThresholdTypes. The BORDER_REPLICATE | BORDER_ISOLATED is used to process boundaries
- thresholdType Thresholding type that must be either THRESH_BINARY or THRESH_BINARY_INV, @see ThresholdTypes.
- blockSize Size of a pixel neighborhood that is used to calculate a threshold value for the pixel: 3, 5, 7, and so on.
- C Constant subtracted from the mean or weighted mean (@see the details below). Normally, it is positive but may be zero or negative as well)

```js
invoke(
  name: 'adaptiveThreshold',
  src: Mat,
  dst: Mat,
  maxValue: number,
  adaptiveMethod: AdaptiveThresholdTypes,
  thresholdType:
    | ThresholdTypes.THRESH_BINARY
    | ThresholdTypes.THRESH_BINARY_INV,
  blockSize: number,
  C: number
): void;
```

### distanceTransform
Calculates the distance to the closest zero pixel for each pixel of the source image
- name Function name.
- src 	8-bit, single-channel (binary) source image
- dst Output image with calculated distances. It is a 8-bit or 32-bit floating-point, single-channel image of the same size as src
- distanceType Type of distance, @see DistanceTypes
- maskSize Size of the distance transform mask, @see DistanceTransformMasks. In case of the DIST_L1 or DIST_C distance type, the parameter is forced to 3 because a 3×3 mask gives the same result as 5×5 or any larger aperture.

```js 
invoke(
  name: 'distanceTransform',
  src: Mat,
  dst: Mat,
  distanceType: DistanceTypes,
  maskSize: DistanceTransformMasks
): void;
```

### integral
Calculates the integral of an image
- name Function name.
- src input image as W×H, 8-bit or floating-point (32f or 64f).
- sum integral image as (W+1)×(H+1) , 32-bit integer or floating-point (32f or 64f).

```js
invoke(name: 'integral', src: Mat, sum: Mat): void;
```

### threshold
Applies a fixed-level threshold to each array element
- name Function name.
- src input array (multiple-channel, 8-bit or 32-bit floating point).
- dst output array of the same size and type and the same number of channels as src.
- thresh threshold value
- maxval maximum value to use with the THRESH_BINARY and THRESH_BINARY_INV thresholding types
- type thresholding type (@see ThresholdTypes).

```js
invoke(
  name: 'threshold',
  src: Mat,
  dst: Mat,
  thresh: number,
  maxval: number,
  type: number
): void;
```


## Imgproc – Object Detection


### matchTemplate
Compares a template against overlapped image regions
- image Image where the search is running. It must be 8-bit or 32-bit floating-point
- templ Searched template. It must be not greater than the source image and have the same data type.
- result Map of comparison results. It must be single-channel 32-bit floating-point. If image is W×H and templ is w×h , then result is (W−w+1)×(H−h+1) .
- method Parameter specifying the comparison method, @see TemplateMatchModes
- mask Mask of searched template. It must have the same datatype and size with templ. It is not set by default. Currently, only the TM_SQDIFF and TM_CCORR_NORMED methods are supported

```js
invoke(
  name: 'matchTemplate',
  image: Mat,
  templ: Mat,
  result: Mat,
  method: TemplateMatchModes,
  mask: Mat
): void;
```

## Imgproc – Shape


### approxPolyDP
Approximates a polygonal curve(s) with the specified precision
- curve Input vector of a 2D point stored in std::vector or Mat
- approxCurve Result of the approximation. The type should match the type of the input curve
- epsilonParameter specifying the approximation accuracy. This is the maximum distance between the original curve and its approximation
- closed If true, the approximated curve is closed (its first and last vertices are connected). Otherwise, it is not closed

```js
invoke(
  name: 'approxPolyDP',
  curve: Mat | MatVector,
  approxCurve: Mat,
  epsilon: number,
  closed: boolean
): void;
```

### arcLength
Calculates a contour perimeter or a curve length.
- curve Input vector of 2D points, stored in std::vector or Mat.
- closed Flag indicating whether the curve is closed or not.
@returns a curve length or a closed contour perimeter.

```js
invoke(
  name: 'arcLength',
  curve: Mat | MatVector,
  closed: boolean
): { value: number };
```

### boundingRect
Calculates the up-right bounding rectangle of a point set or non-zero pixels of gray-scale image.
- array Input gray-scale image or 2D point set, stored in std::vector or Mat.
@returns the minimal up-right bounding rectangle for the specified point set or non-zero pixels of gray-scale image

```js
invoke(name: 'boundingRect', array: Mat | MatVector): Rect;
```

### connectedComponents
computes the connected components labeled image of boolean image
- image the 8-bit single-channel image to be labeled
- labels destination labeled image
@returns N, the total number of labels [0, N-1] where 0 represents the background label

```js
invoke(
  name: 'connectedComponents',
  image: Mat,
  labels: Mat
): { value: number };
```

### connectedComponentsWithStats
computes the connected components labeled image of boolean image and also produces a statistics output for each label
- image the 8-bit single-channel image to be labeled
- labels destination labeled image
- stats statistics output for each label, including the background label. Statistics are accessed via stats(label, COLUMN) where COLUMN is one of ConnectedComponentsTypes, selecting the statistic. The data type is CV_32S.
- centroids centroid output for each label, including the background label. Centroids are accessed via centroids(label, 0) for x and centroids(label, 1) for y. The data type CV_64F
@returns N, the total number of labels [0, N-1] where 0 represents the background label

```js
invoke(
  name: 'connectedComponentsWithStats',
  image: Mat,
  labels: Mat,
  stats: Mat,
  centroids: Mat
): { value: number };
```

### contourArea
Calculates a contour area
- contour Input vector of 2D points (contour vertices), stored in std::vector or Mat.
- oriented Oriented area flag. If it is true, the function returns a signed area value, depending on the contour orientation (clockwise or counter-clockwise). Using this feature you can determine orientation of a contour by taking the sign of an area. By default, the parameter is false, which means that the absolute value is returned
@returns area and the number of non-zero pixels,

```js
invoke(
  name: 'contourArea',
  contour: Mat | MatVector,
  oriented?: boolean
): { value: number };
```

### convexHull
Finds the convex hull of a point set.
- points Input 2D point set, stored in std::vector or Mat.
- hull Output convex hull. It is either an integer vector of indices or vector of points. In the first case, the hull elements are 0-based indices of the convex hull points in the original array (since the set of convex hull points is a subset of the original point set). In the second case, hull elements are the convex hull points themselves

```js
invoke(name: 'convexHull', points: Mat, hull: Mat): void;
```

### convexityDefects
Finds the convexity defects of a contour.
- contour Input contour
- convexHull Convex hull obtained using convexHull that should contain indices of the contour points that make the hull
- convexityDefects  output vector of convexity defects. In C++ and the new Python/Java interface each convexity defect is represented as 4-element integer vector (a.k.a. Vec4i): (start_index, end_index, farthest_pt_index, fixpt_depth), where indices are 0-based indices in the original contour of the convexity defect beginning, end and the farthest point, and fixpt_depth is fixed-point approximation (with 8 fractional bits) of the distance between the farthest contour point and the hull. That is, to get the floating-point value of the depth will be fixpt_depth/256.0.

```js
invoke(
  name: 'convexityDefects',
  contour: Mat,
  convexHull: Mat,
  convexityDefects: Mat
): void;
```

### findContours
Finds contours in a binary image
- image Source, an 8-bit single-channel image. Non-zero pixels are treated as 1s. Zero pixels remain 0s, so the image is treated as binary . You can use compare, inRange, threshold , adaptiveThreshold, Canny, and others to create a binary image out of a grayscale or color one. If mode equals to RETR_CCOMP or RETR_FLOODFILL, the input can also be a 32-bit integer image of labels (CV_32SC1).
- contours Detected contours. Each contour is stored as a vector of points
- mode Contour retrieval mode, @see RetrievalModes
- method Contour approximation method, @see ContourApproximationModes

```js
invoke(
  name: 'findContours',
  image: Mat | MatVector,
  contours: Mat | MatVector,
  mode: RetrievalModes,
  method: ContourApproximationModes
): void;
```

### fitLine
Fits a line to a 2D or 3D point set.
- points Input vector of 2D or 3D points, stored in a Mat.
- line Output line parameters. In case of 2D fitting, it should be a vector of 4 elements (like Vec4f) - (vx, vy, x0, y0), where (vx, vy) is a normalized vector collinear to the line and (x0, y0) is a point on the line. In case of 3D fitting, it should be a vector of 6 elements (like Vec6f) - (vx, vy, vz, x0, y0, z0), where (vx, vy, vz) is a normalized vector collinear to the line and (x0, y0, z0) is a point on the line
- disType Distance used by the M-estimator, @see DistanceTypes
- param Numerical parameter ( C ) for some types of distances. If it is 0, an optimal value is chosen.
- reps Sufficient accuracy for the radius (distance between the coordinate origin and the line).
- aeps Sufficient accuracy for the angle. 0.01 would be a good default value for reps and aeps.

```js
invoke(
  name: 'fitLine',
  points: Mat,
  line: Mat,
  disType: DistanceTypes,
  param: number,
  reps: number,
  aeps: number
): void;
```

### isContourConvex
Tests a contour convexity.
- contour
@returns whether the input contour is convex or not

```js
invoke(name: 'isContourConvex', contour: Mat): boolean;
```

### matchShapes
Compares two shapes
- contour1 First contour or grayscale image
- contour2 Second contour or grayscale image
- method Comparison method, @see ShapeMatchModes
- parameter Method-specific parameter (not supported now).
@returns

```js
invoke(
  name: 'matchShapes',
  contour1: Mat,
  contour2: Mat,
  method: ShapeMatchModes,
  parameter: number
): number;
```

### minAreaRect
Finds a rotated rectangle of the minimum area enclosing the input 2D point set.
- points Input vector of 2D points, stored in a Mat
@returns the minimum-area bounding rectangle (possibly rotated) for a specified point set

```js
invoke(name: 'minAreaRect', points: Mat): RotatedRect;
```