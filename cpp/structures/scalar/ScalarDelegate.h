#include <jsi/jsi.h>
#include <any>
#include <opencv2/opencv.hpp>
#include "hashString.hpp"
#include "ConvertImage.hpp"
#include "FOCV_JsiObject.hpp"
#include "TypedArray.h"
#include "TypeDelegate.hpp"

#ifndef ScalarDelegate_h
#define ScalarDelegate_h

using namespace facebook;

class ScalarDelegate : public TypeDelegate {
public:
  jsi::Value get(jsi::Runtime& rt, const std::string& propName, const std::any& object) override;
  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& runtime) override;
};

#endif // !ScalarDelegate_h
