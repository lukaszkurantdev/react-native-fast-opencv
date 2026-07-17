#include "MatFactory.h"

jsi::Value MatFactory::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);

  switch(hashString(propName.c_str(), propName.size())) {
    case hashString("create", 6): {
      return jsi::Function::createFromHostFunction(
         runtime,
         propNameId,
         3,
         [](jsi::Runtime& rt, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
           auto rows = static_cast<int>(args[0].asNumber());
           auto cols = static_cast<int>(args[1].asNumber());
           auto type = static_cast<int>(args[2].asNumber());
           
           auto channels = CV_MAT_CN(type);
           auto depth = CV_MAT_DEPTH(type);
           std::vector<int> size {rows, cols};
           
           if (count > 3 && args[3].isObject()) {
             auto array = args[3].asObject(rt).asArray(rt);
             auto length = array.length(rt);
             
             std::vector<double> vec;
             vec.reserve(length);
             
             for(size_t i = 0; i < length; i++) {
               vec.push_back(array.getValueAtIndex(rt, i).asNumber());
             }
             
             cv::Mat object(vec, true);
             object = object.reshape(channels, size);
             object.convertTo(object, depth);
             
             return FOCV_JsiObject::wrap(rt, "mat", std::make_shared<cv::Mat>(object));
           } else {
             cv::Mat object(rows, cols, type);
             return FOCV_JsiObject::wrap(rt, "mat", std::make_shared<cv::Mat>(object));
           }
         }
      );
    } break;
    case hashString("createFromBase64", 16): {
      return jsi::Function::createFromHostFunction(
         runtime,
         propNameId,
         1,
         [](jsi::Runtime& rt, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
           auto base64 = args[0].asString(rt).utf8(rt);

           auto mat = ImageConverter::str2mat(base64);
           return FOCV_JsiObject::wrap(rt, "mat", std::make_shared<cv::Mat>(mat));
         }
      );
    } break;
    case hashString("createFromVisionCameraFrameBuffer", 33): {
      return jsi::Function::createFromHostFunction(
         runtime,
         propNameId,
         4,
         [](jsi::Runtime& rt, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
           auto rows = args[0].asNumber();
           auto cols = args[1].asNumber();
           auto channels = args[2].asNumber();
           auto input = args[3].asObject(rt);

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

           auto inputBuffer = mrousavy::getTypedArray(rt, std::move(input));
           auto vec = inputBuffer.toVector(rt);

           cv::Mat mat(rows, cols, type);
           memcpy(mat.data, vec.data(), (int)rows * (int)cols * (int)channels);
           return FOCV_JsiObject::wrap(rt, "mat", std::make_shared<cv::Mat>(mat));
         }
      );
    } break;
    case hashString("createFromBuffer", 16): {
      return jsi::Function::createFromHostFunction(
         runtime,
         propNameId,
         5,
         [](jsi::Runtime& rt, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
           auto type = args[0].asString(rt).utf8(rt);
           auto rows = args[1].asNumber();
           auto cols = args[2].asNumber();
           auto channels = args[3].asNumber();
           auto input = args[4].asObject(rt);

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

           auto inputBuffer = mrousavy::getTypedArray(rt, std::move(input));
           auto vec = inputBuffer.toVector(rt);

           cv::Mat mat(rows, cols, modeType);
           memcpy(mat.data, vec.data(), (int)rows * (int)cols * (int)channels * typeSize);
           return FOCV_JsiObject::wrap(rt, "mat", std::make_shared<cv::Mat>(mat));
         }
      );
    } break;
  }
  
 
  return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> MatFactory::getPropertyNames(jsi::Runtime& rt) {
    std::vector<jsi::PropNameID> names;
    names.push_back(jsi::PropNameID::forUtf8(rt, "create"));
    names.push_back(jsi::PropNameID::forUtf8(rt, "createFromBase64"));
    names.push_back(jsi::PropNameID::forUtf8(rt, "createFromVisionCameraFrameBuffer"));
    names.push_back(jsi::PropNameID::forUtf8(rt, "createFromBuffer"));
    return names;
}

