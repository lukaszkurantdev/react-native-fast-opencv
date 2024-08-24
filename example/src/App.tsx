import { ImageExample } from './ImageExample';
import { VisionCameraExample } from './VisionCameraExample';

export default function App() {
  const camera = true;

  if (camera) {
    return <VisionCameraExample />;
  }

  return <ImageExample />;
}
