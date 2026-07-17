#include <iostream>
#include <filesystem>

#include "react-native-fast-opencv.h"
#include "jsi/Promise.h"
#include "jsi/TypedArray.h"
#include <FOCV_Function.hpp>
#include "FOCV_Object.hpp"
#include "ConvertImage.hpp"
#include "FOCV_JsiObject.hpp"
#include "opencv2/opencv.hpp"

using namespace mrousavy;

void OpenCVPlugin::installOpenCV(jsi::Runtime& runtime, std::shared_ptr<react::CallInvoker> callInvoker) {

    auto func = [=](jsi::Runtime& runtime,
                        const jsi::Value& thisArg,
                        const jsi::Value* args,
                        size_t count) -> jsi::Value {
        auto plugin = std::make_shared<OpenCVPlugin>(callInvoker);
        auto result = jsi::Object::createFromHostObject(runtime, plugin);

        return result;
    };

    auto jsiFunc = jsi::Function::createFromHostFunction(runtime,
        jsi::PropNameID::forUtf8(runtime, "__loadOpenCV"),
        1,
        func);

    runtime.global().setProperty(runtime, "__loadOpenCV", jsiFunc);
}

OpenCVPlugin::OpenCVPlugin(std::shared_ptr<react::CallInvoker> callInvoker) : _callInvoker(callInvoker) {
  matFactory = std::make_shared<MatFactory>();
  matVectorFactory = std::make_shared<MatVectorFactory>();
  rectFactory = std::make_shared<RectFactory>();
  rectVectorFactory = std::make_shared<RectVectorFactory>();
  pointFactory = std::make_shared<PointFactory>();
  pointVectorFactory = std::make_shared<PointVectorFactory>();
  point2fFactory = std::make_shared<Point2fFactory>();
  point2fVectorFactory = std::make_shared<Point2fVectorFactory>();
  pointVectorVectorFactory = std::make_shared<PointVectorVectorFactory>();
  sizeFactory = std::make_shared<SizeFactory>();
  vec3bFactory = std::make_shared<Vec3bFactory>();
  scalarFactory = std::make_shared<ScalarFactory>();
  rotatedRectFactory = std::make_shared<RotatedRectFactory>();
  termCriteriaFactory = std::make_shared<TermCriteriaFactory>();
}

jsi::Value OpenCVPlugin::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);
  
  if (propName == "Mat") return jsi::Object::createFromHostObject(runtime, matFactory);
  if (propName == "MatVector") return jsi::Object::createFromHostObject(runtime, matVectorFactory);
  if (propName == "Rect") return jsi::Object::createFromHostObject(runtime, rectFactory);
  if (propName == "RectVector") return jsi::Object::createFromHostObject(runtime, rectVectorFactory);
  if (propName == "Point") return jsi::Object::createFromHostObject(runtime, pointFactory);
  if (propName == "PointVector") return jsi::Object::createFromHostObject(runtime, pointVectorFactory);
  if (propName == "PointVectorOfVectors") return jsi::Object::createFromHostObject(runtime, pointVectorVectorFactory);
  if (propName == "Point2f") return jsi::Object::createFromHostObject(runtime, point2fFactory);
  if (propName == "Point2fVector") return jsi::Object::createFromHostObject(runtime, point2fVectorFactory);
  if (propName == "Size") return jsi::Object::createFromHostObject(runtime, sizeFactory);
  if (propName == "Vec3b") return jsi::Object::createFromHostObject(runtime, vec3bFactory);
  if (propName == "Scalar") return jsi::Object::createFromHostObject(runtime, scalarFactory);
  if (propName == "RotatedRect") return jsi::Object::createFromHostObject(runtime, rotatedRectFactory);
  if (propName == "TermCriteria") return jsi::Object::createFromHostObject(runtime, termCriteriaFactory);
  
  return jsi::Function::createFromHostFunction(
      runtime, jsi::PropNameID::forAscii(runtime, propName), 0,
      [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
          size_t count) -> jsi::Object {

      std::vector<jsi::Value> newArgs;
      newArgs.reserve(count + 1);
      newArgs.push_back(jsi::String::createFromUtf8(runtime, propName));
      for (size_t i = 0; i < count; i++) {
          newArgs.push_back(jsi::Value(runtime, arguments[i]));
      }

      auto result = FOCV_Function::invoke(runtime, newArgs.data(), newArgs.size());

      // OpenCV writes into wrapped output arguments in place, so the native
      // size they hold may have changed — keep the GC's view up to date.
      for (size_t i = 0; i < count; i++) {
          FOCV_JsiObject::updateExternalMemoryPressure(runtime, arguments[i]);
      }

      return result;
  });
}

std::vector<jsi::PropNameID> OpenCVPlugin::getPropertyNames(jsi::Runtime& runtime) {
    std::vector<jsi::PropNameID> result;

    result.push_back(jsi::PropNameID::forAscii(runtime, "Mat"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "MatVector"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "Rect"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "RectVector"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "Point"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "PointVector"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "PointVectorOfVectors"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "Point2f"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "Point2fVector"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "Size"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "Vec3b"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "Scalar"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "RotatedRect"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "TermCriteria"));

    return result;
}
