//
//  FOCV_Rect.cpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 04/08/2024.
//

#include "FOCV_Rect.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <opencv2/opencv.hpp>
#include <jsi/jsilib.h>
#include <jsi/jsi.h>

using namespace facebook;

std::unordered_map<std::string, cv::Rect> FOCV_Rect::_rects = std::unordered_map<std::string, cv::Rect>();

void FOCV_Rect::clear() {
    _rects.clear();
}

std::string FOCV_Rect::saveRect(cv::Rect rect) {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string tmp = boost::uuids::to_string(uuid);
    
    _rects.insert_or_assign(tmp, rect);
    
    return tmp;
}

std::string FOCV_Rect::saveRect(std::string name, cv::Rect rect) {
    _rects.insert_or_assign(name, rect);
    
    return name;
}

cv::Rect FOCV_Rect::getRect(std::string id) {
    // Validation
    return _rects.at(id);
}

jsi::Object FOCV_Rect::getJsiRect(std::string id, facebook::jsi::Runtime& runtime) {
    cv::Rect rect = _rects.at(id);
    jsi::Object jsiRect = jsi::Object(runtime);
    jsiRect.setProperty(runtime, "x", jsi::Value(rect.x));
    jsiRect.setProperty(runtime, "y", jsi::Value(rect.y));
    jsiRect.setProperty(runtime, "width", jsi::Value(rect.width));
    jsiRect.setProperty(runtime, "height", jsi::Value(rect.height));
    
    return jsiRect;
}
