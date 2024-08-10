//
//  FOCV_Function.cpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 06/08/2024.
//

#include "FOCV_Function.hpp"
#include "FOCV_Storage.hpp"
#include "FOCV_Ids.hpp"
#include <FOCV_JsiObject.hpp>
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

std::string getId(jsi::Runtime& runtime, const jsi::Value& argument) {
    return argument.asString(runtime).utf8(runtime);
}

jsi::Object FOCV_Function::invoke(jsi::Runtime& runtime, const jsi::Value* arguments) {
    jsi::Object value(runtime);
    
    std::string functionName = getId(runtime, arguments[0]);
    
    switch (hashString(functionName.c_str(), functionName.size())) {
        case hashString("cvtColor", 8): {
            cv::Mat src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            cv::Mat dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            cv::cvtColor(src, dst, arguments[3].getNumber());
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("inRange", 7): {
            cv::Mat src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            std::string s = FOCV_JsiObject::id_from_wrap(runtime, arguments[2]);
            std::string id = FOCV_JsiObject::type_from_wrap(runtime, arguments[2]);
            cv::Vec3b lowerBound = FOCV_Storage::get<cv::Vec3b>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            cv::Vec3b upperBound = FOCV_Storage::get<cv::Vec3b>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            cv::Mat dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
            cv::inRange(src, lowerBound, upperBound, dst);
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]), dst);
        } break;
        case hashString("split", 5): {
            cv::Mat src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            std::vector<cv::Mat> dst = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            cv::split(src, dst);
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("findContours", 12): {
            cv::Mat src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            std::vector<std::vector<cv::Point>> contours;
            
            cv::findContours(src, contours, arguments[2].getNumber(), arguments[3].getNumber());

            auto ids = FOCV_Ids();
            
            for (size_t i = 0; i < contours.size(); i++) {
                auto id = FOCV_Storage::save(contours.at(i));
                ids.push(id);
            }

           return ids.toJsiArray(runtime, "point_vector");
        } break;
        case hashString("contourArea", 11): {
            std::vector<cv::Point> src = FOCV_Storage::get<std::vector<cv::Point>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            
            value.setProperty(runtime, "area", contourArea(src, arguments[2].getBool()));
        } break;
        case hashString("boundingRect", 12): {
            std::vector<cv::Point> src = FOCV_Storage::get<std::vector<cv::Point>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            cv::Rect rect = cv::boundingRect(src);
            
            std::string id = FOCV_Storage::save(rect);
            
            return FOCV_JsiObject::wrap(runtime, "rect", id);
        } break;
    }
    
    return value;
}
