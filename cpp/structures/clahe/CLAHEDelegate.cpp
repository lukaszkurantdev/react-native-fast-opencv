#include "CLAHEDelegate.h"
#include "FOCV_JsiObject.hpp"

jsi::Value CLAHEDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("apply", 5): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "apply"), 2,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto clahePtr = std::any_cast<std::shared_ptr<cv::Ptr<cv::CLAHE>>>(object);
              auto src = FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[0]);
              auto dst = FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[1]);

              (*clahePtr)->apply(*src, *dst);
              FOCV_JsiObject::updateExternalMemoryPressure(runtime, args[1]);

              return jsi::Value::undefined();
          }
      );
    } break;
    case hashString("getClipLimit", 12): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "getClipLimit"), 0,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto clahePtr = std::any_cast<std::shared_ptr<cv::Ptr<cv::CLAHE>>>(object);
              return jsi::Value((*clahePtr)->getClipLimit());
          }
      );
    } break;
    case hashString("setClipLimit", 12): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "setClipLimit"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto clahePtr = std::any_cast<std::shared_ptr<cv::Ptr<cv::CLAHE>>>(object);
              (*clahePtr)->setClipLimit(args[0].asNumber());

              return jsi::Value::undefined();
          }
      );
    } break;
    case hashString("getTilesGridSize", 16): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "getTilesGridSize"), 0,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto clahePtr = std::any_cast<std::shared_ptr<cv::Ptr<cv::CLAHE>>>(object);
              auto size = (*clahePtr)->getTilesGridSize();
              return FOCV_JsiObject::wrap(runtime, "size", std::make_shared<cv::Size>(size));
          }
      );
    } break;
    case hashString("setTilesGridSize", 16): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "setTilesGridSize"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto clahePtr = std::any_cast<std::shared_ptr<cv::Ptr<cv::CLAHE>>>(object);
              auto size = FOCV_JsiObject::get_from_wrap<cv::Size>(runtime, args[0]);
              (*clahePtr)->setTilesGridSize(*size);

              return jsi::Value::undefined();
          }
      );
    } break;
    case hashString("collectGarbage", 14): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "collectGarbage"), 0,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto clahePtr = std::any_cast<std::shared_ptr<cv::Ptr<cv::CLAHE>>>(object);
              (*clahePtr)->collectGarbage();

              return jsi::Value::undefined();
          }
      );
    } break;
  }

  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> CLAHEDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "apply"));
  result.push_back(jsi::PropNameID::forAscii(rt, "getClipLimit"));
  result.push_back(jsi::PropNameID::forAscii(rt, "setClipLimit"));
  result.push_back(jsi::PropNameID::forAscii(rt, "getTilesGridSize"));
  result.push_back(jsi::PropNameID::forAscii(rt, "setTilesGridSize"));
  result.push_back(jsi::PropNameID::forAscii(rt, "collectGarbage"));
  return result;
}
