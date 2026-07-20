#include "DMatchVectorVectorDelegate.h"

static jsi::Object dMatchToObject(jsi::Runtime& rt, const cv::DMatch& match) {
  jsi::Object item(rt);
  item.setProperty(rt, "queryIdx", jsi::Value(match.queryIdx));
  item.setProperty(rt, "trainIdx", jsi::Value(match.trainIdx));
  item.setProperty(rt, "imgIdx", jsi::Value(match.imgIdx));
  item.setProperty(rt, "distance", jsi::Value((double)match.distance));
  return item;
}

static jsi::Array dMatchesToArray(jsi::Runtime& rt, const std::vector<cv::DMatch>& matches) {
  auto array = jsi::Array(rt, matches.size());
  for (size_t j = 0; j < matches.size(); j++) {
    array.setValueAtIndex(rt, j, dMatchToObject(rt, matches.at(j)));
  }
  return array;
}

jsi::Value DMatchVectorVectorDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("get", 3): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "get"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<std::vector<cv::DMatch>>>>(object);
              return dMatchesToArray(runtime, vectorPtr->at(args[0].asNumber()));
          }
      );
    } break;
    case hashString("toArray", 7): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "toArray"), 0,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<std::vector<cv::DMatch>>>>(object);
              auto outerArray = jsi::Array(runtime, vectorPtr->size());
              for (size_t i = 0; i < vectorPtr->size(); i++) {
                  outerArray.setValueAtIndex(runtime, i, dMatchesToArray(runtime, vectorPtr->at(i)));
              }
              return outerArray;
          }
      );
    } break;
    case hashString("length", 6): {
      auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<std::vector<cv::DMatch>>>>(object);
      return jsi::Value((int)vectorPtr->size());
    } break;
  }

  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> DMatchVectorVectorDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "get"));
  result.push_back(jsi::PropNameID::forAscii(rt, "toArray"));
  result.push_back(jsi::PropNameID::forAscii(rt, "length"));
  return result;
}

size_t DMatchVectorVectorDelegate::getExternalMemorySize(const std::any& object) {
  auto vectorPtr = std::any_cast<std::shared_ptr<std::vector<std::vector<cv::DMatch>>>>(&object);
  if (vectorPtr == nullptr || *vectorPtr == nullptr) {
    return 0;
  }
  size_t size = (*vectorPtr)->capacity() * sizeof(std::vector<cv::DMatch>);
  for (const auto& inner : **vectorPtr) {
    size += inner.capacity() * sizeof(cv::DMatch);
  }
  return size;
}
