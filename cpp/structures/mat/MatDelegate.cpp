#include "MatDelegate.h"

jsi::Value MatDelegate::get(jsi::Runtime& rt, const std::string& propName, const std::any& object) {
  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("rows", 4): {
      auto matPtr = std::any_cast<std::shared_ptr<cv::Mat>>(object);
      return jsi::Value(matPtr->rows);
    } break;
    case hashString("cols", 4): {
      auto matPtr = std::any_cast<std::shared_ptr<cv::Mat>>(object);
      return jsi::Value(matPtr->cols);
    } break;
    case hashString("type", 4): {
      auto matPtr = std::any_cast<std::shared_ptr<cv::Mat>>(object);
      return jsi::Value(matPtr->type());
    } break;
    case hashString("toBase64", 8): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "toJSValue"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto matPtr = std::any_cast<std::shared_ptr<cv::Mat>>(object);
              
              std::string format = "jpeg";
            
              if(args && args[0].isString()) {
                format = args[0].asString(runtime).utf8(runtime);
              }
           
              matPtr->convertTo(*matPtr, CV_8U);
            
              return jsi::String::createFromUtf8(runtime, ImageConverter::mat2str(*matPtr, format));
          }
      );
    } break;
    case hashString("toBuffer", 8): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "toJSValue"), 1,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              auto matPtr = std::any_cast<std::shared_ptr<cv::Mat>>(object);
              auto mat = *matPtr;

              jsi::Object value(runtime);

              value.setProperty(runtime, "cols", jsi::Value(mat.cols));
              value.setProperty(runtime, "rows", jsi::Value(mat.rows));
              value.setProperty(runtime, "channels", jsi::Value(mat.channels()));

              auto type = args[0].asString(runtime).utf8(runtime);
              auto size = mat.cols * mat.rows * mat.channels();

              if(type == "uint8") {
                auto arr = mrousavy::TypedArray<mrousavy::TypedArrayKind::Uint8Array>(runtime, size);
                arr.updateUnsafe(runtime, (uint8_t*)mat.data, size * sizeof(uint8_t));
                value.setProperty(runtime, "buffer", arr);
              } else if(type == "uint16") {
                auto arr = mrousavy::TypedArray<mrousavy::TypedArrayKind::Uint16Array>(runtime, size);
                arr.updateUnsafe(runtime, (uint16_t*)mat.data, size * sizeof(uint16_t));
                value.setProperty(runtime, "buffer", arr);
              } else if(type == "uint32") {
                auto arr = mrousavy::TypedArray<mrousavy::TypedArrayKind::Uint32Array>(runtime, size);
                arr.updateUnsafe(runtime, (uint32_t*)mat.data, size * sizeof(uint32_t));
                value.setProperty(runtime, "buffer", arr);
              } else if(type == "int8") {
                auto arr = mrousavy::TypedArray<mrousavy::TypedArrayKind::Int8Array>(runtime, size);
                arr.updateUnsafe(runtime, (int8_t*)mat.data, size * sizeof(int8_t));
                value.setProperty(runtime, "buffer", arr);
              } else if(type == "int16") {
                auto arr = mrousavy::TypedArray<mrousavy::TypedArrayKind::Int16Array>(runtime, size);
                arr.updateUnsafe(runtime, (int16_t*)mat.data, size * sizeof(int16_t));
                value.setProperty(runtime, "buffer", arr);
              } else if(type == "int32") {
                auto arr = mrousavy::TypedArray<mrousavy::TypedArrayKind::Int32Array>(runtime, size);
                arr.updateUnsafe(runtime, (int32_t*)mat.data, size * sizeof(int32_t));
                value.setProperty(runtime, "buffer", arr);
              } else if(type == "float32") {
                auto arr = mrousavy::TypedArray<mrousavy::TypedArrayKind::Float32Array>(runtime, size);
                arr.updateUnsafe(runtime, (float*)mat.data, size * sizeof(float));
                value.setProperty(runtime, "buffer", arr);
              } else if(type == "float64") {
                auto arr = mrousavy::TypedArray<mrousavy::TypedArrayKind::Float64Array>(runtime, size);
                arr.updateUnsafe(runtime, (double*)mat.data, size * sizeof(double));
                value.setProperty(runtime, "buffer", arr);
              }
            
              return value;
          }
      );
    } break;
    case hashString("saveToFile", 10): {
      return jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "saveToFile"), 3,
          [object](jsi::Runtime& runtime, const jsi::Value& thisVal, const jsi::Value* args, size_t count) -> jsi::Value {
              if (count < 4) {
                  throw std::runtime_error("saveToFile requires 3 arguments: path, format, compression");
              }
            
              auto matPtr = std::any_cast<std::shared_ptr<cv::Mat>>(object);
              auto mat = *matPtr;
              
              std::string path = args[0].asString(runtime).utf8(runtime);
    
              const std::string filePrefix = "file://";
              if (path.compare(0, filePrefix.length(), filePrefix) == 0) {
                  path = path.substr(filePrefix.length());
              }
    
              auto format = args[1].asString(runtime).utf8(runtime);
              std::vector<int> params;
    
              double compression = args[2].asNumber();
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
          }
      );
    } break;
  }
  
  
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> MatDelegate::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forAscii(rt, "toBase64"));
  result.push_back(jsi::PropNameID::forAscii(rt, "saveToFile"));
  result.push_back(jsi::PropNameID::forAscii(rt, "rows"));
  result.push_back(jsi::PropNameID::forAscii(rt, "cols"));
  result.push_back(jsi::PropNameID::forAscii(rt, "type"));
  return result;
}

size_t MatDelegate::getExternalMemorySize(const std::any& object) {
  auto matPtr = std::any_cast<std::shared_ptr<cv::Mat>>(&object);
  if (matPtr == nullptr || *matPtr == nullptr) {
    return 0;
  }
  return (*matPtr)->total() * (*matPtr)->elemSize();
}

