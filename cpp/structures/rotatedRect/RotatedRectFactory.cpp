#include "RotatedRectFactory.h"

jsi::Value RotatedRectFactory::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);

  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("create", 6): {
      return jsi::Function::createFromHostFunction(
         runtime,
         propNameId,
         5,
         [](jsi::Runtime& rt, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
           auto x = static_cast<int>(args[0].asNumber());
           auto y = static_cast<int>(args[1].asNumber());
           auto width  = static_cast<int>(args[2].asNumber());
           auto height = static_cast<int>(args[3].asNumber());
           auto angle = static_cast<float>(args[4].asNumber());
           
           cv::RotatedRect object(cv::Point(x,y), cv::Size(width, height), angle);
           
           return FOCV_JsiObject::wrap(rt, "rotated_rect", std::make_shared<decltype(object)>(object));
         }
      );
    } break;
  }
 
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> RotatedRectFactory::getPropertyNames(jsi::Runtime& rt) {
    std::vector<jsi::PropNameID> names;
    names.push_back(jsi::PropNameID::forUtf8(rt, "create"));
    return names;
}

