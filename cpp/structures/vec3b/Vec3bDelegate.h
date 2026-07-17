#include <jsi/jsi.h>
#include <any>
#include <opencv2/opencv.hpp>
#include "hashString.hpp"
#include "ConvertImage.hpp"
#include "FOCV_JsiObject.hpp"
#include "TypedArray.h"
#include "TypeDelegate.hpp"

#ifndef Vec3bDelegate_h
#define Vec3bDelegate_h

using namespace facebook;

class Vec3bDelegate : public TypeDelegate {
public:
  jsi::Value get(jsi::Runtime& rt, const std::string& propName, const std::any& object) override;
  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& runtime) override;
};

#endif // !Vec3bDelegate_h
