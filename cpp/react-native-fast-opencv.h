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

using namespace facebook;

class OpenCVPlugin : public jsi::HostObject {
private:
    std::shared_ptr<react::CallInvoker> _callInvoker;
    static std::unordered_map<std::string, cv::Mat> _matrices;
    
public:
    explicit OpenCVPlugin(std::shared_ptr<react::CallInvoker> callInvoker);
    
    static void installOpenCV(jsi::Runtime& runtime, std::shared_ptr<react::CallInvoker> callInvoker);
    
    jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& name) override;
    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& runtime) override;
    
private:
    void clear();
    
    jsi::String frameBufferToMat(jsi::Runtime& runtime, jsi::Value rows, jsi::Value cols, jsi::Object input);
};

#endif /* FASTOPENCV_H */
