#include "Vec3bFactory.h"

jsi::Value Vec3bFactory::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);

  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("create", 6): {
      return jsi::Function::createFromHostFunction(
         runtime,
         propNameId,
         3,
         [](jsi::Runtime& rt, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
           auto a = static_cast<int>(args[0].asNumber());
           auto b = static_cast<int>(args[1].asNumber());
           auto c = static_cast<int>(args[1].asNumber());
           
           cv::Vec3b object(a, b, c);
           
           return FOCV_JsiObject::wrap(rt, "vec3b", std::make_shared<decltype(object)>(object));
         }
      );
    } break;
  }
  
 
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> Vec3bFactory::getPropertyNames(jsi::Runtime& rt) {
    std::vector<jsi::PropNameID> names;
    names.push_back(jsi::PropNameID::forUtf8(rt, "create"));
    return names;
}

