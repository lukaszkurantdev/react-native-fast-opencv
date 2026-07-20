#include "RotatedRectDelegate.h"

jsi::Value RotatedRectDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("x", 1): {
      auto rectPtr = std::any_cast<std::shared_ptr<cv::RotatedRect>>(object);
      return jsi::Value(rectPtr->center.x);
    } break;
    case hashString("y", 1): {
      auto rectPtr = std::any_cast<std::shared_ptr<cv::RotatedRect>>(object);
      return jsi::Value(rectPtr->center.y);
    } break;
    case hashString("width", 5): {
      auto rectPtr = std::any_cast<std::shared_ptr<cv::RotatedRect>>(object);
      return jsi::Value(rectPtr->size.width);
    } break;
    case hashString("height", 6): {
      auto rectPtr = std::any_cast<std::shared_ptr<cv::RotatedRect>>(object);
      return jsi::Value(rectPtr->size.height);
    } break;
    case hashString("angle", 5): {
      auto rectPtr = std::any_cast<std::shared_ptr<cv::RotatedRect>>(object);
      return jsi::Value(rectPtr->angle);
    } break;
  }
  
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> RotatedRectDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "x"));
  result.push_back(jsi::PropNameID::forAscii(rt, "y"));
  result.push_back(jsi::PropNameID::forAscii(rt, "width"));
  result.push_back(jsi::PropNameID::forAscii(rt, "height"));
  result.push_back(jsi::PropNameID::forAscii(rt, "angle"));
  return result;
}

