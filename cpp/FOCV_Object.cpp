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
#include "jsi/TypedArray.h"

using namespace mrousavy;

// General idea and this function for hashing is from
// https://mrousavy.com/blog/Hashing-String-Ifs
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
    std::string id = "";
    std::string objectType = arguments[0].asString(runtime).utf8(runtime);

    switch(hashString(objectType.c_str(), objectType.size())) {
        case hashString("mat", 3): {
            int rows = arguments[1].asNumber();
            int cols = arguments[2].asNumber();
            int type = arguments[3].asNumber();
            
            if(arguments[4].isObject()) {
                auto rawArray = arguments[4].asObject(runtime);
                auto array = rawArray.asArray(runtime);
                
                auto rawLength = rawArray.getProperty(runtime, "length");
                auto length = rawLength.asNumber();
                
                std::vector<float> vec;
                
                for(auto i = 0; i < length; i++) {
                    vec.push_back(array.getValueAtIndex(runtime, i).asNumber());
                }

                cv::Mat mat{vec, true};
                mat = mat.reshape(1, rows);
                mat.convertTo(mat, type);
                
                id = FOCV_Storage::save(mat);
            } else {
                cv::Mat object(rows, cols, type);
                id = FOCV_Storage::save(object);
            }
        } break;
        case hashString("mat_vector", 10): {
            std::vector<cv::Mat> object;
            id = FOCV_Storage::save(object);
        } break;
        case hashString("rect", 4): {
            int x = arguments[1].asNumber();
            int y = arguments[2].asNumber();
            int width  = arguments[3].asNumber();
            int height = arguments[4].asNumber();
            cv::Rect object(x, y, width, height);
            id = FOCV_Storage::save(object);
        } break;
        case hashString("rect_vector", 11): {
            std::vector<cv::Rect> object;
            id = FOCV_Storage::save(object);
        } break;
        case hashString("point", 5): {
            int x = arguments[1].asNumber();
            int y = arguments[2].asNumber();
            cv::Point object(x, y);
            id = FOCV_Storage::save(object);
        } break;
        case hashString("point_vector", 12): {
            std::vector<cv::Point> object;
            id = FOCV_Storage::save(object);
        } break;
        case hashString("point_vector_vector", 19): {
            std::vector<std::vector<cv::Point>> object;
            id = FOCV_Storage::save(object);
        } break;
        case hashString("size", 4): {
            int width = arguments[1].asNumber();
            int height = arguments[2].asNumber();
            cv::Size object(width, height);
            id = FOCV_Storage::save(object);
        } break;
        case hashString("vec3b", 5): {
            int a = arguments[1].asNumber();
            int b = arguments[2].asNumber();
            int c = arguments[3].asNumber();
            cv::Vec3b object(a, b, c);
            id = FOCV_Storage::save(object);
        } break;
        case hashString("scalar", 6): {
            if(arguments[4].isNumber()) {
                int a = arguments[1].asNumber();
                int b = arguments[2].asNumber();
                int c = arguments[3].asNumber();
                int d = arguments[3].asNumber();

                cv::Scalar object(a, b, c, d);
                id = FOCV_Storage::save(object);
            } else if(arguments[3].isNumber()) {
                int a = arguments[1].asNumber();
                int b = arguments[2].asNumber();
                int c = arguments[3].asNumber();

                cv::Scalar object(a, b, c);
                id = FOCV_Storage::save(object);
            } else {
                int a = arguments[1].asNumber();
                cv::Scalar object(a);
                id = FOCV_Storage::save(object);
            }
        } break;
        case hashString("rotated_rect", 12): {
            int x = arguments[1].asNumber();
            int y = arguments[2].asNumber();
            int width  = arguments[3].asNumber();
            int height = arguments[4].asNumber();
            int angle = arguments[5].asNumber();

            cv::RotatedRect object(cv::Point(x,y), cv::Size(width, height), angle);
            id = FOCV_Storage::save(object);
        } break;
    }


    return FOCV_JsiObject::wrap(runtime, objectType, id);
}

jsi::Object FOCV_Object::convertToJSI(jsi::Runtime& runtime, const jsi::Value* arguments) {
    jsi::Object value(runtime);
    std::string objectType = FOCV_JsiObject::type_from_wrap(runtime, arguments[0]);
    std::string id = FOCV_JsiObject::id_from_wrap(runtime, arguments[0]);

    switch(hashString(objectType.c_str(), objectType.size())) {
        case hashString("mat", 3): {
            auto mat = *FOCV_Storage::get<cv::Mat>(id);
            mat.convertTo(mat, CV_8U);

            value.setProperty(runtime, "base64", jsi::String::createFromUtf8(runtime, ImageConverter::mat2str(mat)));
            value.setProperty(runtime, "size", jsi::Value(mat.size));
            value.setProperty(runtime, "cols", jsi::Value(mat.cols));
            value.setProperty(runtime, "rows", jsi::Value(mat.rows));
        } break;
        case hashString("mat_vector", 10): {
            auto mats = *FOCV_Storage::get<std::vector<cv::Mat>>(id);

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
            auto rect = *FOCV_Storage::get<cv::Rect>(id);

            value.setProperty(runtime, "x", jsi::Value(rect.x));
            value.setProperty(runtime, "y", jsi::Value(rect.y));
            value.setProperty(runtime, "width", jsi::Value(rect.width));
            value.setProperty(runtime, "height", jsi::Value(rect.height));
        } break;
        case hashString("rect_vector", 11): {
            auto rects = *FOCV_Storage::get<std::vector<cv::Rect>>(id);

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
            auto point = *FOCV_Storage::get<cv::Point>(id);

            value.setProperty(runtime, "x", jsi::Value(point.x));
            value.setProperty(runtime, "y", jsi::Value(point.y));
        } break;
        case hashString("point_vector", 12): {
            auto points = *FOCV_Storage::get<std::vector<cv::Point>>(id);

            auto array = jsi::Array(runtime, points.size());

            for (int i = 0; i < points.size(); i++) {
                jsi::Object item(runtime);

                item.setProperty(runtime, "x", jsi::Value(points.at(i).x));
                item.setProperty(runtime, "y", jsi::Value(points.at(i).y));
                array.setValueAtIndex(runtime, i, item);
            }

            value.setProperty(runtime, "array", array);
        } break;
        case hashString("point_vector_vector", 19): {
            auto points_vector = *FOCV_Storage::get<std::vector<std::vector<cv::Point>>>(id);

            auto vectors_array = jsi::Array(runtime, points_vector.size());

            for (int i = 0; i < points_vector.size(); i++) {
                auto points = points_vector.at(i);
                auto array = jsi::Array(runtime, points.size());
              
                for (int j = 0; j < points.size(); j++) {
                    jsi::Object item(runtime);
                    
                    item.setProperty(runtime, "x", jsi::Value(points.at(j).x));
                    item.setProperty(runtime, "y", jsi::Value(points.at(j).y));
                    array.setValueAtIndex(runtime, j, item);
                }
                
                vectors_array.setValueAtIndex(runtime, i, array);
            }

            value.setProperty(runtime, "array", vectors_array);
        } break;
        case hashString("size", 4): {
            auto size = *FOCV_Storage::get<cv::Size>(id);

            value.setProperty(runtime, "width", jsi::Value(size.width));
            value.setProperty(runtime, "height", jsi::Value(size.height));
        } break;
        case hashString("vec3b", 5): {
            auto vec = *FOCV_Storage::get<cv::Vec3b>(id);

            value.setProperty(runtime, "a", jsi::Value(vec.val[0]));
            value.setProperty(runtime, "b", jsi::Value(vec.val[1]));
            value.setProperty(runtime, "c", jsi::Value(vec.val[2]));
        } break;
        case hashString("scalar", 6): {
            auto scalar = *FOCV_Storage::get<cv::Scalar>(id);

            value.setProperty(runtime, "a", jsi::Value(scalar.val[0]));
            value.setProperty(runtime, "b", jsi::Value(scalar.val[1]));
            value.setProperty(runtime, "c", jsi::Value(scalar.val[2]));
            value.setProperty(runtime, "d", jsi::Value(scalar.val[3]));
        } break;
        case hashString("rotated_rect", 12): {
            auto rect = *FOCV_Storage::get<cv::RotatedRect>(id);

            value.setProperty(runtime, "centerX", jsi::Value(rect.center.x));
            value.setProperty(runtime, "centerY", jsi::Value(rect.center.y));
            value.setProperty(runtime, "width", jsi::Value(rect.size.width));
            value.setProperty(runtime, "height", jsi::Value(rect.size.height));
            value.setProperty(runtime, "angle", jsi::Value(rect.angle));
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
            auto array = *FOCV_Storage::get<std::vector<cv::Mat>>(vectorId);
            cv::Mat mat = array.at(index);
            createdId = FOCV_Storage::save(mat);
            return FOCV_JsiObject::wrap(runtime, "mat", createdId);
        } break;
        case hashString("rect_vector", 11): {
            auto array = *FOCV_Storage::get<std::vector<cv::Rect>>(vectorId);
            cv::Rect rect = array.at(index);
            createdId = FOCV_Storage::save(rect);
            return FOCV_JsiObject::wrap(runtime, "rect", createdId);
        } break;
        case hashString("point_vector", 12): {
            auto array = *FOCV_Storage::get<std::vector<cv::Point>>(vectorId);
            cv::Point point = array.at(index);
            createdId = FOCV_Storage::save(point);
            return FOCV_JsiObject::wrap(runtime, "point", createdId);
        } break;
        case hashString("point_vector_vector", 19): {
            auto array = *FOCV_Storage::get<std::vector<std::vector<cv::Point>>>(vectorId);
            std::vector<cv::Point> point = array.at(index);
            createdId = FOCV_Storage::save(point);
            return FOCV_JsiObject::wrap(runtime, "point_vector", createdId);
        } break;
    }

    return value;
}
