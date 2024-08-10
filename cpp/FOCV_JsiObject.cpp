//
//  FOCV_JsiObject.cpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 10/08/2024.
//

#include "FOCV_JsiObject.hpp"

jsi::Object FOCV_JsiObject::wrap(jsi::Runtime& runtime, std::string type, std::string id) {
    jsi::Object wrapped(runtime);
    wrapped.setProperty(runtime, "type", jsi::String::createFromUtf8(runtime, type));
    wrapped.setProperty(runtime, "id", jsi::String::createFromUtf8(runtime, id));
    return wrapped;
}

std::string FOCV_JsiObject::id_from_wrap(jsi::Runtime& runtime, const jsi::Value& wrap) {
    return wrap.asObject(runtime).getProperty(runtime, "id").asString(runtime).utf8(runtime);
}

std::string FOCV_JsiObject::type_from_wrap(jsi::Runtime& runtime, const jsi::Value& wrap) {
    return wrap.asObject(runtime).getProperty(runtime, "type").asString(runtime).utf8(runtime);
}
