//
//  FOCV_Rect.hpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 04/08/2024.
//

#ifndef FOCV_Rect_hpp
#define FOCV_Rect_hpp

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

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

#include <stdio.h>

class FOCV_Rect {
private:
    static std::unordered_map<std::string, cv::Rect> _rects;
    
public:
    static void clear();
    
    static std::string saveRect(cv::Rect);
    static std::string saveRect(std::string,  cv::Rect);
    
    static cv::Rect getRect(std::string id);
    static facebook::jsi::Object getJsiRect(std::string id, facebook::jsi::Runtime& runtime);
};

#endif /* FOCV_Rect_hpp */
