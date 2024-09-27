import {
  AlphaType,
  Canvas,
  ColorType,
  Image,
  Skia,
  type SkData,
  type SkImage,
} from '@shopify/react-native-skia';
import { useEffect } from 'react';
import { SafeAreaView, StyleSheet, Text, View } from 'react-native';
import { DataTypes, ObjectType, OpenCV } from 'react-native-fast-opencv';
import { useSharedValue } from 'react-native-reanimated';
import {
  Camera,
  useCameraDevice,
  useCameraPermission,
  useFrameProcessor,
} from 'react-native-vision-camera';
import { useRunOnJS } from 'react-native-worklets-core';
import { useResizePlugin, type Options } from 'vision-camera-resize-plugin';

type PixelFormat = Options<'uint8'>['pixelFormat'];

const WIDTH = 300;
const HEIGHT = 300;
const TARGET_TYPE = 'uint8' as const;
const TARGET_FORMAT: PixelFormat = 'rgba';

let lastWarn: PixelFormat | undefined;
lastWarn = undefined;
function warnNotSupported(pixelFormat: PixelFormat) {
  if (lastWarn !== pixelFormat) {
    console.log(
      `Pixel Format '${pixelFormat}' is not natively supported by Skia! ` +
        `Displaying a fall-back format that might use wrong colors instead...`
    );
    lastWarn = pixelFormat;
  }
}

function getSkiaTypeForPixelFormat(pixelFormat: PixelFormat): ColorType {
  switch (pixelFormat) {
    case 'abgr':
    case 'argb':
      warnNotSupported(pixelFormat);
      return ColorType.RGBA_8888;
    case 'bgr':
      warnNotSupported(pixelFormat);
      return ColorType.RGB_888x;
    case 'rgb':
      return ColorType.RGB_888x;
    case 'rgba':
      return ColorType.RGBA_8888;
    case 'bgra':
      return ColorType.BGRA_8888;
  }
}
function getComponentsPerPixel(pixelFormat: PixelFormat): number {
  switch (pixelFormat) {
    case 'abgr':
    case 'rgba':
    case 'bgra':
    case 'argb':
      return 4;
    case 'rgb':
    case 'bgr':
      return 3;
  }
}

export function createSkiaImageFromData(
  data: SkData,
  width: number,
  height: number,
  pixelFormat: PixelFormat
): SkImage | null {
  const componentsPerPixel = getComponentsPerPixel(pixelFormat);
  return Skia.Image.MakeImage(
    {
      width: width,
      height: height,
      alphaType: AlphaType.Opaque,
      colorType: getSkiaTypeForPixelFormat(pixelFormat),
    },
    data,
    width * componentsPerPixel
  );
}

export function CameraAffineTransform() {
  const device = useCameraDevice('back');
  const { hasPermission, requestPermission } = useCameraPermission();
  const previewImage = useSharedValue<SkImage | null>(null);
  const { resize } = useResizePlugin();

  useEffect(() => {
    requestPermission();
  }, [requestPermission]);

  const updatePreviewImageFromData = useRunOnJS(
    (data: SkData, pixelFormat: PixelFormat) => {
      const image = createSkiaImageFromData(data, WIDTH, HEIGHT, pixelFormat);
      if (image == null) {
        throw new Error('Failed to create Skia image from data');
      }
      previewImage.value?.dispose();
      previewImage.value = image;
    },
    []
  );

  const frameProcessor = useFrameProcessor(
    (frame) => {
      'worklet';

      const resized = resize(frame, {
        scale: {
          width: WIDTH,
          height: HEIGHT,
        },
        crop: {
          x: 0,
          y: 0,
          width: frame.width,
          height: frame.height,
        },
        pixelFormat: TARGET_FORMAT,
        dataType: TARGET_TYPE,
        rotation: '90deg',
      });

      const frameMat = OpenCV.frameBufferToMat(HEIGHT, WIDTH, 4, resized);
      const outputMat = OpenCV.createObject(
        ObjectType.Mat,
        HEIGHT,
        WIDTH,
        DataTypes.CV_8UC4
      );

      const scaleX = frame.height / frame.width;
      const scaledFrameWidth = WIDTH * scaleX;
      const translateX = (scaledFrameWidth - WIDTH) / 2;

      // 2x3 affine matrix has the following form (for scale and translation only):
      // | sx 0  tx |
      // | 0  sy ty |
      const matrix = [
        [scaleX, 0.0, -translateX],
        [0.0, 1.0, 0.0],
      ];

      const transformMat = OpenCV.createObject(
        ObjectType.Mat,
        2,
        3,
        DataTypes.CV_32F,
        matrix.flat()
      );

      OpenCV.invoke('warpAffine', frameMat, outputMat, transformMat);

      const output = OpenCV.matToBuffer(outputMat, 'uint8');
      const data = Skia.Data.fromBytes(output.buffer);

      updatePreviewImageFromData(data, TARGET_FORMAT).then(() => {
        data.dispose();
      });

      OpenCV.clearBuffers(); // REMEMBER TO CLEAN
    },
    [updatePreviewImageFromData]
  );

  if (!hasPermission) {
    return <Text>No permission</Text>;
  }

  if (device == null) {
    return <Text>No device</Text>;
  }

  return (
    <View style={styles.container}>
      <Camera
        style={StyleSheet.absoluteFill}
        device={device}
        enableFpsGraph
        isActive={true}
        pixelFormat="yuv"
        frameProcessor={frameProcessor}
      />
      <SafeAreaView style={styles.safe}>
        <Canvas style={styles.canvas}>
          <Image
            image={previewImage}
            x={0}
            y={0}
            width={WIDTH}
            height={HEIGHT}
            fit="contain"
          />
        </Canvas>
      </SafeAreaView>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    width: '100%',
    alignItems: 'center',
    justifyContent: 'center',
  },
  safe: {
    flex: 1,
    width: '100%',
    alignItems: 'center',
    justifyContent: 'flex-end',
  },
  canvas: {
    width: WIDTH,
    height: HEIGHT,
    borderColor: 'red',
    borderWidth: 2,
  },
});
