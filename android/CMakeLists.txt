cmake_minimum_required(VERSION 3.22.1)
project(FastOpencv)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ReactAndroid REQUIRED CONFIG)
find_package(fbjni REQUIRED CONFIG)
find_package(OpenCV REQUIRED CONFIG)

file(GLOB_RECURSE FASTOPENCV_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../cpp/*.cpp")

add_library(react-native-fast-opencv SHARED
  ${FASTOPENCV_SOURCES}
  cpp-adapter.cpp
)

# Headers are included without directory prefixes (same as the flattened
# CocoaPods header map on iOS), so every source directory must be listed here.
set(FASTOPENCV_INCLUDE_DIRS
  ../cpp
  ../cpp/jsi
  ../cpp/delegates
  ../cpp/utils
)

file(GLOB FASTOPENCV_STRUCTURE_DIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/../cpp/structures/*")
foreach(STRUCTURE_DIR ${FASTOPENCV_STRUCTURE_DIRS})
  if(IS_DIRECTORY ${STRUCTURE_DIR})
    list(APPEND FASTOPENCV_INCLUDE_DIRS ${STRUCTURE_DIR})
  endif()
endforeach()

target_include_directories(react-native-fast-opencv PUBLIC ${FASTOPENCV_INCLUDE_DIRS})

target_link_libraries(react-native-fast-opencv
  android
  log
  fbjni::fbjni
  ReactAndroid::jsi
  ReactAndroid::reactnative
  OpenCV::opencv_java4
)
