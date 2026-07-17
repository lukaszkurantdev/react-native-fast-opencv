#include "SizeDelegate.h"

jsi::Value SizeDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("width", 5): {
      auto ptr = std::any_cast<std::shared_ptr<cv::Size>>(object);
      return jsi::Value(ptr->width);
    } break;
    case hashString("height", 6): {
      auto ptr = std::any_cast<std::shared_ptr<cv::Size>>(object);
      return jsi::Value(ptr->height);
    } break;
  }
  
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> SizeDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "width"));
  result.push_back(jsi::PropNameID::forAscii(rt, "height"));
  return result;
}

