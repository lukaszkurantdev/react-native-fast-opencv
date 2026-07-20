# Installation

To install the library, use npm/yarn/pnpm:

```
yarn add react-native-fast-opencv
```

And then:

```
cd ios && pod install
```

## OpenCV

This library does not build OpenCV from source — it links a prebuilt OpenCV binary on each platform, pulled in automatically when you install the package (`pod install` on iOS, Gradle dependency resolution on Android). You do **not** need to add OpenCV to your app manually.

The bundled OpenCV version currently differs between platforms:

| Platform | OpenCV version | Source |
| --- | --- | --- |
| iOS | **4.9.0** | [`FastOpenCV-iOS`](https://cocoapods.org/pods/FastOpenCV-iOS) pod (prebuilt `opencv2.xcframework`, arm64 device + arm64/x86_64 simulator) |
| Android | **4.12.0** | [`org.opencv:opencv:4.12.0`](https://mvnrepository.com/artifact/org.opencv/opencv) from Maven Central |

> Because the versions are not identical, a handful of functions may behave slightly differently between iOS and Android. If you rely on a function whose behaviour changed between these OpenCV releases, test it on both platforms. Check the OpenCV [changelog](https://github.com/opencv/opencv/wiki/ChangeLog) for details.

#### Integrations

The library can be easily integrated with:
- 📸 [VisionCamera](https://github.com/mrousavy/react-native-vision-camera) – The library allows frames from frame processors to be easily converted into OpenCV objects. To add a library check [here](./installation/visioncamera.md).
- 🧵 [WorkletsCore](https://github.com/margelo/react-native-worklets-core) – Operations on images can be time-consuming, and the library works with synchronous functions, hence it is a good idea to move the execution of the operation to another thread, so as not to block the JavaScript thread. Integration with this library allows tasks to be delegated to another thread. To add a library check [here](./installation/worklets.md).

