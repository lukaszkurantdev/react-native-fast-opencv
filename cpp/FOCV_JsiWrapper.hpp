//
//  FOCV_JsiWrapper.hpp
//  react-native-fast-opencv
//

#ifndef FOCV_JsiWrapper_hpp
#define FOCV_JsiWrapper_hpp

#include <jsi/jsi.h>
#include <any>
#include <string>
#include "DelegateRegistry.h"

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
        if (propName == "release") {
            return jsi::Function::createFromHostFunction(
                runtime, jsi::PropNameID::forAscii(runtime, "release"), 0,
                [this](jsi::Runtime& rt, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
                    this->object.reset();
                    if (thisVal.isObject()) {
                        auto self = thisVal.asObject(rt);
                        if (self.isHostObject(rt) && self.getHostObject(rt).get() == this) {
                            self.setExternalMemoryPressure(rt, 0);
                        }
                    }
                    return jsi::Value::undefined();
                }
            );
        }
      
        auto handler = DelegateRegistry::getHandler(this->type);
      
        if (handler) {
            jsi::Value val = handler->get(runtime, propName, this->object);
            
            if (!val.isUndefined()) {
                return val;
            }
        }
        
        return jsi::Value::undefined();
    }
    
    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& runtime) override {
        std::vector<jsi::PropNameID> result;
        result.push_back(jsi::PropNameID::forAscii(runtime, "type"));
        result.push_back(jsi::PropNameID::forAscii(runtime, "release"));
      
        TypeDelegate* handler = DelegateRegistry::getHandler(this->type);
      
        if (handler) {
            std::vector<jsi::PropNameID> val = handler->getPropertyNames(runtime);
            
            for(size_t i = 0; i < val.size(); i++) {
              result.push_back(jsi::PropNameID::forUtf8(runtime, val.at(i).utf8(runtime)));
            }
        }
      
        return result;
    }
};

#endif /* FOCV_JsiWrapper_hpp */
