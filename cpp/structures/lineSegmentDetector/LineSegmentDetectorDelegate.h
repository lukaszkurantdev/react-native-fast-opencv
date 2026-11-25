#include "TypeDelegate.hpp"
#include <jsi/jsi.h>
#include <any>
#include <opencv2/opencv.hpp>
#include "hashString.hpp"

#ifndef LineSegmentDetectorDelegate_h
#define LineSegmentDetectorDelegate_h

using namespace facebook;

class LineSegmentDetectorDelegate : public TypeDelegate {
public:
  jsi::Value get(jsi::Runtime& rt, const std::string& propName, const std::any& object) override;
  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& runtime) override;
};

#endif // !LineSegmentDetectorDelegate_h
