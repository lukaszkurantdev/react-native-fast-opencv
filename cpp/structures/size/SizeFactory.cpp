#include "SizeFactory.h"

jsi::Value SizeFactory::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);

  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("create", 6): {
      return jsi::Function::createFromHostFunction(
         runtime,
         propNameId,
         2,
         [](jsi::Runtime& rt, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
           auto width = static_cast<int>(args[0].asNumber());
           auto height = static_cast<int>(args[1].asNumber());
           
           cv::Size object(width, height);
           
           return FOCV_JsiObject::wrap(rt, "size", std::make_shared<decltype(object)>(object));
         }
      );
    } break;
  }
  
 
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> SizeFactory::getPropertyNames(jsi::Runtime& rt) {
    std::vector<jsi::PropNameID> names;
    names.push_back(jsi::PropNameID::forUtf8(rt, "create"));
    return names;
}

