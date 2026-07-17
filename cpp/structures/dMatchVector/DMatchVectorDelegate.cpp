#include "DMatchVectorDelegate.h"

// DMatches are plain value data, exposed to JS directly as objects.
static jsi::Object dMatchToObject(jsi::Runtime& rt, const cv::DMatch& match) {
  jsi::Object item(rt);
  item.setProperty(rt, "queryIdx", jsi::Value(match.queryIdx));
  item.setProperty(rt, "trainIdx", jsi::Value(match.trainIdx));
  item.setProperty(rt, "imgIdx", jsi::Value(match.imgIdx));
  item.setProperty(rt, "distance", jsi::Value((double)match.distance));
  return item;
}

jsi::Value DMatchVectorDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("get", 3): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "get"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::DMatch>>>(object);
              return dMatchToObject(runtime, vectorPtr->at(args[0].asNumber()));
          }
      );
    } break;
    case hashString("toArray", 7): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "toArray"), 0,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::DMatch>>>(object);
              auto array = jsi::Array(runtime, vectorPtr->size());
              for (size_t i = 0; i < vectorPtr->size(); i++) {
                  array.setValueAtIndex(runtime, i, dMatchToObject(runtime, vectorPtr->at(i)));
              }
              return array;
          }
      );
    } break;
    case hashString("length", 6): {
      auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::DMatch>>>(object);
      return jsi::Value((int)vectorPtr->size());
    } break;
  }

  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> DMatchVectorDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "get"));
  result.push_back(jsi::PropNameID::forAscii(rt, "toArray"));
  result.push_back(jsi::PropNameID::forAscii(rt, "length"));
  return result;
}

size_t DMatchVectorDelegate::getExternalMemorySize(const std::any& object) {
  auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<cv::DMatch>>>(&object);
  if (vectorPtr == nullptr || *vectorPtr == nullptr) {
    return 0;
  }
  return (*vectorPtr)->capacity() * sizeof(cv::DMatch);
}
