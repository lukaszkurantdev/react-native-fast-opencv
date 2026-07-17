#include <jsi/jsi.h>
#include <any>
#include <opencv2/opencv.hpp>
#include "hashString.hpp"
#include "ConvertImage.hpp"
#include "FOCV_JsiObject.hpp"
#include "TypedArray.h"
#include "TypeDelegate.hpp"
#include <iostream>
#include <filesystem>

#ifndef MatDelegate_h
#define MatDelegate_h

using namespace facebook;

class MatDelegate : public TypeDelegate {
public:
  jsi::Value get(jsi::Runtime& rt, const std::string& propName, const std::any& object) override;
  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& runtime) override;
  size_t getExternalMemorySize(const std::any& object) override;
};

#endif // !MatDelegate_h
