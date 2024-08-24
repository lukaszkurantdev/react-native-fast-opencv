import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  install(): boolean;
}

const OpenCVInstaller = TurboModuleRegistry.getEnforcing<Spec>('FastOpencv');

if (global.__loadOpenCV == null) {
  if (
    OpenCVInstaller == null ||
    typeof OpenCVInstaller.install !== 'function'
  ) {
    console.error(
      'Native Fast OpenCV Module cannot be found! Make sure you correctly ' +
        'installed native dependencies and rebuilt your app.'
    );
  } else {
    const result = OpenCVInstaller.install();

    if (result !== true) {
      console.error(
        'Native OpenCV Module failed to correctly install JSI Bindings!'
      );
    }
  }
}

export default OpenCVInstaller;
