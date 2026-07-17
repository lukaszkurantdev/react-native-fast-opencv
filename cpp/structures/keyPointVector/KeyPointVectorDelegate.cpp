#include "KeyPointVectorDelegate.h"

static jsi::Object keyPointToObject(jsi::Runtime& rt, const cv::KeyPoint& kp) {
  jsi::Object item(rt);
  item.setProperty(rt, "x", jsi::Value((double)kp.pt.x));
  item.setProperty(rt, "y", jsi::Value((double)kp.pt.y));
  item.setProperty(rt, "size", jsi::Value((double)kp.size));
  item.setProperty(rt, "angle", jsi::Value((double)kp.angle));
  item.setProperty(rt, "response", jsi::Value((double)kp.response));
  item.setProperty(rt, "octave", jsi::Value(kp.octave));
  item.setProperty(rt, "classId", jsi::Value(kp.class_id));
  return item;
}

jsi::Value KeyPointVectorDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("get", 3): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "get"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::KeyPoint>>>(object);
              return keyPointToObject(runtime, vectorPtr->at(args[0].asNumber()));
          }
      );
    } break;
    case hashString("toArray", 7): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "toArray"), 0,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::KeyPoint>>>(object);
              auto array = jsi::Array(runtime, vectorPtr->size());
              for (size_t i = 0; i < vectorPtr->size(); i++) {
                  array.setValueAtIndex(runtime, i, keyPointToObject(runtime, vectorPtr->at(i)));
              }
              return array;
          }
      );
    } break;
    case hashString("length", 6): {
      auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::KeyPoint>>>(object);
      return jsi::Value((int)vectorPtr->size());
    } break;
  }

  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> KeyPointVectorDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "get"));
  result.push_back(jsi::PropNameID::forAscii(rt, "toArray"));
  result.push_back(jsi::PropNameID::forAscii(rt, "length"));
  return result;
}

size_t KeyPointVectorDelegate::getExternalMemorySize(const std::any& object) {
  auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::KeyPoint>>>(&object);
  if (vectorPtr == nullptr || *vectorPtr == nullptr) {
    return 0;
  }
  return (*vectorPtr)->capacity() * sizeof(cv::KeyPoint);
}
