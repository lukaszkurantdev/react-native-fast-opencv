#include "MatVectorFactory.h"
  
jsi::Value MatVectorFactory::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);

  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("create", 6): {
      return jsi::Function::createFromHostFunction(
         runtime,
         propNameId,
         0,
         [](jsi::Runtime& rt, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
           std::vector<cv::Mat> vec;
           return FOCV_JsiObject::wrap(rt, "mat_vector", std::make_shared<decltype(vec)>(vec));
         }
      );
    } break;
  }
  
 
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> MatVectorFactory::getPropertyNames(jsi::Runtime& rt) {
    std::vector<jsi::PropNameID> names;
    names.push_back(jsi::PropNameID::forUtf8(rt, "create"));
    return names;
}

