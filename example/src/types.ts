import type { ParamListBase } from '@react-navigation/native';

export enum Route {
  Home = 'Home',
  ImageBlur = 'ImageBlur',
  FitEllipse = 'FitEllipse',
  CLAHE = 'CLAHE',
  CameraPassthrough = 'CameraPassthrough',
  CameraRealtimeDetection = 'CameraRealtimeDetection',
  DocumentDetection = 'DocumentDetection',
}

export interface StackParamList extends ParamListBase {
  Home: undefined;
  ImageBlur: undefined;
  FitEllipse: undefined;
  CLAHE: undefined;
  CameraPassthrough: undefined;
  CameraRealtimeDetection: undefined;
  DocumentDetection: undefined;
}

// https://reactnavigation.org/docs/typescript#specifying-default-types-for-usenavigation-link-ref-etc
declare global {
  namespace ReactNavigation {
    interface RootParamList extends StackParamList {}
  }
}
