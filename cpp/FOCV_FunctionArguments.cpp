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

FOCV_FunctionArguments::FOCV_FunctionArguments(jsi::Runtime& runtime, const jsi::Value* arguments) {
    this->arguments = arguments;
    this->runtime = &runtime;
}

double FOCV_FunctionArguments::asNumber(int index) {
    return this->arguments[index].asNumber();
}

bool FOCV_FunctionArguments::asBool(int index) {
    return this->arguments[index].asBool();
}

std::string FOCV_FunctionArguments::asString(int index) {
    return this->arguments[index].asString(*this->runtime).utf8(*this->runtime);
}

std::shared_ptr<cv::Mat> FOCV_FunctionArguments::asMatPtr(int index) {
    return FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<std::vector<cv::Mat>> FOCV_FunctionArguments::asMatVectorPtr(int index) {
    return FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<cv::Point> FOCV_FunctionArguments::asPointPtr(int index) {
    return FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<std::vector<cv::Point>> FOCV_FunctionArguments::asPointVectorPtr(int index) {
    return FOCV_Storage::get<std::vector<cv::Point>>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<std::vector<cv::Point2f>> FOCV_FunctionArguments::asPoint2fVectorPtr(int index) {
    return FOCV_Storage::get<std::vector<cv::Point2f>>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<std::vector<std::vector<cv::Point>>> FOCV_FunctionArguments::asPointVectorOfVectorsPtr(int index) {
    return FOCV_Storage::get<std::vector<std::vector<cv::Point>>>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<cv::Rect> FOCV_FunctionArguments::asRectPtr(int index) {
    return FOCV_Storage::get<cv::Rect>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<std::vector<cv::Rect>> FOCV_FunctionArguments::asRectVectorPtr(int index) {
    return FOCV_Storage::get<std::vector<cv::Rect>>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<cv::Size> FOCV_FunctionArguments::asSizePtr(int index) {
    return FOCV_Storage::get<cv::Size>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<cv::Scalar> FOCV_FunctionArguments::asScalarPtr(int index) {
    return FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

std::shared_ptr<cv::RotatedRect> FOCV_FunctionArguments::asRotatedRectPtr(int index) {
    return FOCV_Storage::get<cv::RotatedRect>(FOCV_JsiObject::id_from_wrap(*this->runtime, arguments[index]));
}

bool FOCV_FunctionArguments::isNumber(int index) {
    return this->arguments[index].isNumber();
}

bool FOCV_FunctionArguments::isBool(int index) {
    return this->arguments[index].isNumber();
}

bool FOCV_FunctionArguments::isString(int index) {
    return this->arguments[index].isNumber();
}

bool FOCV_FunctionArguments::isObject(int index) {
    return this->arguments[index].isNumber();
}

bool FOCV_FunctionArguments::isMat(int index) {
    return FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "mat";
}

bool FOCV_FunctionArguments::isMatVector(int index) {
    return FOCV_JsiObject::type_from_wrap(*this->runtime, arguments[index]) == "mat_vector";
}
