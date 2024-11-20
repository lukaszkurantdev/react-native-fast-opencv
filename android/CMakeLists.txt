cmake_minimum_required(VERSION 3.4.1)
project(FastOpencv)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 20)

file(TO_CMAKE_PATH "${NODE_MODULES_DIR}" NODE_MODULES_DIR)

find_package(ReactAndroid REQUIRED CONFIG)
find_package(fbjni REQUIRED CONFIG)
find_package(OpenCV REQUIRED COMPONENTS OpenCV::opencv_java4)

add_library(react-native-fast-opencv
        SHARED
        "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi/jsi/jsi.cpp"
        ../cpp/react-native-fast-opencv.cpp
        ../cpp/react-native-fast-opencv.h
        cpp-adapter.cpp
        ../cpp/ConvertImage.cpp
        ../cpp/FOCV_Function.cpp
        ../cpp/FOCV_FunctionArguments.cpp
        ../cpp/FOCV_Ids.cpp
        ../cpp/FOCV_JsiObject.cpp
        ../cpp/FOCV_Object.cpp
        ../cpp/FOCV_Storage.cpp
        ../cpp/FOCV_Storage.hpp
        ../cpp/UUID.cpp
        ../cpp/jsi/TypedArray.cpp
        ../cpp/jsi/Promise.cpp

)

# Specifies a path to native header files.
include_directories(
          ../cpp
          ../cpp/jsi
          "${NODE_MODULES_DIR}/react-native/React"
          "${NODE_MODULES_DIR}/react-native/React/Base"
          "${NODE_MODULES_DIR}/react-native/ReactCommon"
          "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"
          "${NODE_MODULES_DIR}/react-native/ReactCommon/callinvoker"
          "${NODE_MODULES_DIR}/react-native/ReactAndroid/src/main/jni/react/turbomodule"
)

if(ReactAndroid_VERSION_MINOR GREATER_EQUAL 76)
  target_link_libraries(
    react-native-fast-opencv
    log
    android
    ReactAndroid::reactnative
    fbjni::fbjni
    OpenCV::opencv_java4
  )
else()
  target_link_libraries(
    react-native-fast-opencv
    log
    android
    ReactAndroid::folly_runtime
    ReactAndroid::glog
    ReactAndroid::jsi
    ReactAndroid::reactnativejni
    fbjni::fbjni
    OpenCV::opencv_java4
  )
endif()