import { AlphaType, ColorType, Skia } from '@shopify/react-native-skia';
import { useEffect } from 'react';
import { StyleSheet, Text } from 'react-native';
import {
  OpenCV,
  DataTypes,
  Mat,
  ColorConversionCodes,
  RotateFlags,
} from 'react-native-fast-opencv';
import {
  useCameraDevice,
  useCameraPermission,
} from 'react-native-vision-camera';
import { SkiaCamera } from 'react-native-vision-camera-skia';
import { useResizer, type GPUFrame } from 'react-native-vision-camera-resizer';

const WIDTH = 300;
const HEIGHT = 300;

export function CameraPassthrough() {
  const device = useCameraDevice('back');
  const { hasPermission, requestPermission } = useCameraPermission();

  const { resizer } = useResizer({
    width: WIDTH,
    height: HEIGHT,
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
      style={styles.container}
      device={device}
      isActive={true}
      orientationSource="device"
      onFrame={(frame, render) => {
        'worklet';

        if (resizer == null) return;

        const resized = resizer.resize(frame) as GPUFrame;
        const pixels = new Uint8Array(resized.getPixelBuffer());

        const src = Mat.createFromBuffer('uint8', HEIGHT, WIDTH, 3, pixels);
        const dst = Mat.create(0, 0, DataTypes.CV_8U);
        OpenCV.cvtColor(src, src, ColorConversionCodes.COLOR_BGR2HLS);
        OpenCV.cvtColor(src, dst, ColorConversionCodes.COLOR_BGR2RGBA);
        OpenCV.rotate(dst, dst, RotateFlags.ROTATE_90_CLOCKWISE);

        const output = dst.toBuffer('uint8');
        const data = Skia.Data.fromBytes(output.buffer);
        const image = Skia.Image.MakeImage(
          {
            width: WIDTH,
            height: HEIGHT,
            alphaType: AlphaType.Opaque,
            colorType: ColorType.RGBA_8888,
          },
          data,
          WIDTH * 4
        );

        render(({ canvas, frameTexture }) => {
          canvas.drawImage(frameTexture, 0, 0);

          if (image) {
            const paint = Skia.Paint();
            paint.setColor(Skia.Color('red'));
            paint.setStyle(1);
            paint.setStrokeWidth(2);

            const x = (frame.width - WIDTH) / 2;
            const y = frame.height - HEIGHT - 50;

            canvas.drawImage(image, x, y);
            canvas.drawRect({ x, y, width: WIDTH, height: HEIGHT }, paint);

            image.dispose();
          }
        });

        data.dispose();
        resized.dispose();
        frame.dispose();
      }}
    />
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
});
