# Vision Camera Integration

The library allows frames from frame processors to be easily converted into OpenCV objects. To install the library and its dependencies, follow these steps.


1. Add libraries:

```
yarn add react-native-vision-camera react-native-worklets-core
```

And then:

```
cd ios && pod install
```

2. Update `Info.plist` and add the following lines inside <dict> tag:

```
<key>NSCameraUsageDescription</key>
<string>$(PRODUCT_NAME) needs access to your Camera.</string>
```

3. Update `AndroidManifest.xml` and add the following line inside the <manifest> tag:

```
<uses-permission android:name="android.permission.CAMERA" />
```

4. Add the babel plugin to your `babel.config.js`:

```
module.exports = {
  plugins: [
    ["react-native-worklets-core/plugin"],
    // ...
  ],
  // ...
};
```

5. Restart Metro with clean cache:

```
yarn start --reset-cache
```

You can find a detailed description of the installation process [here](https://react-native-vision-camera.com/docs/guides).


### Usage

The methods of use are [here](../usage.md).