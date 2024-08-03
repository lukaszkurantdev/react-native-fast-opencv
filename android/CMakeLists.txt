cmake_minimum_required(VERSION 3.4.1)
project(FastOpencv)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 14)

add_library(react-native-fast-opencv            SHARED
            ../cpp/react-native-fast-opencv.cpp
            cpp-adapter.cpp
)

# Specifies a path to native header files.
include_directories(
            ../cpp
)
