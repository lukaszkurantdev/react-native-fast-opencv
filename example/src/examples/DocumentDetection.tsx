import { PaintStyle, Skia, StrokeJoin } from '@shopify/react-native-skia';
import { useEffect } from 'react';
import { StyleSheet, Text } from 'react-native';
import {
  OpenCV,
  ColorConversionCodes,
  MorphShapes,
  MorphTypes,
  RetrievalModes,
  ContourApproximationModes,
  PointVectorOfVectors,
  PointVector,
  Mat,
  type Point,
} from 'react-native-fast-opencv';
import {
  useCameraDevice,
  useCameraPermission,
} from 'react-native-vision-camera';
import { SkiaCamera } from 'react-native-vision-camera-skia';
import { useResizer, type GPUFrame } from 'react-native-vision-camera-resizer';

const paint = Skia.Paint();
paint.setStyle(PaintStyle.Fill);
paint.setColor(Skia.Color('red'));
paint.setAlphaf(0.4);

const border = Skia.Paint();
border.setStyle(PaintStyle.Stroke);
border.setColor(Skia.Color('red'));
border.setStrokeWidth(5);
border.setStrokeJoin(StrokeJoin.Round);

const RESIZER_WIDTH = 320;
const RESIZER_HEIGHT = 180;

export function DocumentDetection() {
  const device = useCameraDevice('back');
  const { hasPermission, requestPermission } = useCameraPermission();

  const { resizer } = useResizer({
    width: RESIZER_WIDTH,
    height: RESIZER_HEIGHT,
    channelOrder: 'bgr',
    dataType: 'uint8',
    pixelLayout: 'interleaved',
    scaleMode: 'cover',
  });

  useEffect(() => {
    requestPermission();
  }, [requestPermission]);

  if (!hasPermission) {
    return <Text>No permission</Text>;
  }

  if (device == null) {
    return <Text>No device</Text>;
  }

  return (
    <SkiaCamera
      style={StyleSheet.absoluteFill}
      device={device}
      isActive={true}
      orientationSource="interface"
      onFrame={(frame, render) => {
        'worklet';

        if (resizer == null) return;

        const resized = resizer.resize(frame) as GPUFrame;
        const width = resized.width;
        const height = resized.height;

        const pixels = new Uint8Array(resized.getPixelBuffer());
        const source = Mat.createFromBuffer('uint8', height, width, 3, pixels);

        OpenCV.cvtColor(source, source, ColorConversionCodes.COLOR_BGR2GRAY);

        const kernel = OpenCV.Size.create(4, 4);
        const structuringElement = OpenCV.getStructuringElement(
          MorphShapes.MORPH_ELLIPSE,
          kernel
        );

        OpenCV.morphologyEx(
          source,
          source,
          MorphTypes.MORPH_OPEN,
          structuringElement
        );
        OpenCV.morphologyEx(
          source,
          source,
          MorphTypes.MORPH_CLOSE,
          structuringElement
        );
        OpenCV.Canny(source, source, 75, 100);

        const contours = PointVectorOfVectors.create();

        OpenCV.findContours(
          source,
          contours,
          RetrievalModes.RETR_LIST,
          ContourApproximationModes.CHAIN_APPROX_SIMPLE
        );

        let greatestPolygon: PointVector | undefined;
        let greatestArea = 0;

        for (let index = 0; index < contours.length; index++) {
          const contour = contours.get(index);
          const { value: area } = OpenCV.contourArea(contour, false);

          if (area > 2000 && area > greatestArea) {
            const peri = OpenCV.arcLength(contour, true);
            const approx = PointVector.create();

            OpenCV.approxPolyDP(contour, approx, 0.1 * peri.value, true);

            greatestPolygon = approx;
            greatestArea = area;
          }
        }

        render(({ canvas, frameTexture }) => {
          canvas.drawImage(frameTexture, 0, 0);

          if (greatestPolygon) {
            const points: Point[] = greatestPolygon.getAll();

            if (points.length === 4) {
              const path = Skia.Path.Make();

              const scaleToCanvasX = frame.width / RESIZER_HEIGHT;
              const scaleToCanvasY = frame.height / RESIZER_WIDTH;

              const mapPointX = (p: Point) =>
                (RESIZER_HEIGHT - p.y) * scaleToCanvasX;
              const mapPointY = (p: Point) => p.x * scaleToCanvasY;

              const p0x = mapPointX(points[0]!);
              const p0y = mapPointY(points[0]!);
              const p1x = mapPointX(points[1]!);
              const p1y = mapPointY(points[1]!);
              const p2x = mapPointX(points[2]!);
              const p2y = mapPointY(points[2]!);
              const p3x = mapPointX(points[3]!);
              const p3y = mapPointY(points[3]!);

              path.moveTo(p3x, p3y);
              path.lineTo(p0x, p0y);
              path.lineTo(p1x, p1y);
              path.lineTo(p2x, p2y);
              path.close();

              canvas.drawPath(path, paint);
              canvas.drawPath(path, border);
            }
          }
        });

        resized.dispose();
        frame.dispose();
      }}
    />
  );
}
