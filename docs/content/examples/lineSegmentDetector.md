# Detect line segments

Open **Line Segment Detector** in the example app, select a photo, then tap **Process**. Detected segments are drawn in red.

### Code

```ts
import {
  ColorConversionCodes,
  DataTypes,
  Mat,
  OpenCV,
} from 'react-native-fast-opencv';

// gray is a CV_8UC1 grayscale Mat.
const lines = Mat.create(0, 0, DataTypes.CV_32FC4);
const result = Mat.create(0, 0, DataTypes.CV_8UC3);
const detector = OpenCV.createLineSegmentDetector();

try {
  detector.detect(gray, lines);
  OpenCV.cvtColor(gray, result, ColorConversionCodes.COLOR_GRAY2BGR);
  detector.drawSegments(result, lines);
  const image = result.toBase64();
} finally {
  detector.release();
  lines.release();
  result.release();
}
```

`detect` writes endpoints `(x1, y1, x2, y2)` into `lines`. Pass optional `Mat` outputs for width, precision, or false-alarm scores. Scores require a detector created with `LineSegmentDetectorModes.LSD_REFINE_ADV`.

`drawSegments` changes the image in place. `compareSegments(size, lines1, lines2)` returns the number of mismatching pixels, or `0` for identical line sets.
