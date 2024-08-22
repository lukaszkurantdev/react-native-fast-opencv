import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  install(): boolean;
}

const OpenCVInstaller = TurboModuleRegistry.getEnforcing<Spec>('FastOpencv');

console.log('try to install', OpenCVInstaller);

if (global.__loadOpenCV == null) {
  if (
    OpenCVInstaller == null ||
    typeof OpenCVInstaller.install !== 'function'
  ) {
    console.error(
      'Native Worklets Module cannot be found! Make sure you correctly ' +
        'installed native dependencies and rebuilt your app.'
    );
  } else {
    // Install the module
    const result = OpenCVInstaller.install();
    if (result !== true) {
      console.error(
        `Native Worklets Module failed to correctly install JSI Bindings! Result: ${result}`
      );
    } else {
      console.log('Worklets loaded successfully');
    }
  }
} else {
  console.log('react-native-worklets-core installed.');
}

export default OpenCVInstaller;
