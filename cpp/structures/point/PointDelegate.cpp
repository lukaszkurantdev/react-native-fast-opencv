#include "PointDelegate.h"

jsi::Value PointDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("x", 1): {
      auto ptr = std::any_cast<std::shared_ptr<cv::Point>>(object);
      return jsi::Value(ptr->x);
    } break;
    case hashString("y", 1): {
      auto ptr = std::any_cast<std::shared_ptr<cv::Point>>(object);
      return jsi::Value(ptr->y);
    } break;
  }
  
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> PointDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "x"));
  result.push_back(jsi::PropNameID::forAscii(rt, "y"));
  return result;
}

