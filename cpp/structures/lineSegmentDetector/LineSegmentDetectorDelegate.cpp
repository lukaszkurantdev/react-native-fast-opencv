#include "LineSegmentDetectorDelegate.h"
#include "FOCV_JsiObject.hpp"
#include <opencv2/imgproc.hpp>

jsi::Value LineSegmentDetectorDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("compareSegments", 15): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "compareSegments"), 3,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              if (count < 3) {
                  throw std::runtime_error("compareSegments requires 3 arguments: size, lines1, lines2");
              }
              auto lineSegmentDetectorPtr = std::any_cast<std::shared_ptr<cv::Ptr<cv::LineSegmentDetector>>>(object);
              auto size = FOCV_JsiObject::get_from_wrap<cv::Size>(runtime, args[0]);
              auto lines1 = FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[1]);
              auto lines2 = FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[2]);

              if (count > 3 && !args[3].isUndefined()) {
                  auto image = FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[3]);
                  auto result = (*lineSegmentDetectorPtr)->compareSegments(*size, *lines1, *lines2, *image);
                  FOCV_JsiObject::updateExternalMemoryPressure(runtime, args[3]);
                  return jsi::Value(result);
              }

              return jsi::Value((*lineSegmentDetectorPtr)->compareSegments(*size, *lines1, *lines2));
          }
      );
    } break;
    case hashString("detect", 6): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "detect"), 2,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              if (count < 2) {
                  throw std::runtime_error("detect requires 2 arguments: image, lines");
              }
              auto lineSegmentDetectorPtr = std::any_cast<std::shared_ptr<cv::Ptr<cv::LineSegmentDetector>>>(object);
              auto image = FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[0]);
              auto lines = FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[1]);
              auto width = count > 2 && !args[2].isUndefined()
                  ? FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[2]) : nullptr;
              auto prec = count > 3 && !args[3].isUndefined()
                  ? FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[3]) : nullptr;
              auto nfa = count > 4 && !args[4].isUndefined()
                  ? FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[4]) : nullptr;

              (*lineSegmentDetectorPtr)->detect(
                  *image, *lines,
                  width ? cv::_OutputArray(*width) : cv::_OutputArray(),
                  prec ? cv::_OutputArray(*prec) : cv::_OutputArray(),
                  nfa ? cv::_OutputArray(*nfa) : cv::_OutputArray()
              );

              for (size_t i = 1; i < count; i++) {
                  FOCV_JsiObject::updateExternalMemoryPressure(runtime, args[i]);
              }
              return jsi::Value::undefined();
          }
      );
    } break;
    case hashString("drawSegments", 12): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "drawSegments"), 2,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              if (count < 2) {
                  throw std::runtime_error("drawSegments requires 2 arguments: image, lines");
              }
              auto lineSegmentDetectorPtr = std::any_cast<std::shared_ptr<cv::Ptr<cv::LineSegmentDetector>>>(object);
              auto image = FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[0]);
              auto lines = FOCV_JsiObject::get_from_wrap<cv::Mat>(runtime, args[1]);

              (*lineSegmentDetectorPtr)->drawSegments(*image, *lines);
              FOCV_JsiObject::updateExternalMemoryPressure(runtime, args[0]);
              return jsi::Value::undefined();
          }
      );
    } break;
  }

  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> LineSegmentDetectorDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "compareSegments"));
  result.push_back(jsi::PropNameID::forAscii(rt, "detect"));
  result.push_back(jsi::PropNameID::forAscii(rt, "drawSegments"));
  return result;
}
