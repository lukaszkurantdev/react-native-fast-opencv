#include <jsi/jsi.h>
#include <opencv2/opencv.hpp>
#include "FOCV_JsiObject.hpp"
#include "hashString.hpp"
#include "TypedArray.h"

#ifndef PointVectorVectorFactory_h
#define PointVectorVectorFactory_h

using namespace facebook;

class PointVectorVectorFactory: public jsi::HostObject {
  jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) override;
  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& rt) override;
};

#endif // !PointVectorVectorFactory_h
