//
//  FOCV_JsiObject.cpp
//  react-native-fast-opencv
//

#include "FOCV_JsiObject.hpp"

static size_t externalMemorySize(const std::string& type, const std::any& object) {
    auto handler = DelegateRegistry::getHandler(type);
    return handler ? handler->getExternalMemorySize(object) : 0;
}

jsi::Object FOCV_JsiObject::wrap(jsi::Runtime& runtime, std::string type, std::any object) {
    auto wrapper = std::make_shared<FOCV_JsiWrapper>(type, object);
    auto jsObject = jsi::Object::createFromHostObject(runtime, wrapper);

    // The GC only sees the tiny host object, not the native buffers behind it.
    // Report them so collections are scheduled before memory piles up.
    auto size = externalMemorySize(type, wrapper->object);
    if (size > 0) {
        jsObject.setExternalMemoryPressure(runtime, size);
    }

    return jsObject;
}

void FOCV_JsiObject::updateExternalMemoryPressure(jsi::Runtime& runtime, const jsi::Value& value) {
    if (!value.isObject()) {
        return;
    }

    auto object = value.asObject(runtime);
    if (!object.isHostObject(runtime)) {
        return;
    }

    auto wrapper = std::dynamic_pointer_cast<FOCV_JsiWrapper>(object.getHostObject(runtime));
    if (wrapper == nullptr) {
        return;
    }

    object.setExternalMemoryPressure(runtime, externalMemorySize(wrapper->type, wrapper->object));
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
