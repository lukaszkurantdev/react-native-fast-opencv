#include "ScalarFactory.h"

jsi::Value ScalarFactory::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);

  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("create", 6): {
      return jsi::Function::createFromHostFunction(
         runtime,
         propNameId,
         3,
         [](jsi::Runtime& rt, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
           if (count > 3 && args[3].isNumber()) {
               auto a = args[0].asNumber();
               auto b = args[1].asNumber();
               auto c = args[2].asNumber();
               auto d = args[3].asNumber();

               cv::Scalar object(a, b, c, d);
               return FOCV_JsiObject::wrap(rt, "scalar", std::make_shared<decltype(object)>(object));
           } else if(count > 2 && args[2].isNumber()) {
               auto a = args[0].asNumber();
               auto b = args[1].asNumber();
               auto c = args[2].asNumber();

               cv::Scalar object(a, b, c);
               return FOCV_JsiObject::wrap(rt, "scalar", std::make_shared<decltype(object)>(object));
           } else {
               auto a = args[0].asNumber();
               cv::Scalar object(a);
               return FOCV_JsiObject::wrap(rt, "scalar", std::make_shared<decltype(object)>(object));
           }
         }
      );
    } break;
  }
  
 
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> ScalarFactory::getPropertyNames(jsi::Runtime& rt) {
    std::vector<jsi::PropNameID> names;
    names.push_back(jsi::PropNameID::forUtf8(rt, "create"));
    return names;
}

