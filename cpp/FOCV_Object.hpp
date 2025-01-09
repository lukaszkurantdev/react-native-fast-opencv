//
//  FOCV_Object.hpp
//  Pods
//
//  Created by Łukasz Kurant on 06/08/2024.
//

#ifndef FOCV_Object_hpp
#define FOCV_Object_hpp

#include <jsi/jsilib.h>
#include <jsi/jsi.h>
#include <stdio.h>

#ifdef __cplusplus
#undef YES
#undef NO
#include <opencv2/opencv.hpp>
using namespace cv;
#if __has_feature(objc_bool)
#define YES __objc_yes
#define NO  __objc_no
#else
#define YES ((BOOL)1)
#define NO  ((BOOL)0)
#endif
#endif

using namespace facebook;

class FOCV_Object {
public:
    static jsi::Object create(jsi::Runtime& runtime, const jsi::Value* arguments, size_t count);
    static jsi::Object convertToJSI(jsi::Runtime& runtime, const jsi::Value* arguments, size_t count);
    static jsi::Object copyObjectFromVector(jsi::Runtime& runtime, const jsi::Value* arguments, size_t count);
};

#endif /* FOCV_Object_hpp */
