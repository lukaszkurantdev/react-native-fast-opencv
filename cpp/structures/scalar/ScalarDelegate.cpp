#include "ScalarDelegate.h"

jsi::Value ScalarDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("a", 1): {
      auto ptr = std::any_cast<std::shared_ptr<cv::Scalar>>(object);
      return jsi::Value(ptr->val[0]);
    } break;
    case hashString("b", 1): {
      auto ptr = std::any_cast<std::shared_ptr<cv::Scalar>>(object);
      return jsi::Value(ptr->val[1]);
    } break;
    case hashString("c", 1): {
      auto ptr = std::any_cast<std::shared_ptr<cv::Scalar>>(object);
      return jsi::Value(ptr->val[2]);
    } break;
    case hashString("d", 1): {
      auto ptr = std::any_cast<std::shared_ptr<cv::Scalar>>(object);
      return jsi::Value(ptr->val[3]);
    } break;
  }
  
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> ScalarDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "a"));
  result.push_back(jsi::PropNameID::forAscii(rt, "b"));
  result.push_back(jsi::PropNameID::forAscii(rt, "c"));
  result.push_back(jsi::PropNameID::forAscii(rt, "d"));
  return result;
}

