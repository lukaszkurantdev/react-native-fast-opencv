#include "TermCriteriaFactory.h"

jsi::Value TermCriteriaFactory::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);

  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("create", 6): {
      return jsi::Function::createFromHostFunction(
         runtime,
         propNameId,
         5,
         [](jsi::Runtime& rt, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
           auto termCriteriaType = static_cast<int>(args[0].asNumber());
           auto maxCount = static_cast<int>(args[1].asNumber());
           auto epsilon  = args[2].asNumber();

           cv::TermCriteria object(termCriteriaType, maxCount, epsilon);
           if (!object.isValid()) {
               throw std::runtime_error("Fast OpenCV Error: Invalid TermCriteria object parameters!");
           }
           
           return FOCV_JsiObject::wrap(rt, "term_criteria", std::make_shared<decltype(object)>(object));
         }
      );
    } break;
  }
 
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> TermCriteriaFactory::getPropertyNames(jsi::Runtime& rt) {
    std::vector<jsi::PropNameID> names;
    names.push_back(jsi::PropNameID::forUtf8(rt, "create"));
    return names;
}

