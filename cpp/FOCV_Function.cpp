//
//  FOCV_Function.cpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 06/08/2024.
//

#include "FOCV_Function.hpp"
#include "FOCV_Storage.hpp"
#include <opencv2/opencv.hpp>

constexpr uint64_t hashString(const char* str, size_t length) {
  uint64_t hash = 14695981039346656037ull;
  const uint64_t fnv_prime = 1099511628211ull;
 
  for (size_t i = 0; i < length; ++i) {
      hash ^= static_cast<uint64_t>(str[i]);
      hash *= fnv_prime;
  }
 
  return hash;
}

std::string getId(jsi::Object argument) {
    return argument.asString(runtime).utf8(runtime)
}

jsi::Object FOCV_Function::invoke(jsi::Runtime& runtime, const jsi::Value* arguments) {
    jsi::Object value(runtime);
    std::string functionName = getId(arguments[0]);
    
    switch(hashString(objectType.c_str(), objectType.size())) {
        case hashString("cvtColor", 8): {
            cv::Mat src = FOCV_Storage::get<cv::Mat>(getId(arguments[1]));
            cv::Mat dst = FOCV_Storage::get<cv::Mat>(getId(arguments[2]));
            cv::cvtColor(src, dst, arguments[3].getNumber());
            FOCV_Storage::save(getId(arguments[2]), dst));
        } break;
        case hashString("inRange", 7): {
            cv::Mat src = FOCV_Storage::get<cv::Mat>(getId(arguments[0]));
            cv::Vec3b src = FOCV_Storage::get<cv::Vec3b>(getId(arguments[1]));
            cv::Vec3b src = FOCV_Storage::get<cv::Vec3b>(getId(arguments[2]));
            cv::Mat dst = FOCV_Storage::get<cv::Mat>(getId(arguments[3]));
            cv::inRange(src, lowerBound, upperBound, dst);
            FOCV_Storage::save(getId(arguments[3]), dst);
        } break;
        case hashString("split", 5): {
            cv::Mat src = FOCV_Storage::get<cv::Mat>(getId(arguments[0]));
            std::vector<cv::Mat> dst = FOCV_Storage::get<std::vector<cv::Mat>>(getId(arguments[1]));
            cv::split(src, dst);
            
            auto ids = FOCV_Ids();
            
            for (size_t i = 0; i < dst.size(); i++) {
                auto id = FOCV_Mat::saveMat(dst.at(i));
                ids.push(id);
            }
            value.setProperty(runtime, "array", ids.toJsiArray(runtime));
        } break;
        case hashString("findContours", 12): {
            cv::Mat src = FOCV_Storage::get<cv::Mat>(getId(arguments[0]));
            std::vector<std::vector<cv::Point>> contours;
            
            cv::findContours(src, contours, arguments[1].getNumber(), arguments[2].getNumber());

            auto ids = FOCV_Ids();
            
            for (size_t i = 0; i < contours.size(); i++) {
                auto id = FOCV_Storage::save(contours.at(i));
                ids.push(id);
            }

            value.setProperty(runtime, "array", ids.toJsiArray(runtime));
        } break;
        case hashString("contourArea", 11): {
            std::vector<cv::Point> src = FOCV_Storage::get<std::vector<cv::Point>>(getId(arguments[0]));
            
            value.setProperty(runtime, "area", contourArea(src, arguments[1].getBool()));
        } break;

    }
    
    jsi::Object object(runtime);
    object.setProperty(runtime, "value", value);
  
    return object;
}
