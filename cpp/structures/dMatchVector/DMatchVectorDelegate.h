#include "TypeDelegate.hpp"
#include <jsi/jsi.h>
#include <any>
#include <opencv2/opencv.hpp>
#include "hashString.hpp"
#include "FOCV_JsiObject.hpp"

#ifndef DMatchVectorDelegate_h
#define DMatchVectorDelegate_h

using namespace facebook;

class DMatchVectorDelegate : public TypeDelegate {
public:
  jsi::Value get(jsi::Runtime& rt, const std::string& propName, const std::any& object) override;
  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& runtime) override;
  size_t getExternalMemorySize(const std::any& object) override;
};

#endif // !DMatchVectorDelegate_h
