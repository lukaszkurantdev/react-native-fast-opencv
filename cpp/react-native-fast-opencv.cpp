#include <iostream>
#include <filesystem>

#include "react-native-fast-opencv.h"
#include "jsi/Promise.h"
#include "jsi/TypedArray.h"
#include <FOCV_Ids.hpp>
#include <FOCV_Storage.hpp>
#include <FOCV_Function.hpp>
#include "FOCV_Object.hpp"
#include "ConvertImage.hpp"
#include "FOCV_JsiObject.hpp"
#include "opencv2/opencv.hpp"

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

jsi::Value OpenCVPlugin::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);

  if (propName == "frameBufferToMat") {
    return jsi::Function::createFromHostFunction(
        runtime, jsi::PropNameID::forAscii(runtime, "frameBufferToMat"), 4,
        [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
            size_t count) -> jsi::Object {
        auto rows = arguments[0].asNumber();
        auto cols = arguments[1].asNumber();
        auto channels = arguments[2].asNumber();
        auto input = arguments[3].asObject(runtime);

        auto type = -1;
        if (channels == 1) {
          type = CV_8U;
        }
        if (channels == 3) {
          type = CV_8UC3;
        }
        if (channels == 4) {
          type = CV_8UC4;
        }
              
        if (channels == -1) {
          throw std::runtime_error("Fast OpenCV Error: Invalid channel count passed to frameBufferToMat!");
        }

        auto inputBuffer = getTypedArray(runtime, std::move(input));
        auto vec = inputBuffer.toVector(runtime);

        cv::Mat mat(rows, cols, type);
        memcpy(mat.data, vec.data(), (int)rows * (int)cols * (int)channels);
        auto id = FOCV_Storage::save(mat);

        return FOCV_JsiObject::wrap(runtime, "mat", id);
    });
  } else  if (propName == "bufferToMat") {
    return jsi::Function::createFromHostFunction(
        runtime, jsi::PropNameID::forAscii(runtime, "bufferToMat"), 4,
        [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
            size_t count) -> jsi::Object {
        auto type = arguments[0].asString(runtime).utf8(runtime);
        auto rows = arguments[1].asNumber();
        auto cols = arguments[2].asNumber();
        auto channels = arguments[3].asNumber();
        auto input = arguments[4].asObject(runtime);

        auto modeType = -1;
        auto typeSize = 1;
              
        if(type == "uint8") {
          typeSize = 1;
          if (channels == 1) modeType = CV_8U;
          if (channels == 3) modeType = CV_8UC3;
          if (channels == 4) modeType = CV_8UC4;
        } else if(type == "uint16") {
          typeSize = 2;
          if (channels == 1) modeType = CV_16U;
          if (channels == 3) modeType = CV_16UC3;
          if (channels == 4) modeType = CV_16UC4;
        } else if(type == "int8") {
          typeSize = 1;
          if (channels == 1) modeType = CV_8S;
          if (channels == 3) modeType = CV_8SC3;
          if (channels == 4) modeType = CV_8SC4;
        } else if(type == "int16") {
          typeSize = 2;
          if (channels == 1) modeType = CV_16S;
          if (channels == 3) modeType = CV_16SC3;
          if (channels == 4) modeType = CV_16SC4;
        } else if(type == "int32") {
          typeSize = 4;
          if (channels == 1) modeType = CV_32S;
          if (channels == 3) modeType = CV_32SC3;
          if (channels == 4) modeType = CV_32SC4;
        } else if(type == "float32") {
          typeSize = 4;
          if (channels == 1) modeType = CV_32F;
          if (channels == 3) modeType = CV_32FC3;
          if (channels == 4) modeType = CV_32FC4;
        } else if(type == "float64") {
          typeSize = 8;
          if (channels == 1) modeType = CV_64F;
          if (channels == 3) modeType = CV_64FC3;
          if (channels == 4) modeType = CV_64FC4;
        }
              
        if (channels == -1) {
          throw std::runtime_error("Fast OpenCV Error: Invalid channel count passed to frameBufferToMat!");
        }

        auto inputBuffer = getTypedArray(runtime, std::move(input));
        auto vec = inputBuffer.toVector(runtime);

        cv::Mat mat(rows, cols, modeType);
        memcpy(mat.data, vec.data(), (int)rows * (int)cols * (int)channels * typeSize);
        auto id = FOCV_Storage::save(mat);

        return FOCV_JsiObject::wrap(runtime, "mat", id);
    });
  }
  else if (propName == "base64ToMat") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "base64ToMat"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Object {

          auto base64 = arguments[0].asString(runtime).utf8(runtime);

          auto mat = ImageConverter::str2mat(base64);
          auto id = FOCV_Storage::save(mat);

          return FOCV_JsiObject::wrap(runtime, "mat", id);
      });
    }
  else if (propName == "matToBuffer") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "matToBuffer"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Object {

                auto id = FOCV_JsiObject::id_from_wrap(runtime, arguments[0]);
                auto mat = *FOCV_Storage::get<cv::Mat>(id);

                jsi::Object value(runtime);

                value.setProperty(runtime, "cols", jsi::Value(mat.cols));
                value.setProperty(runtime, "rows", jsi::Value(mat.rows));
                value.setProperty(runtime, "channels", jsi::Value(mat.channels()));

                auto type = arguments[1].asString(runtime).utf8(runtime);
                auto size = mat.cols * mat.rows * mat.channels();

                if(type == "uint8") {
                  auto arr = TypedArray<TypedArrayKind::Uint8Array>(runtime, size);
                  arr.updateUnsafe(runtime, (uint8_t*)mat.data, size * sizeof(uint8_t));
                  value.setProperty(runtime, "buffer", arr);
                } else if(type == "uint16") {
                  auto arr = TypedArray<TypedArrayKind::Uint16Array>(runtime, size);
                  arr.updateUnsafe(runtime, (uint16_t*)mat.data, size * sizeof(uint16_t));
                  value.setProperty(runtime, "buffer", arr);
                } else if(type == "uint32") {
                  auto arr = TypedArray<TypedArrayKind::Uint32Array>(runtime, size);
                  arr.updateUnsafe(runtime, (uint32_t*)mat.data, size * sizeof(uint32_t));
                  value.setProperty(runtime, "buffer", arr);
                } else if(type == "int8") {
                  auto arr = TypedArray<TypedArrayKind::Int8Array>(runtime, size);
                  arr.updateUnsafe(runtime, (int8_t*)mat.data, size * sizeof(int8_t));
                  value.setProperty(runtime, "buffer", arr);
                } else if(type == "int16") {
                  auto arr = TypedArray<TypedArrayKind::Int16Array>(runtime, size);
                  arr.updateUnsafe(runtime, (int16_t*)mat.data, size * sizeof(int16_t));
                  value.setProperty(runtime, "buffer", arr);
                } else if(type == "int32") {
                  auto arr = TypedArray<TypedArrayKind::Int32Array>(runtime, size);
                  arr.updateUnsafe(runtime, (int32_t*)mat.data, size * sizeof(int32_t));
                  value.setProperty(runtime, "buffer", arr);
                } else if(type == "float32") {
                  auto arr = TypedArray<TypedArrayKind::Float32Array>(runtime, size);
                  arr.updateUnsafe(runtime, (float*)mat.data, size * sizeof(float));
                  value.setProperty(runtime, "buffer", arr);
                } else if(type == "float64") {
                  auto arr = TypedArray<TypedArrayKind::Float64Array>(runtime, size);
                  arr.updateUnsafe(runtime, (double*)mat.data, size * sizeof(double));
                  value.setProperty(runtime, "buffer", arr);
                }

                return value;
      });
    } else if (propName == "createObject") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "createObject"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Object {

          return FOCV_Object::create(runtime, arguments, count);
      });
    }
  else if (propName == "toJSValue") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "toJSValue"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Object {

          return FOCV_Object::convertToJSI(runtime, arguments, count);
      });
    }
  else if (propName == "copyObjectFromVector") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "copyObjectFromVector"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Object {

          return FOCV_Object::copyObjectFromVector(runtime, arguments, count);
      });
    }
  else if (propName == "addObjectToVector") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "addObjectToVector"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Value {

          FOCV_Object::addObjectToVector(runtime, arguments, count);
                
          return jsi::Value(true);
      });
    }
  else if (propName == "invoke") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "invoke"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Object {

          return FOCV_Function::invoke(runtime, arguments, count);
      });
  } else if (propName == "clearBuffers") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "clearBuffers"), 1,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Value {
          std::set<std::string> ids_to_keep;

          if (count > 0) {
            auto array = arguments[0].asObject(runtime).asArray(runtime);
            auto length = array.length(runtime);
            for (size_t i = 0; i < length; i++) {
              auto id = array.getValueAtIndex(runtime, i).asString(runtime).utf8(runtime);
              ids_to_keep.insert(id);
            }
          }

          FOCV_Storage::clear(ids_to_keep);
          return true;
      });
  } else if (propName == "saveMatToFile") {
      return jsi::Function::createFromHostFunction(
          runtime, jsi::PropNameID::forAscii(runtime, "saveMatToFile"), 4,
          [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
              size_t count) -> jsi::Value {

          if (count < 4) {
              throw std::runtime_error("saveMatToFile requires 4 arguments: mat, path, format, compression");
          }

          auto id = FOCV_JsiObject::id_from_wrap(runtime, arguments[0]);
          auto matPtr = FOCV_Storage::get<cv::Mat>(id);
          if (!matPtr) throw std::runtime_error("Mat not found in storage");
          auto& mat = *matPtr;

          std::string path = arguments[1].asString(runtime).utf8(runtime);

          const std::string filePrefix = "file://";
          if (path.compare(0, filePrefix.length(), filePrefix) == 0) {
              path = path.substr(filePrefix.length());
          }

          auto format = arguments[2].asString(runtime).utf8(runtime);
          std::vector<int> params;

          double compression = arguments[3].asNumber();
          if (compression < 0.0 || compression > 1.0) {
              throw std::runtime_error("Compression must be between 0 and 1");
          }

          if (format == "jpeg") {
              int quality = static_cast<int>(compression * 100);
              params.push_back(cv::IMWRITE_JPEG_QUALITY);
              params.push_back(quality);
          } else if (format == "png") {
              int level = static_cast<int>((1.0 - compression) * 9);
              params.push_back(cv::IMWRITE_PNG_COMPRESSION);
              params.push_back(level);
          } else {
              throw std::runtime_error("Unsupported format: only 'jpeg' or 'png' allowed");
          }

          std::filesystem::path fsPath(path);
          auto parentDir = fsPath.parent_path();
          if (!parentDir.empty() && !std::filesystem::exists(parentDir)) {
              std::filesystem::create_directories(parentDir);
          }

          if (!cv::imwrite(path, mat, params)) {
              throw std::runtime_error("Failed to save Mat to file: " + path);
          }

          return jsi::Value(true);
      });
  }

  return jsi::HostObject::get(runtime, propNameId);
}

std::vector<jsi::PropNameID> OpenCVPlugin::getPropertyNames(jsi::Runtime& runtime) {
    std::vector<jsi::PropNameID> result;

    result.push_back(jsi::PropNameID::forAscii(runtime, "frameBufferToMat"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "base64ToMat"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "matToBuffer"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "createObject"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "toJSValue"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "copyObjectFromVector"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "invoke"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "clearBuffers"));
    result.push_back(jsi::PropNameID::forAscii(runtime, "saveMatToFile"));

    return result;
}
