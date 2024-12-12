//
//  FOCV_FunctionArguments.cpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 20/08/2024.
//

#include "FOCV_FunctionArguments.hpp"
#include <opencv2/opencv.hpp>
#include "FOCV_Storage.hpp"
#include "FOCV_JsiObject.hpp"

FOCV_FunctionArguments::FOCV_FunctionArguments(jsi::Runtime& runtime, const jsi::Value* arguments, size_t count) {
    this->arguments = arguments;
    this->runtime = &runtime;
    this->count = count;
}

double FOCV_FunctionArguments::asNumber(int index) {
    if (!this->isNumber(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a number!");
    }
    return this->arguments[index].asNumber();
}

bool FOCV_FunctionArguments::asBool(int index) {
    if (!this->isBool(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a boolean!");
    }
    return this->arguments[index].asBool();
}

std::string FOCV_FunctionArguments::asString(int index) {
    if (!this->isString(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a string!");
    }
    return this->arguments[index].asString(*this->runtime).utf8(*this->runtime);
}

std::shared_ptr<cv::Mat> FOCV_FunctionArguments::asMatPtr(int index) {
    if (!this->isMat(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a Mat!");
    }
    return FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<std::vector<cv::Mat>> FOCV_FunctionArguments::asMatVectorPtr(int index) {
    if (!this->isMatVector(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a MatVector!");
    }
    return FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<cv::Point> FOCV_FunctionArguments::asPointPtr(int index) {
    if (!this->isPoint(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a Point!");
    }
    return FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<std::vector<cv::Point>> FOCV_FunctionArguments::asPointVectorPtr(int index) {
    if (!this->isPointVector(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a PointVector!");
    }
    return FOCV_Storage::get<std::vector<cv::Point>>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<std::vector<cv::Point2f>> FOCV_FunctionArguments::asPoint2fVectorPtr(int index) {
    if (!this->isPoint2fVector(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a Point2fVector!");
    }
    return FOCV_Storage::get<std::vector<cv::Point2f>>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<std::vector<std::vector<cv::Point>>> FOCV_FunctionArguments::asPointVectorOfVectorsPtr(int index) {
    if (!this->isPointVectorOfVectors(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a PointVectorOfVectors!");
    }
    return FOCV_Storage::get<std::vector<std::vector<cv::Point>>>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<cv::Rect> FOCV_FunctionArguments::asRectPtr(int index) {
    if (!this->isRect(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a Rect!");
    }
    return FOCV_Storage::get<cv::Rect>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<std::vector<cv::Rect>> FOCV_FunctionArguments::asRectVectorPtr(int index) {
    if (!this->isRectVector(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a RectVector!");
    }
    return FOCV_Storage::get<std::vector<cv::Rect>>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<cv::Size> FOCV_FunctionArguments::asSizePtr(int index) {
    if (!this->isSize(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a Size!");
    }
    return FOCV_Storage::get<cv::Size>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<cv::Scalar> FOCV_FunctionArguments::asScalarPtr(int index) {
    if (!this->isScalar(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a Scalar!");
    }
    return FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<cv::RotatedRect> FOCV_FunctionArguments::asRotatedRectPtr(int index) {
    if (!this->isRotatedRect(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a RotatedRect!");
    }
    return FOCV_Storage::get<cv::RotatedRect>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<cv::TermCriteria> FOCV_FunctionArguments::asTermCriteriaPtr(int index) {
    if (!this->isTermCriteria(index)) {
        throw std::runtime_error("Fast OpenCV Error: Argument (" + std::to_string(index) + ") is not a TermCriteria!");
    }
    return FOCV_Storage::get<cv::TermCriteria>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

bool FOCV_FunctionArguments::isNumber(int index) {
    this->assertIndex(index);
    return this->arguments[index].isNumber();
}

bool FOCV_FunctionArguments::isBool(int index) {
    this->assertIndex(index);
    return this->arguments[index].isBool();
}

bool FOCV_FunctionArguments::isString(int index) {
    this->assertIndex(index);
    return this->arguments[index].isString();
}

bool FOCV_FunctionArguments::isObject(int index) {
    this->assertIndex(index);
    return this->arguments[index].isObject();
}

bool FOCV_FunctionArguments::isMat(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "mat";
}

bool FOCV_FunctionArguments::isMatVector(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "mat_vector";
}

bool FOCV_FunctionArguments::isPoint(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "point";
}

bool FOCV_FunctionArguments::isPointVector(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "point_vector";
}

bool FOCV_FunctionArguments::isPoint2fVector(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "point2f_vector";
}

bool FOCV_FunctionArguments::isPointVectorOfVectors(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "point_vector_vector";
}

bool FOCV_FunctionArguments::isRect(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "rect";
}

bool FOCV_FunctionArguments::isRectVector(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "rect_vector";
}

bool FOCV_FunctionArguments::isSize(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "size";
}

bool FOCV_FunctionArguments::isScalar(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "scalar";
}

bool FOCV_FunctionArguments::isRotatedRect(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "rotated_rect";
}

bool FOCV_FunctionArguments::isTermCriteria(int index) {
    return this->isObject(index) && FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "term_criteria";
}


