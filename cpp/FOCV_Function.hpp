//
//  FOCV_Function.hpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 06/08/2024.
//

#ifndef FOCV_Function_hpp
#define FOCV_Function_hpp

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

class FOCV_Function {
public:
    static jsi::Object invoke(jsi::Runtime& runtime, const jsi::Value* arguments);
};


#endif /* FOCV_Function_hpp */
