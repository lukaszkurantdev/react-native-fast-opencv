# Installation

To install the library, use npm/yarn/pnpm:

```
yarn add react-native-fast-opencv
```

And then:

```
cd ios && pod install
```

#### Integrations

The library can be easily integrated with:
- 📸 [VisionCamera](https://github.com/mrousavy/react-native-vision-camera) – The library allows frames from frame processors to be easily converted into OpenCV objects. To add a library check [here](./installation/visioncamera.md).
- 🧵 [WorkletsCore](https://github.com/margelo/react-native-worklets-core) – Operations on images can be time-consuming, and the library works with synchronous functions, hence it is a good idea to move the execution of the operation to another thread, so as not to block the JavaScript thread. Integration with this library allows tasks to be delegated to another thread. To add a library check [here](./installation/worklets.md).

