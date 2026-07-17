#include <jsi/jsi.h>
#include <any>

using namespace facebook;

#ifndef TypeDelegate_hpp
#define TypeDelegate_hpp

class TypeDelegate {
public:
    virtual ~TypeDelegate() = default;
    virtual jsi::Value get(jsi::Runtime& rt, const std::string& propName, const std::any& object) = 0;
    virtual std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& rt) = 0;

    // Native bytes held by the wrapped object, reported to the JS GC as
    // external memory pressure. Types with negligible payload keep 0.
    virtual size_t getExternalMemorySize(const std::any& object) { return 0; }
};

#endif // !TypeDelegate_hpp
