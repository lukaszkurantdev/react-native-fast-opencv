# Enhance contrast with CLAHE

CLAHE improves local contrast in grayscale images. Open **CLAHE** in the example app, select a photo, then tap **Process** to compare the grayscale image with the result.

### Code

```ts
import { DataTypes, Mat, OpenCV, Size } from 'react-native-fast-opencv';

// src is a single-channel CV_8UC1 or CV_16UC1 Mat.
const dst = Mat.create(0, 0, DataTypes.CV_8UC1);
const grid = Size.create(8, 8);
const clahe = OpenCV.createCLAHE(2.0, grid);

try {
  clahe.apply(src, dst);
  const image = dst.toBase64();

  // Reuse the instance with a different clip limit.
  clahe.setClipLimit(4.0);
  clahe.apply(src, dst);
} finally {
  clahe.release();
  grid.release();
  dst.release();
}
```

Convert color images to grayscale before calling `apply`. Grid width and height are the number of tiles, not pixels.

Use `getClipLimit()`, `getTilesGridSize()`, and `setTilesGridSize(size)` to read or change the settings. Release the `Size` returned by `getTilesGridSize()` when finished.

`collectGarbage()` clears cached buffers while keeping the instance. Call `release()` when you no longer need it.
