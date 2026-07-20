#include <jsi/jsi.h>
#include <opencv2/opencv.hpp>
#include "FOCV_JsiObject.hpp"
#include "hashString.hpp"
#include "TypedArray.h"
#include "ConvertImage.hpp"

#ifndef MatFactory_h
#define MatFactory_h

using namespace facebook;

class MatFactory: public jsi::HostObject {
  jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) override;
  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& rt) override;
};

#endif // !MatFactory_h
