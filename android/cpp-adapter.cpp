#include <jni.h>
#include "react-native-fast-opencv.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_fastopencv_FastOpencvModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return fastopencv::multiply(a, b);
}
