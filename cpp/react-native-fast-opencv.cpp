#include <iostream>

#include "react-native-fast-opencv.h"
#include "jsi/Promise.h"
#include "jsi/TypedArray.h"
#include <FOCV_Mat.hpp>
#include <FOCV_Ids.hpp>
#include <FOCV_Rect.hpp>
#include <FOCV_Storage.hpp>
#include <FOCV_PointsGroup.hpp>
#include <FOCV_StoredObject.hpp>
#include "FOCV_Object.hpp"
#include "opencv2/opencv.hpp"

//using namespace facebook;
using namespace mrousavy;


void OpenCVPlugin::installOpenCV(jsi::Runtime& runtime, std::shared_ptr<react::CallInvoker> callInvoker) {
    
    auto func = [=](jsi::Runtime& runtime,
                        const jsi::Value& thisArg,
                        const jsi::Value* args,
                        size_t count) -> jsi::Value {
        auto plugin = std::make_shared<OpenCVPlugin>(callInvoker);
        auto result = jsi::Object::createFromHostObject(runtime, plugin);
        
        return result;
    };

    auto jsiFunc = jsi::Function::createFromHostFunction(runtime,
                                                         jsi::PropNameID::forUtf8(runtime, "__loadOpenCV"),
                                                         1,
                                                         func);

    runtime.global().setProperty(runtime, "__loadOpenCV", jsiFunc);
    
}

OpenCVPlugin::OpenCVPlugin(std::shared_ptr<react::CallInvoker> callInvoker) : _callInvoker(callInvoker) {}

jsi::String OpenCVPlugin::frameBufferToMat(jsi::Runtime& runtime, jsi::Value rows, jsi::Value cols, jsi::Object input) {
    // TODO: validation

    TypedArrayBase inputBuffer = getTypedArray(runtime, std::move(input)); // Po co to?
    auto vec = inputBuffer.toVector(runtime);

    auto id = FOCV_Mat::createMat(rows.asNumber(), cols.asNumber(), vec.data());
     
    return jsi::String::createFromUtf8(runtime, id);
}

jsi::Value OpenCVPlugin::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);

  if (propName == "frameBufferToMat") {
    return jsi::Function::createFromHostFunction(
        runtime, jsi::PropNameID::forAscii(runtime, "frameBufferToMat"), 1,
        [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
            size_t count) -> jsi::String {

        return frameBufferToMat(runtime,
                                arguments[0].getNumber(),
                                arguments[1].getNumber(),
                                arguments[2].asObject(runtime));
    });
  }
  else if (propName == "createObject") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "createObject"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::String {

          return FOCV_Object::create(runtime, arguments);
      });
    }
  else if (propName == "convertObjectToJSI") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "convertObjectToJSI"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Object {

          return FOCV_Object::convertToJSI(runtime, arguments);
      });
    }
  else if (propName == "cvtColor") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "cvtColor"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Value {
                  cv::Mat src = FOCV_Mat::getMat(arguments[0].asString(runtime).utf8(runtime));
                  cv::Mat dst = FOCV_Mat::getMat(arguments[1].asString(runtime).utf8(runtime));
                  cv::cvtColor(src, dst, arguments[2].getNumber());
                  FOCV_Mat::saveMat(arguments[1].asString(runtime).utf8(runtime), dst);
                  return true;
      });
  } else if (propName == "inRange") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "inRange"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Value {
                  jsi::Array lowerBoundArray = arguments[1].asObject(runtime).asArray(runtime);
                  jsi::Array upperBoundArray = arguments[2].asObject(runtime).asArray(runtime);

                  // Tutaj zmiana na tablicę
                  cv::Vec3b lowerBound(lowerBoundArray.getValueAtIndex(runtime, 0).asNumber(),
                                       lowerBoundArray.getValueAtIndex(runtime, 1).asNumber(),
                                       lowerBoundArray.getValueAtIndex(runtime, 2).asNumber());
                  
                  cv::Vec3b upperBound(upperBoundArray.getValueAtIndex(runtime, 0).asNumber(),
                                       upperBoundArray.getValueAtIndex(runtime, 1).asNumber(),
                                       upperBoundArray.getValueAtIndex(runtime, 2).asNumber());
                  
                  cv::Mat src = FOCV_Mat::getMat(arguments[0].asString(runtime).utf8(runtime));
                  cv::Mat dst = FOCV_Mat::getMat(arguments[3].asString(runtime).utf8(runtime));
                  
                  cv::inRange(src, lowerBound, upperBound, dst);
                  // To jest kopia dlatego zapis jest potrzebny!!! trzeba to zrobić na wskaźnikach!
                  FOCV_Mat::saveMat(arguments[3].asString(runtime).utf8(runtime), dst);
                  return true;
      });
  } else if (propName == "split") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "split"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Array {
                  
                  std::vector<cv::Mat> splited;
                
                  cv::Mat src = FOCV_Mat::getMat(arguments[0].asString(runtime).utf8(runtime));
                  
                  cv::split(src, splited);
                  
                  auto ids = FOCV_Ids();
                  
                  for (size_t i = 0; i < splited.size(); i++) {
                      auto id = FOCV_Mat::saveMat(splited.at(i));
                      ids.push(id);
                  }
                  
                  return ids.toJsiArray(runtime);
      });
  } else if (propName == "findContours") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "findContours"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Array {
                  
                  cv::Mat src = FOCV_Mat::getMat(arguments[0].asString(runtime).utf8(runtime));
                  std::vector<std::vector<cv::Point>> contours;
                  
                  cv::findContours(src, contours, arguments[1].getNumber(), arguments[2].getNumber());

                  auto ids = FOCV_Ids();
                  
                  for (size_t i = 0; i < contours.size(); i++) {
                      
                      auto id = FOCV_Storage::save(contours.at(i));
                      ids.push(id);
                  }

                  return ids.toJsiArray(runtime);
      });
  }  else if (propName == "contourArea") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "contourArea"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Value {
                  FOCV_StoredObject<std::vector<cv::Point>> storage;
                
                  std::vector<cv::Point> src = FOCV_Storage::get<std::vector<cv::Point>>(arguments[0].asString(runtime).utf8(runtime));

                  return contourArea(src, arguments[1].getBool());
      });
  }  else if (propName == "boundingRect") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "boundingRect"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::String {
                  
                  std::vector<cv::Point> src = FOCV_Storage::get<std::vector<cv::Point>>(arguments[0].asString(runtime).utf8(runtime));
                  cv::Rect rect = cv::boundingRect(src);
                  std::string id = FOCV_Rect::saveRect(rect);
                  
                  return jsi::String::createFromUtf8(runtime, id);
      });
  } else if (propName == "getRect") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "getRect"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Object {

                  return FOCV_Rect::getJsiRect(arguments[0].asString(runtime).utf8(runtime), runtime);
      });
  } else if (propName == "clearBuffers") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "clearBuffers"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Value {
                  FOCV_Rect::clear();
                  FOCV_PointsGroup::clear();
                  FOCV_Mat::clear();
                  FOCV_Storage::clear();
                  return true;
      });
  } else if (propName == "createMat") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "createMat"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::String {
                  auto id = FOCV_Mat::createMat();
                  return jsi::String::createFromUtf8(runtime, id);
      });
  }

  return jsi::HostObject::get(runtime, propNameId);
}

std::vector<jsi::PropNameID> OpenCVPlugin::getPropertyNames(jsi::Runtime& runtime) {
    std::vector<jsi::PropNameID> result;
    // list of available functions!!!
    result.push_back(jsi::PropNameID::forAscii(runtime, "frameBufferToMat"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "createObject"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "convertObjectToJSI"));
    
    
    
    result.push_back(jsi::PropNameID::forAscii(runtime, "cvtColor"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "inRange"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "split"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "findContours"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "contourArea"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "boundingRect"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "getRect"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "clearBuffers"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "createMat"));
    return result;
}

void OpenCVPlugin::clear() {
 
}
