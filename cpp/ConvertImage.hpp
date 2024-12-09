//
//  ConvertImage.hpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 13/08/2024.
//

#ifndef ConvertImage_hpp
#define ConvertImage_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include <vector>
#include <string>

using namespace std;
using namespace cv;

class ImageConverter {
public:
    static cv::Mat str2mat(const string& imageBase64);
    static string mat2str(const Mat& img, std::string &format);

private:
    static std::string base64_encode(uchar const* bytesToEncode, unsigned int inLen);
    static std::string base64_decode(std::string const& encodedString);
};

#endif
