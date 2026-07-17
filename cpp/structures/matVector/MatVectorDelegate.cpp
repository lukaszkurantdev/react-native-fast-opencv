#include "MatVectorDelegate.h"

jsi::Value MatVectorDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("get", 3): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "get"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto matVectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::Mat>>>(object);
              auto mat = matVectorPtr->at(args[0].asNumber());
              return FOCV_JsiObject::wrap(runtime, "mat", std::make_shared<decltype(mat)>(mat));
          }
      );
    } break;
    case hashString("push", 4): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "push"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto matVectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::Mat>>>(object);
              auto& object = *FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[0]);
              matVectorPtr->push_back(std::move(object));
              FOCV_JsiObject::updateExternalMemoryPressure(runtime, thisVal);

              return jsi::Value(true);
          }
      );
    } break;
    case hashString("length", 6): {
      auto matPtr = std::any_cast<std::shared_ptr<std::vector<cv::Mat>>>(object);
      return jsi::Value((int)matPtr->size());
    } break;
  }
  
  return jsi::Value::undefined();
}
  
std::vector<jsi::PropNameID> MatVectorDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "get"));
  result.push_back(jsi::PropNameID::forAscii(rt, "push"));
  result.push_back(jsi::PropNameID::forAscii(rt, "length"));
  return result;
}

size_t MatVectorDelegate::getExternalMemorySize(const std::any& object) {
  auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::Mat>>>(&object);
  if (vectorPtr == nullptr || *vectorPtr == nullptr) {
    return 0;
  }
  size_t size = (*vectorPtr)->capacity() * sizeof(cv::Mat);
  for (const auto& mat : **vectorPtr) {
    size += mat.total() * mat.elemSize();
  }
  return size;
}

