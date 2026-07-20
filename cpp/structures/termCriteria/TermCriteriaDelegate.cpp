#include "TermCriteriaDelegate.h"

jsi::Value TermCriteriaDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("type", 4): {
      auto ptr = std::any_cast<std::shared_ptr<cv::TermCriteria>>(object);
      return jsi::Value(ptr->type);
    } break;
    case hashString("maxCount", 8): {
      auto ptr = std::any_cast<std::shared_ptr<cv::TermCriteria>>(object);
      return jsi::Value(ptr->maxCount);
    } break;
    case hashString("epsilon", 7): {
      auto ptr = std::any_cast<std::shared_ptr<cv::TermCriteria>>(object);
      return jsi::Value(ptr->epsilon);
    } break;
  }
  
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> TermCriteriaDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "type"));
  result.push_back(jsi::PropNameID::forAscii(rt, "maxCount"));
  result.push_back(jsi::PropNameID::forAscii(rt, "epsilon"));
  return result;
}

