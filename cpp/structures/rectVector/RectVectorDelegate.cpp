#include "RectVectorDelegate.h"

jsi::Value RectVectorDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("get", 3): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "get"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto rectVectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::Rect>>>(object);
              auto rect = rectVectorPtr->at(args[0].asNumber());
              return FOCV_JsiObject::wrap(runtime, "rect", std::make_shared<decltype(rect)>(rect));
          }
      );
    }
    case hashString("getAll", 6): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "get"), 0,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto rectVectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::Rect>>>(object);
              auto array = jsi::Array(runtime, rectVectorPtr->size());
            
              for (size_t i = 0; i < rectVectorPtr->size(); i++) {
                  auto rect = rectVectorPtr->at(i);
                  auto wrappedRect = FOCV_JsiObject::wrap(runtime, "rect", std::make_shared<decltype(rect)>(rect));
                  array.setValueAtIndex(runtime, i, wrappedRect);
              }
            
              return array;
          }
      );
    } break;
    case hashString("push", 4): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "push"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto rectVectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::Rect>>>(object);
              auto& object = *FOCV_JsiObject::get_from_wrap<cv::Rect>(runtime, args[0]);
              rectVectorPtr->push_back(std::move(object));
              FOCV_JsiObject::updateExternalMemoryPressure(runtime, thisVal);

              return jsi::Value(true);
          }
      );
    } break;
    case hashString("length", 6): {
      auto matPtr = std::any_cast<std::shared_ptr<std::vector<cv::Rect>>>(object);
      return jsi::Value((int)matPtr->size());
    } break;
  }
  
  return jsi::Value::undefined();
}
  
std::vector<jsi::PropNameID> RectVectorDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "get"));
  result.push_back(jsi::PropNameID::forAscii(rt, "getAll"));
  result.push_back(jsi::PropNameID::forAscii(rt, "push"));
  result.push_back(jsi::PropNameID::forAscii(rt, "length"));
  return result;
}

size_t RectVectorDelegate::getExternalMemorySize(const std::any& object) {
  auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::Rect>>>(&object);
  if (vectorPtr == nullptr || *vectorPtr == nullptr) {
    return 0;
  }
  return (*vectorPtr)->capacity() * sizeof(cv::Rect);
}

