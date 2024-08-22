#include <jni.h>
#include <jsi/jsi.h>

#include "react-native-fast-opencv.h"
#include <ReactCommon/CallInvokerHolder.h>

using namespace facebook;

extern "C"
JNIEXPORT void JNICALL
Java_com_fastopencv_FastOpencvModule_nativeInstall(JNIEnv *env, jobject thiz, jlong jsi_runtime_ref,
        jobject js_call_invoker_holder) {
        auto jsiRuntime{ reinterpret_cast<jsi::Runtime*>(jsi_runtime_ref) };
        auto jsCallInvoker{ jni::alias_ref<react::CallInvokerHolder::javaobject>{reinterpret_cast<react::CallInvokerHolder::javaobject>(js_call_invoker_holder) }->cthis()->getCallInvoker() };

        //    RNWorklet::JsiWorkletContext::getDefaultInstance()->initialize(
        //    "default", jsiRuntime, [=](std::function<void()> &&f) {
        //        jsCallInvoker->invokeAsync(std::move(f));
        //    });

        OpenCVPlugin::installOpenCV(*jsiRuntime, jsCallInvoker);
}
