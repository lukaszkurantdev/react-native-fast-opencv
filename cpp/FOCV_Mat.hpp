//
//  FOCV_Mat.hpp
//
//  Created by Łukasz Kurant on 03/08/2024.
//

#ifndef FOCV_Mat_hpp
#define FOCV_Mat_hpp

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

class FOCV_Mat {
private:
    static std::unordered_map<std::string, cv::Mat> _matrices;
    
public:
    static void clear();
    
    static std::string createMat();
    static std::string createMat(std::string name);
    static std::string createMat(int rows, int cols, uint8_t* buffer);
    
    static std::string saveMat(cv::Mat);
    static std::string saveMat(std::string name, cv::Mat);
    
    static cv::Mat getMat(std::string id);
};

#endif /* FOCV_Mat_hpp */
