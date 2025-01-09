//
//  FOCV_FunctionArguments.hpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 20/08/2024.
//

#ifndef FOCV_FunctionArguments_hpp
#define FOCV_FunctionArguments_hpp

#include <jsi/jsilib.h>
#include <jsi/jsi.h>
#include <stdio.h>

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

using namespace facebook;

class FOCV_FunctionArguments {
private:
    const jsi::Value* arguments;
    jsi::Runtime* runtime;
    size_t count;

    inline void assertIndex(int index) {
        if (index < 0 || index >= count) {
            throw std::runtime_error("Fast OpenCV Error: Argument index (" + std::to_string(index) + ") is out of bounds!");
        }
    }

public:
    FOCV_FunctionArguments(jsi::Runtime& runtime, const jsi::Value* arguments, size_t count);

    double asNumber(int index);
    bool asBool(int index);
    std::string asString(int index);
    std::shared_ptr<cv::Mat> asMatPtr(int index);
    std::shared_ptr<std::vector<cv::Mat>> asMatVectorPtr(int index);
    std::shared_ptr<cv::Point> asPointPtr(int index);
    std::shared_ptr<std::vector<cv::Point>> asPointVectorPtr(int index);
    std::shared_ptr<std::vector<cv::Point2f>> asPoint2fVectorPtr(int index);
    std::shared_ptr<std::vector<std::vector<cv::Point>>> asPointVectorOfVectorsPtr(int index);
    std::shared_ptr<cv::Rect> asRectPtr(int index);
    std::shared_ptr<std::vector<cv::Rect>> asRectVectorPtr(int index);
    std::shared_ptr<cv::Size> asSizePtr(int index);
    std::shared_ptr<cv::Scalar> asScalarPtr(int index);
    std::shared_ptr<cv::RotatedRect> asRotatedRectPtr(int index);
    std::shared_ptr<cv::TermCriteria> asTermCriteriaPtr(int index);
    
    bool isNumber(int index);
    bool isBool(int index);
    bool isString(int index);
    bool isObject(int index);
    bool isMat(int index);
    bool isMatVector(int index);
    bool isPoint(int index);
    bool isPointVector(int index);
    bool isPoint2fVector(int index);
    bool isPointVectorOfVectors(int index);
    bool isRect(int index);
    bool isRectVector(int index);
    bool isSize(int index);
    bool isScalar(int index);
    bool isRotatedRect(int index);
    bool isTermCriteria(int index);
};

#endif /* FOCV_FunctionArguments_hpp */
