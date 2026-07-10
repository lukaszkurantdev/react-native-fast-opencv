//
//  FOCV_JsiObject.cpp
//  react-native-fast-opencv
//

#include "FOCV_JsiObject.hpp"

jsi::Object FOCV_JsiObject::wrap(jsi::Runtime& runtime, std::string type, std::any object) {
    auto wrapper = std::make_shared<FOCV_JsiWrapper>(type, object);
    return jsi::Object::createFromHostObject(runtime, wrapper);
}

std::string FOCV_JsiObject::id_from_wrap(jsi::Runtime& runtime, const jsi::Value& wrap) {
    // For backwards compatibility where ID is requested in TS API
    auto hostObj = wrap.asObject(runtime).asHostObject<FOCV_JsiWrapper>(runtime);
    return "host-object-" + hostObj->type;
}

std::string FOCV_JsiObject::type_from_wrap(jsi::Runtime& runtime, const jsi::Value& wrap) {
    auto hostObj = wrap.asObject(runtime).asHostObject<FOCV_JsiWrapper>(runtime);
    return hostObj->type;
}
