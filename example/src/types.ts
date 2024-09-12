import type { ParamListBase } from '@react-navigation/native';

export enum Route {
  Home = 'Home',
  ImageBlur = 'ImageBlur',
  CameraPassthrough = 'CameraPassthrough',
  CameraRealtimeDetection = 'CameraRealtimeDetection',
}

export interface StackParamList extends ParamListBase {
  Home: undefined;
  ImageBlur: undefined;
  CameraPassthrough: undefined;
  CameraRealtimeDetection: undefined;
}

// https://reactnavigation.org/docs/typescript#specifying-default-types-for-usenavigation-link-ref-etc
declare global {
  namespace ReactNavigation {
    interface RootParamList extends StackParamList {}
  }
}