#include "RectFactory.h"

jsi::Value RectFactory::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);

  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("create", 6): {
      return jsi::Function::createFromHostFunction(
         runtime,
         propNameId,
         4,
         [](jsi::Runtime& rt, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
           auto x = static_cast<int>(args[0].asNumber());
           auto y = static_cast<int>(args[1].asNumber());
           auto width  = static_cast<int>(args[2].asNumber());
           auto height = static_cast<int>(args[3].asNumber());
           
           cv::Rect object(x, y, width, height);
           
           return FOCV_JsiObject::wrap(rt, "rect", std::make_shared<decltype(object)>(object));
         }
      );
    } break;
  }
  
 
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> RectFactory::getPropertyNames(jsi::Runtime& rt) {
    std::vector<jsi::PropNameID> names;
    names.push_back(jsi::PropNameID::forUtf8(rt, "create"));
    return names;
}

