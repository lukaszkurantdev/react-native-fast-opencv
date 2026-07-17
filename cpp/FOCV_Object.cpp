//
//  FOCV_ObjectCreation.cpp
//  Pods
//
//  Created by Łukasz Kurant on 06/08/2024.
//

#include "FOCV_Object.hpp"
#include "FOCV_JsiObject.hpp"
#include "jsi/TypedArray.h"
#include <opencv2/opencv.hpp>
#include "ConvertImage.hpp"
#include "jsi/TypedArray.h"
#include "hashString.hpp"

using namespace mrousavy;


jsi::Object FOCV_Object::create(jsi::Runtime& runtime, const jsi::Value* arguments, size_t count) {
    
    std::string objectType = arguments[0].asString(runtime).utf8(runtime);

    switch(hashString(objectType.c_str(), objectType.size())) {
        case hashString("mat", 3): {
            auto rows = static_cast<int>(arguments[1].asNumber());
            auto cols = static_cast<int>(arguments[2].asNumber());
            auto type = static_cast<int>(arguments[3].asNumber());
            auto channels = CV_MAT_CN(type);
            auto depth = CV_MAT_DEPTH(type);
            std::vector<int> size {rows, cols};
            
            if (count > 4 && arguments[4].isObject()) {
                auto array = arguments[4].asObject(runtime).asArray(runtime);
                auto length = array.length(runtime);
                
                std::vector<double> vec;
                vec.reserve(length);
                for(size_t i = 0; i < length; i++) {
                    vec.push_back(array.getValueAtIndex(runtime, i).asNumber());
                }

                cv::Mat object(vec, true);
                object = object.reshape(channels, size);
                object.convertTo(object, depth);
                return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<cv::Mat>(object));
            } else {
                cv::Mat object(rows, cols, type);
                return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<cv::Mat>(object));
            }
        } break;
        case hashString("mat_vector", 10): {
            std::vector<cv::Mat> vec;
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(vec)>(vec));
        } break;
        case hashString("rect", 4): {
            auto x = static_cast<int>(arguments[1].asNumber());
            auto y = static_cast<int>(arguments[2].asNumber());
            auto width  = static_cast<int>(arguments[3].asNumber());
            auto height = static_cast<int>(arguments[4].asNumber());
            cv::Rect object(x, y, width, height);
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(object)>(object));
        } break;
        case hashString("rect_vector", 11): {
            std::vector<cv::Rect> vec;
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(vec)>(vec));
        } break;
        case hashString("point", 5): {
            auto x = static_cast<int>(arguments[1].asNumber());
            auto y = static_cast<int>(arguments[2].asNumber());
            cv::Point object(x, y);
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(object)>(object));
        } break;
        case hashString("point_vector", 12): {
            std::vector<cv::Point> vec;
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(vec)>(vec));
        } break;
        case hashString("point2f", 7): {
            auto x = static_cast<float>(arguments[1].asNumber());
            auto y = static_cast<float>(arguments[2].asNumber());
            cv::Point2f object(x, y);
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(object)>(object));
        } break;
        case hashString("point2f_vector", 14): {
            std::vector<cv::Point2f> vec;
            if (count > 1 && arguments[1].isObject()) {
                auto array = arguments[1].asObject(runtime).asArray(runtime);
                auto length = array.length(runtime);
                
                for(size_t i = 0; i < length; i++) {
                    auto value = array.getValueAtIndex(runtime, i);
                    auto value_id = FOCV_JsiObject::id_from_wrap(runtime, value);
                    auto point2fPtr = FOCV_JsiObject::get_from_wrap<cv::Point2f>(runtime, value);

                    vec.push_back(*point2fPtr);
                }
            }
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(vec)>(vec));
        } break;
        case hashString("point_vector_vector", 19): {
            std::vector<std::vector<cv::Point>> vec;
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(vec)>(vec));
        } break;
        case hashString("size", 4): {
            auto width = static_cast<int>(arguments[1].asNumber());
            auto height = static_cast<int>(arguments[2].asNumber());
            cv::Size object(width, height);
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(object)>(object));
        } break;
        case hashString("vec3b", 5): {
            auto a = static_cast<uchar>(arguments[1].asNumber());
            auto b = static_cast<uchar>(arguments[2].asNumber());
            auto c = static_cast<uchar>(arguments[3].asNumber());
            cv::Vec3b object(a, b, c);
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(object)>(object));
        } break;
        case hashString("scalar", 6): {
            if (count > 4 && arguments[4].isNumber()) {
                auto a = arguments[1].asNumber();
                auto b = arguments[2].asNumber();
                auto c = arguments[3].asNumber();
                auto d = arguments[4].asNumber();

                cv::Scalar object(a, b, c, d);
                return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(object)>(object));
            } else if(count > 3 && arguments[3].isNumber()) {
                auto a = arguments[1].asNumber();
                auto b = arguments[2].asNumber();
                auto c = arguments[3].asNumber();

                cv::Scalar object(a, b, c);
                return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(object)>(object));
            } else {
                auto a = arguments[1].asNumber();
                cv::Scalar object(a);
                return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(object)>(object));
            }
        } break;
        case hashString("rotated_rect", 12): {
            auto x = static_cast<int>(arguments[1].asNumber());
            auto y = static_cast<int>(arguments[2].asNumber());
            auto width  = static_cast<int>(arguments[3].asNumber());
            auto height = static_cast<int>(arguments[4].asNumber());
            auto angle = static_cast<float>(arguments[5].asNumber());

            cv::RotatedRect object(cv::Point(x,y), cv::Size(width, height), angle);
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(object)>(object));
        } break;
        case hashString("term_criteria", 13): {
            auto termCriteriaType = static_cast<int>(arguments[1].asNumber());
            auto maxCount = static_cast<int>(arguments[2].asNumber());
            auto epsilon  = arguments[3].asNumber();

            cv::TermCriteria object(termCriteriaType, maxCount, epsilon);
            if (!object.isValid()) {
                throw std::runtime_error("Fast OpenCV Error: Invalid TermCriteria object parameters!");
            }
            
            return FOCV_JsiObject::wrap(runtime, objectType, std::make_shared<decltype(object)>(object));
        } break;
        default: {
         
        }
    }
    jsi::Object value(runtime);
    return value;
}

jsi::Object FOCV_Object::convertToJSI(jsi::Runtime& runtime, const jsi::Value* arguments, size_t count) {
    jsi::Object value(runtime);
    std::string objectType = FOCV_JsiObject::type_from_wrap(runtime, arguments[0]);
    

    switch(hashString(objectType.c_str(), objectType.size())) {
        case hashString("mat", 3): {
            auto mat = *FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, arguments[0]);
            std::string format = "jpeg";
          
            if(arguments[1].isString()) {
              format = arguments[1].asString(runtime).utf8(runtime);
            }
         
            mat.convertTo(mat, CV_8U);
          
            value.setProperty(runtime, "base64", jsi::String::createFromUtf8(runtime, ImageConverter::mat2str(mat, format)));
            value.setProperty(runtime, "size", jsi::Value(mat.size));
            value.setProperty(runtime, "cols", jsi::Value(mat.cols));
            value.setProperty(runtime, "rows", jsi::Value(mat.rows));
            value.setProperty(runtime, "type", jsi::Value(mat.type()));
        } break;
        case hashString("mat_vector", 10): {
            auto mats = *FOCV_JsiObject::get_from_wrap<std::vector<cv::Mat>>(runtime, arguments[0]);

            auto array = jsi::Array(runtime, mats.size());

            for (size_t i = 0; i < mats.size(); i++) {
                jsi::Object item(runtime);

                item.setProperty(runtime, "size", jsi::Value(mats.at(i).size));
                item.setProperty(runtime, "cols", jsi::Value(mats.at(i).cols));
                item.setProperty(runtime, "rows", jsi::Value(mats.at(i).rows));
                array.setValueAtIndex(runtime, i, item);
            }

            value.setProperty(runtime, "array", array);
        } break;
        case hashString("rect", 4): {
            auto rect = *FOCV_JsiObject::get_from_wrap<cv::Rect>(runtime, arguments[0]);

            value.setProperty(runtime, "x", jsi::Value(rect.x));
            value.setProperty(runtime, "y", jsi::Value(rect.y));
            value.setProperty(runtime, "width", jsi::Value(rect.width));
            value.setProperty(runtime, "height", jsi::Value(rect.height));
        } break;
        case hashString("rect_vector", 11): {
            auto rects = *FOCV_JsiObject::get_from_wrap<std::vector<cv::Rect>>(runtime, arguments[0]);

            auto array = jsi::Array(runtime, rects.size());

            for (size_t i = 0; i < rects.size(); i++) {
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
            auto point = *FOCV_JsiObject::get_from_wrap<cv::Point>(runtime, arguments[0]);

            value.setProperty(runtime, "x", jsi::Value(point.x));
            value.setProperty(runtime, "y", jsi::Value(point.y));
        } break;
        case hashString("point2f", 7): {
            auto point = *FOCV_JsiObject::get_from_wrap<cv::Point2f>(runtime, arguments[0]);

            value.setProperty(runtime, "x", jsi::Value(point.x));
            value.setProperty(runtime, "y", jsi::Value(point.y));
        } break;
        case hashString("point_vector", 12): {
            auto points = *FOCV_JsiObject::get_from_wrap<std::vector<cv::Point>>(runtime, arguments[0]);

            auto array = jsi::Array(runtime, points.size());

            for (size_t i = 0; i < points.size(); i++) {
                jsi::Object item(runtime);

                item.setProperty(runtime, "x", jsi::Value(points.at(i).x));
                item.setProperty(runtime, "y", jsi::Value(points.at(i).y));
                array.setValueAtIndex(runtime, i, item);
            }

            value.setProperty(runtime, "array", array);
        } break;
        case hashString("point_vector_vector", 19): {
            auto points_vector = *FOCV_JsiObject::get_from_wrap<std::vector<std::vector<cv::Point>>>(runtime, arguments[0]);

            auto vectors_array = jsi::Array(runtime, points_vector.size());

            for (size_t i = 0; i < points_vector.size(); i++) {
                const auto& points = points_vector.at(i);
                auto array = jsi::Array(runtime, points.size());
              
                for (size_t j = 0; j < points.size(); j++) {
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
            auto size = *FOCV_JsiObject::get_from_wrap<cv::Size>(runtime, arguments[0]);

            value.setProperty(runtime, "width", jsi::Value(size.width));
            value.setProperty(runtime, "height", jsi::Value(size.height));
        } break;
        case hashString("vec3b", 5): {
            auto vec = *FOCV_JsiObject::get_from_wrap<cv::Vec3b>(runtime, arguments[0]);

            value.setProperty(runtime, "a", jsi::Value(vec.val[0]));
            value.setProperty(runtime, "b", jsi::Value(vec.val[1]));
            value.setProperty(runtime, "c", jsi::Value(vec.val[2]));
        } break;
        case hashString("scalar", 6): {
            auto scalar = *FOCV_JsiObject::get_from_wrap<cv::Scalar>(runtime, arguments[0]);

            value.setProperty(runtime, "a", jsi::Value(scalar.val[0]));
            value.setProperty(runtime, "b", jsi::Value(scalar.val[1]));
            value.setProperty(runtime, "c", jsi::Value(scalar.val[2]));
            value.setProperty(runtime, "d", jsi::Value(scalar.val[3]));
        } break;
        case hashString("rotated_rect", 12): {
            auto rect = *FOCV_JsiObject::get_from_wrap<cv::RotatedRect>(runtime, arguments[0]);

            value.setProperty(runtime, "centerX", jsi::Value(rect.center.x));
            value.setProperty(runtime, "centerY", jsi::Value(rect.center.y));
            value.setProperty(runtime, "width", jsi::Value(rect.size.width));
            value.setProperty(runtime, "height", jsi::Value(rect.size.height));
            value.setProperty(runtime, "angle", jsi::Value(rect.angle));
        } break;
        case hashString("term_criteria", 13): {
            auto termCriteria = *FOCV_JsiObject::get_from_wrap<cv::TermCriteria>(runtime, arguments[0]);

            value.setProperty(runtime, "type", jsi::Value(termCriteria.type));
            value.setProperty(runtime, "maxCount", jsi::Value(termCriteria.maxCount));
            value.setProperty(runtime, "epsilon", jsi::Value(termCriteria.epsilon));
        } break;
    }

    return value;
}

jsi::Object FOCV_Object::copyObjectFromVector(jsi::Runtime& runtime, const jsi::Value* arguments, size_t count) {
    

    jsi::Object value(runtime);
    std::string objectType = FOCV_JsiObject::type_from_wrap(runtime, arguments[0]);
    
    auto index = static_cast<int>(arguments[1].asNumber());

    switch(hashString(objectType.c_str(), objectType.size())) {
        case hashString("mat_vector", 10): {
            auto array = *FOCV_JsiObject::get_from_wrap<std::vector<cv::Mat>>(runtime, arguments[0]);
            auto mat = array.at(index);
            return FOCV_JsiObject::wrap(runtime, "mat", std::make_shared<decltype(mat)>(mat));
        } break;
        case hashString("rect_vector", 11): {
            auto array = *FOCV_JsiObject::get_from_wrap<std::vector<cv::Rect>>(runtime, arguments[0]);
            auto rect = array.at(index);
            return FOCV_JsiObject::wrap(runtime, "rect", std::make_shared<decltype(rect)>(rect));
        } break;
        case hashString("point_vector", 12): {
            auto array = *FOCV_JsiObject::get_from_wrap<std::vector<cv::Point>>(runtime, arguments[0]);
            auto point = array.at(index);
            return FOCV_JsiObject::wrap(runtime, "point", std::make_shared<decltype(point)>(point));
        } break;
        case hashString("point_vector_vector", 19): {
            auto array = *FOCV_JsiObject::get_from_wrap<std::vector<std::vector<cv::Point>>>(runtime, arguments[0]);
            auto point = array.at(index);
            return FOCV_JsiObject::wrap(runtime, "point_vector", std::make_shared<decltype(point)>(point));
        } break;
    }

    return value;
}

void FOCV_Object::addObjectToVector(jsi::Runtime& runtime, const jsi::Value* arguments, size_t count) {
    

    jsi::Object value(runtime);
    std::string objectType = FOCV_JsiObject::type_from_wrap(runtime, arguments[0]);
    
    
  
    switch(hashString(objectType.c_str(), objectType.size())) {
        case hashString("mat_vector", 10): {
            auto& array = *FOCV_JsiObject::get_from_wrap<std::vector<cv::Mat>>(runtime, arguments[0]);
            auto& object = *FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, arguments[1]);
            array.push_back(std::move(object));
        } break;
        case hashString("rect_vector", 11): {
            auto& array = *FOCV_JsiObject::get_from_wrap<std::vector<cv::Rect>>(runtime, arguments[0]);
            auto& object = *FOCV_JsiObject::get_from_wrap<cv::Rect>(runtime, arguments[1]);
            array.push_back(object);
        } break;
        case hashString("point_vector", 12): {
            auto& array = *FOCV_JsiObject::get_from_wrap<std::vector<cv::Point>>(runtime, arguments[0]);
            auto& object = *FOCV_JsiObject::get_from_wrap<cv::Point>(runtime, arguments[1]);
            array.push_back(object);
        } break;
        case hashString("point_vector_vector", 19): {
            auto& array = *FOCV_JsiObject::get_from_wrap<std::vector<std::vector<cv::Point>>>(runtime, arguments[0]);
            auto& object = *FOCV_JsiObject::get_from_wrap<std::vector<cv::Point>>(runtime, arguments[1]);
            array.push_back(object);
        } break;
    }
}

