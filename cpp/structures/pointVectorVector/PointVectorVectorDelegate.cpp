#include "PointVectorVectorDelegate.h"

jsi::Value PointVectorVectorDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("get", 3): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "get"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto pointVectorPtr = std::any_cast<std::shared_ptr<std::vector<std::vector<cv::Point>>>>(object);
              auto point = pointVectorPtr->at(args[0].asNumber());
              return FOCV_JsiObject::wrap(runtime, "point_vector", std::make_shared<decltype(point)>(point));
          }
      );
    }
    case hashString("getAll", 6): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "get"), 0,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto pointVectorPtr = std::any_cast<std::shared_ptr<std::vector<std::vector<cv::Point>>>>(object);
              auto array = jsi::Array(runtime, pointVectorPtr->size());
            
              for (size_t i = 0; i < pointVectorPtr->size(); i++) {
                  auto point = pointVectorPtr->at(i);
                  auto wrapped = FOCV_JsiObject::wrap(runtime, "point_vector", std::make_shared<decltype(point)>(point));
                  array.setValueAtIndex(runtime, i, wrapped);
              }
            
              return array;
          }
      );
    } break;
    case hashString("push", 4): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "push"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto pointVectorPtr = std::any_cast<std::shared_ptr<std::vector<std::vector<cv::Point>>>>(object);
              auto& object = *FOCV_JsiObject::get_from_wrap<std::vector<cv::Point>>(runtime, args[0]);
              pointVectorPtr->push_back(std::move(object));
              FOCV_JsiObject::updateExternalMemoryPressure(runtime, thisVal);

              return jsi::Value(true);
          }
      );
    } break;
    case hashString("length", 6): {
      auto matPtr = std::any_cast<std::shared_ptr<std::vector<std::vector<cv::Point>>>>(object);
      return jsi::Value((int)matPtr->size());
    } break;
  }
  
  return jsi::Value::undefined();
}
  
std::vector<jsi::PropNameID> PointVectorVectorDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "get"));
  result.push_back(jsi::PropNameID::forAscii(rt, "getAll"));
  result.push_back(jsi::PropNameID::forAscii(rt, "push"));
  result.push_back(jsi::PropNameID::forAscii(rt, "length"));
  return result;
}

size_t PointVectorVectorDelegate::getExternalMemorySize(const std::any& object) {
  auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<std::vector<cv::Point>>>>(&object);
  if (vectorPtr == nullptr || *vectorPtr == nullptr) {
    return 0;
  }
  size_t size = (*vectorPtr)->capacity() * sizeof(std::vector<cv::Point>);
  for (const auto& points : **vectorPtr) {
    size += points.capacity() * sizeof(cv::Point);
  }
  return size;
}

