//
//  FOCV_JsiWrapper.hpp
//  react-native-fast-opencv
//

#ifndef FOCV_JsiWrapper_hpp
#define FOCV_JsiWrapper_hpp

#include <jsi/jsi.h>
#include <any>
#include <string>

using namespace facebook;

class FOCV_JsiWrapper : public jsi::HostObject {
public:
    std::string type;
    std::any object;

    FOCV_JsiWrapper(std::string type, std::any obj) : type(type), object(obj) {}

    jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& name) override {
        auto propName = name.utf8(runtime);
        if (propName == "type") {
            return jsi::String::createFromUtf8(runtime, type);
        }
        if (propName == "id") {
            // Zwracamy statyczne ID, ponieważ w TS niektóre logiki mogą oczekiwać stringa.
            // Pamięć i tak jest zarządzana przez powiązanie HostObject z GC.
            return jsi::String::createFromUtf8(runtime, "host-object-id");
        if (propName == "release") {
            return jsi::Function::createFromHostFunction(
                runtime, jsi::PropNameID::forAscii(runtime, "release"), 0,
                [this](jsi::Runtime& rt, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
                    this->object.reset();
                    return jsi::Value::undefined();
                }
            );
        }
        return jsi::Value::undefined();
    }
    
    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& runtime) override {
        std::vector<jsi::PropNameID> result;
        result.push_back(jsi::PropNameID::forAscii(runtime, "type"));
        result.push_back(jsi::PropNameID::forAscii(runtime, "id"));
        result.push_back(jsi::PropNameID::forAscii(runtime, "release"));
        return result;
    }
};

#endif /* FOCV_JsiWrapper_hpp */
