![React Native Fast OpenCV](../images/title-banner.svg)

A powerful port of **OpenCV** for React Native.

> The library is in the early stages of development and not all functions or objects available in OpenCV are supported. Add an issue if you have any problems or questions.

- 🔥 Powered by JSI
- 🏎️ Uses OpenCV C++ API
- 🏛️ New architecture ready
- 🪽 Easy usage, without manual configuration
- 📸 Easy [VisionCamera](https://github.com/mrousavy/react-native-vision-camera) integration
- 🧵 Easy [WorkletsCore](https://github.com/margelo/react-native-worklets-core) integration
- ⛓️‍💥 It can also be used on its own without integration

### Motivation

OpenCV is a popular library for image processing, but quite tricky when it comes to its integration and use in React Native applications. My main goal is to enable simple operations directly from JavaScript code.

Currently, there is a port of the OpenCV library but due to the change in standards when developing React Native applications, I decided to create a new library using an API in C++ that will allow for simpler integration, better performance and readability when used in code.

### Installation

The method of installation is described [here](./installation.md).

### State of development

Due to the size of the OpenCV library, this port currently only supports selected objects and functions. However, development is simple enough to only require the addition of specific code in C++ using the functionality.

List of available functions are available [here](./availablefunctions.md).

---

### Credits
Special thanks to:
- The creators of the [Vision Camera](https://github.com/mrousavy/react-native-vision-camera) and [WorkletsCore](https://github.com/margelo/react-native-worklets-core) libraries, especially Marc Rousavy - thanks for the amazing libraries.
- Creator of the [react-native-opencv3](https://github.com/adamgf/react-native-opencv3) library (Adam G. Freeman) - your library was an important starting point for creating my port.
- Creator of the [TS definition for OpenCV](https://github.com/peteruhnak/opencv-ts) (Peter Uhnak) - the library was an important support for this port.



### License
MIT

---

2024 Lukasz Kurant