//
//  FOCV_PointsGroup.hpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 04/08/2024.
//

#ifndef FOCV_PointsGroup_hpp
#define FOCV_PointsGroup_hpp

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

class FOCV_PointsGroup {
private:
    static std::unordered_map<std::string, std::vector<cv::Point>> _groups;
    
public:
    static void clear();
    
    static std::string saveGroup(std::vector<cv::Point>);
    static std::string saveGroup(std::string, std::vector<cv::Point>);
    
    static std::vector<cv::Point> getGroup(std::string id);
};

#endif /* FOCV_PointsGroup_hpp */
