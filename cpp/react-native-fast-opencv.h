#ifndef FASTOPENCV_H
#define FASTOPENCV_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

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

#ifdef ANDROID
#include <ReactCommon/CallInvoker.h>
#else
#include <React-callinvoker/ReactCommon/CallInvoker.h>
#endif

#include "MatFactory.h"
#include "MatVectorFactory.h"
#include "RectFactory.h"
#include "RectVectorFactory.h"
#include "PointFactory.h"
#include "PointVectorFactory.h"
#include "Point2fFactory.h"
#include "Point2fVectorFactory.h"
#include "PointVectorVectorFactory.h"
#include "SizeFactory.h"
#include "Vec3bFactory.h"
#include "ScalarFactory.h"
#include "RotatedRectFactory.h"
#include "TermCriteriaFactory.h"

using namespace facebook;

class OpenCVPlugin : public jsi::HostObject {
private:
    std::shared_ptr<react::CallInvoker> _callInvoker;
  
    std::shared_ptr<MatFactory> matFactory;
    std::shared_ptr<MatVectorFactory> matVectorFactory;
    std::shared_ptr<RectFactory> rectFactory;
    std::shared_ptr<RectVectorFactory> rectVectorFactory;
    std::shared_ptr<PointFactory> pointFactory;
    std::shared_ptr<PointVectorFactory> pointVectorFactory;
    std::shared_ptr<Point2fFactory> point2fFactory;
    std::shared_ptr<Point2fVectorFactory> point2fVectorFactory;
    std::shared_ptr<PointVectorVectorFactory> pointVectorVectorFactory;
    std::shared_ptr<SizeFactory> sizeFactory;
    std::shared_ptr<Vec3bFactory> vec3bFactory;
    std::shared_ptr<ScalarFactory> scalarFactory;
    std::shared_ptr<RotatedRectFactory> rotatedRectFactory;
    std::shared_ptr<TermCriteriaFactory> termCriteriaFactory;
  
public:
    explicit OpenCVPlugin(std::shared_ptr<react::CallInvoker> callInvoker);
    static void installOpenCV(jsi::Runtime& runtime, std::shared_ptr<react::CallInvoker> callInvoker);
    
    jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& name) override;
    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& runtime) override;
};

#endif /* FASTOPENCV_H */
