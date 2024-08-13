//
//  FOCV_ObjectCreation.cpp
//  Pods
//
//  Created by Łukasz Kurant on 06/08/2024.
//

#include "FOCV_Object.hpp"
#include "FOCV_Storage.hpp"
#include "FOCV_JsiObject.hpp"
#include "jsi/TypedArray.h"
#include <opencv2/opencv.hpp>
#include "ConvertImage.hpp"

constexpr uint64_t hashString(const char* str, size_t length) {
  uint64_t hash = 14695981039346656037ull;
  const uint64_t fnv_prime = 1099511628211ull;
 
  for (size_t i = 0; i < length; ++i) {
      hash ^= static_cast<uint64_t>(str[i]);
      hash *= fnv_prime;
  }
 
  return hash;
}

jsi::Object FOCV_Object::create(jsi::Runtime& runtime, const jsi::Value* arguments) {
    std::any object;
    std::string objectType = arguments[0].asString(runtime).utf8(runtime);
    
    switch(hashString(objectType.c_str(), objectType.size())) {
        case hashString("mat", 3): {
            int rows = arguments[1].asNumber();
            int cols = arguments[2].asNumber();
            int type = arguments[3].asNumber();
            object = cv::Mat(rows, cols, type);
        } break;
        case hashString("mat_vector", 10): {
            object = std::vector<cv::Mat>();
        } break;
        case hashString("rect", 4): {
            int x = arguments[1].asNumber();
            int y = arguments[2].asNumber();
            int width  = arguments[3].asNumber();
            int height = arguments[4].asNumber();
            object = cv::Rect(x, y, width, height);
        } break;
        case hashString("rect_vector", 11): {
            object = std::vector<cv::Rect>();
        } break;
        case hashString("point", 5): {
            int x = arguments[1].asNumber();
            int y = arguments[2].asNumber();
            object = cv::Point(x, y);
        } break;
        case hashString("point_vector", 12): {
            object = std::vector<cv::Point>();
        } break;
        case hashString("size", 4): {
            int width = arguments[1].asNumber();
            int height = arguments[2].asNumber();
            object = cv::Size(width, height);
        } break;
        case hashString("vec3b", 5): {
            int a = arguments[1].asNumber();
            int b = arguments[2].asNumber();
            int c = arguments[3].asNumber();
            object = cv::Vec3b(a, b, c);
        } break;
        case hashString("scalar", 6): {
            if(arguments[4].isNumber()) {
                int a = arguments[1].asNumber();
                int b = arguments[2].asNumber();
                int c = arguments[3].asNumber();
                int d = arguments[3].asNumber();
                
                object = cv::Scalar(a, b, c, d);
            } else if(arguments[3].isNumber()) {
                int a = arguments[1].asNumber();
                int b = arguments[2].asNumber();
                int c = arguments[3].asNumber();

                object = cv::Scalar(a, b, c);
            } else {
                int a = arguments[1].asNumber();
                object = cv::Scalar(a);
            }
        } break;
    }
    
    std::string id = FOCV_Storage::save(object);
    return FOCV_JsiObject::wrap(runtime, objectType, id);
}

jsi::Object FOCV_Object::convertToJSI(jsi::Runtime& runtime, const jsi::Value* arguments) {
    jsi::Object value(runtime);
    std::string objectType = FOCV_JsiObject::type_from_wrap(runtime, arguments[0]);
    std::string id = FOCV_JsiObject::id_from_wrap(runtime, arguments[0]);
    
    switch(hashString(objectType.c_str(), objectType.size())) {
        case hashString("mat", 3): {
            cv::Mat mat = FOCV_Storage::get<cv::Mat>(id);
     
            value.setProperty(runtime, "base64", jsi::String::createFromUtf8(runtime, ImageConverter::mat2str(mat)));
            value.setProperty(runtime, "size", jsi::Value(mat.size));
            value.setProperty(runtime, "cols", jsi::Value(mat.cols));
            value.setProperty(runtime, "rows", jsi::Value(mat.rows));
        } break;
        case hashString("mat_vector", 9): {
            std::vector<cv::Mat> mats = FOCV_Storage::get<std::vector<cv::Mat>>(id);
            
            auto array = jsi::Array(runtime, mats.size());
            
            for (int i = 0; i < mats.size(); i++) {
                jsi::Object item(runtime);
                
                item.setProperty(runtime, "size", jsi::Value(mats.at(i).size));
                item.setProperty(runtime, "cols", jsi::Value(mats.at(i).cols));
                item.setProperty(runtime, "rows", jsi::Value(mats.at(i).rows));
                array.setValueAtIndex(runtime, i, item);
            }
            
            value.setProperty(runtime, "array", array);
        } break;
        case hashString("rect", 4): {
            cv::Rect rect = FOCV_Storage::get<cv::Rect>(id);
            
            value.setProperty(runtime, "x", jsi::Value(rect.x));
            value.setProperty(runtime, "y", jsi::Value(rect.y));
            value.setProperty(runtime, "width", jsi::Value(rect.width));
            value.setProperty(runtime, "height", jsi::Value(rect.height));
        } break;
        case hashString("rect_vector", 10): {
            std::vector<cv::Rect> rects = FOCV_Storage::get<std::vector<cv::Rect>>(id);
            
            auto array = jsi::Array(runtime, rects.size());
            
            for (int i = 0; i < rects.size(); i++) {
                jsi::Object item(runtime);
                
                item.setProperty(runtime, "x", jsi::Value(rects.at(i).x));
                item.setProperty(runtime, "y", jsi::Value(rects.at(i).y));
                item.setProperty(runtime, "width", jsi::Value(rects.at(i).width));
                item.setProperty(runtime, "height", jsi::Value(rects.at(i).height));
                array.setValueAtIndex(runtime, i, item);
            }
            
            value.setProperty(runtime, "array", array);
        } break;
        case hashString("point", 5): {
            cv::Point point = FOCV_Storage::get<cv::Point>(id);
            
            value.setProperty(runtime, "x", jsi::Value(point.x));
            value.setProperty(runtime, "y", jsi::Value(point.y));
        } break;
        case hashString("point_vector", 11): {
            std::vector<cv::Point> points = FOCV_Storage::get<std::vector<cv::Point>>(id);
            
            auto array = jsi::Array(runtime, points.size());
            
            for (int i = 0; i < points.size(); i++) {
                jsi::Object item(runtime);
                
                item.setProperty(runtime, "x", jsi::Value(points.at(i).x));
                item.setProperty(runtime, "y", jsi::Value(points.at(i).y));
                array.setValueAtIndex(runtime, i, item);
            }
            
            value.setProperty(runtime, "array", array);
        } break;
        case hashString("size", 4): {
            cv::Size size = FOCV_Storage::get<cv::Size>(id);
            
            value.setProperty(runtime, "width", jsi::Value(size.width));
            value.setProperty(runtime, "height", jsi::Value(size.height));
        } break;
        case hashString("vec3b", 4): {
            cv::Vec3b vec = FOCV_Storage::get<cv::Vec3b>(id);
            
            value.setProperty(runtime, "a", jsi::Value(vec.val[0]));
            value.setProperty(runtime, "b", jsi::Value(vec.val[1]));
            value.setProperty(runtime, "c", jsi::Value(vec.val[2]));
        } break;
        case hashString("scalar", 6): {
            cv::Scalar scalar = FOCV_Storage::get<cv::Scalar>(id);
            
            value.setProperty(runtime, "a", jsi::Value(scalar.val[0]));
            value.setProperty(runtime, "b", jsi::Value(scalar.val[1]));
            value.setProperty(runtime, "c", jsi::Value(scalar.val[2]));
            value.setProperty(runtime, "d", jsi::Value(scalar.val[3]));
        } break;
    }
  
    return value;
}

jsi::Object FOCV_Object::copyObjectFromVector(jsi::Runtime& runtime, const jsi::Value* arguments) {
    std::string createdId;
    
    jsi::Object value(runtime);
    std::string objectType = FOCV_JsiObject::type_from_wrap(runtime, arguments[0]);
    std::string vectorId = FOCV_JsiObject::id_from_wrap(runtime, arguments[0]);
    int index = arguments[1].asNumber();
    
    switch(hashString(objectType.c_str(), objectType.size())) {
        case hashString("mat_vector", 10): {
            std::vector<cv::Mat> array = FOCV_Storage::get<std::vector<cv::Mat>>(vectorId);
            cv::Mat mat = array.at(index);
            createdId = FOCV_Storage::save(mat);
            return FOCV_JsiObject::wrap(runtime, "mat", createdId);
        } break;
        case hashString("rect_vector", 11): {
            std::vector<cv::Rect> array = FOCV_Storage::get<std::vector<cv::Rect>>(vectorId);
            cv::Rect rect = array.at(index);
            createdId = FOCV_Storage::save(rect);
            return FOCV_JsiObject::wrap(runtime, "rect", createdId);
        } break;
        case hashString("point_vector", 12): {
            std::vector<cv::Point> array = FOCV_Storage::get<std::vector<cv::Point>>(vectorId);
            cv::Point point = array.at(index);
            createdId = FOCV_Storage::save(point);
            return FOCV_JsiObject::wrap(runtime, "point", createdId);
        } break;
    }

    return value;
}
