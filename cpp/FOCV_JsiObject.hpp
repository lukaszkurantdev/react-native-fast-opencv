//
//  FOCV_JsiObject.hpp
//  react-native-fast-opencv
//

#ifndef FOCV_JsiObject_hpp
#define FOCV_JsiObject_hpp

#include <stdio.h>
#include <jsi/jsilib.h>
#include <jsi/jsi.h>
#include <any>
#include <memory>
#include "FOCV_JsiWrapper.hpp"

using namespace facebook;

class FOCV_JsiObject {
public:
    static jsi::Object wrap(jsi::Runtime& runtime, std::string type, std::any object);
    static void updateExternalMemoryPressure(jsi::Runtime& runtime, const jsi::Value& value);
    
    template <typename T>
    static std::shared_ptr<T> get_from_wrap(jsi::Runtime& runtime, const jsi::Value& wrap) {
        auto hostObj = wrap.asObject(runtime).asHostObject<FOCV_JsiWrapper>(runtime);
        return std::any_cast<std::shared_ptr<T>>(hostObj->object);
    }
    
    static std::string id_from_wrap(jsi::Runtime& runtime, const jsi::Value& wrap);
    static std::string type_from_wrap(jsi::Runtime& runtime, const jsi::Value& wrap);
};

#endif /* FOCV_JsiObject_hpp */
