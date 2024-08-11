//
//  FOCV_Function.cpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 06/08/2024.
//

#include "FOCV_Function.hpp"
#include "FOCV_Storage.hpp"
#include "FOCV_Ids.hpp"
#include <FOCV_JsiObject.hpp>
#include <opencv2/opencv.hpp>

constexpr uint64_t hashString(const char* str, size_t length) {
  uint64_t hash = 14695981039346656037ull;
  const uint64_t fnv_prime = 1099511628211ull;
 
  for (size_t i = 0; i < length; ++i) {
      hash ^= static_cast<uint64_t>(str[i]);
      hash *= fnv_prime;
  }
 
  return hash;
}

std::string getId(jsi::Runtime& runtime, const jsi::Value& argument) {
    return argument.asString(runtime).utf8(runtime);
}

jsi::Object FOCV_Function::invoke(jsi::Runtime& runtime, const jsi::Value* arguments) {
    jsi::Object value(runtime);
    
    std::string functionName = getId(runtime, arguments[0]);
    
    switch (hashString(functionName.c_str(), functionName.size())) {
        case hashString("cvtColor", 8): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto code = arguments[3].getNumber();
            
            if(arguments[4].isNumber()) {
                auto dsnCn = arguments[4].getNumber();
                
                cv::cvtColor(src, dst, code, dsnCn);
            } else {
                cv::cvtColor(src, dst, code);
            }
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("split", 5): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            
            cv::split(src, dst);
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("findContours", 12): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto mode = arguments[2].getNumber();
            auto method = arguments[3].getNumber();
            
            std::vector<std::vector<cv::Point>> contours;
            
            cv::findContours(src, contours, mode, method);

            auto ids = FOCV_Ids();
            for (size_t i = 0; i < contours.size(); i++) {
                auto id = FOCV_Storage::save(contours.at(i));
                ids.push(id);
            }

           return ids.toJsiArray(runtime, "point_vector");
        } break;
        case hashString("contourArea", 11): {
            auto src = FOCV_Storage::get<std::vector<cv::Point>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto oriented = arguments[2].getBool();
            
            value.setProperty(runtime, "value", contourArea(src, oriented));
        } break;
        case hashString("boundingRect", 12): {
            auto src = FOCV_Storage::get<std::vector<cv::Point>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            
            cv::Rect rect = cv::boundingRect(src);
            std::string id = FOCV_Storage::save(rect);
            
            return FOCV_JsiObject::wrap(runtime, "rect", id);
        } break;
            
        case hashString("absdiff", 7): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            
            cv::absdiff(src1, src2, dst);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
        } break;
        case hashString("add", 3): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            
            if(arguments[5].isNumber()) {
                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
                auto dtype = arguments[5].asNumber();
                
                cv::add(src1, src2, dst, mask, dtype);
            } else if(arguments[4].isObject()) {
                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
                
                cv::add(src1, src2, dst, mask);
            } else {
                cv::add(src1, src2, dst);
            }
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
        } break;
        case hashString("addWeighted", 11): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto alpha = arguments[2].asNumber();
            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            auto beta = arguments[4].asNumber();
            auto gamma = arguments[5].asNumber();
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[6]));
            
            if(arguments[7].isNumber()) {
                auto dtype = arguments[7].asNumber();
                
                cv::addWeighted(src1, alpha, src2, beta, gamma, dst, dtype);
            } else {
                cv::addWeighted(src1, alpha, src2, beta, gamma, dst);
            }
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[6]), dst);
        } break;
        case hashString("batchDistance", 13): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto dist = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            auto dtype = arguments[4].asNumber();
            auto nidx = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[5]));
            auto normType = arguments[6].asNumber();
            auto K = arguments[7].asNumber();
            auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[8]));
            auto update = arguments[9].asNumber();
            auto crosscheck = arguments[10].asNumber();
            
            cv::batchDistance(src1, src2, dist, dtype, nidx, normType, K, mask, update, crosscheck);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dist);
        } break;
        case hashString("bitwise_and", 11): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            
            if(arguments[4].isObject()) {
                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
                
                cv::bitwise_and(src1, src2, dst, mask);
            } else {
                cv::bitwise_and(src1, src2, dst);
            }
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
        } break;
        case hashString("bitwise_not", 11): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            
            if(arguments[3].isObject()) {
                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
                
                cv::bitwise_not(src1, dst, mask);
            } else {
                cv::bitwise_not(src1, dst);
            }
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("bitwise_or", 10): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            
            if(arguments[4].isObject()) {
                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
                
                cv::bitwise_or(src1, src2, dst, mask);
            } else {
                cv::bitwise_or(src1, src2, dst);
            }
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
        } break;
        case hashString("bitwise_xor", 11): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            
            if(arguments[4].isObject()) {
                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
                
                cv::bitwise_xor(src1, src2, dst, mask);
            } else {
                cv::bitwise_xor(src1, src2, dst);
            }
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
        } break;
        case hashString("borderInterpolate", 17): {
            auto p = arguments[1].asNumber();
            auto len = arguments[2].asNumber();
            auto borderType = arguments[3].asNumber();
            
            auto result = cv::borderInterpolate(p, len, borderType);
            
            value.setProperty(runtime, "value", result);
        } break;
        case hashString("calcCovarMatrix", 15): {
            auto samples = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto nsamples = arguments[2].asNumber();
            auto covar = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            auto mean = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
            auto flags = arguments[5].asNumber();
            auto dtype = arguments[6].asNumber();
            
            cv::calcCovarMatrix(samples.data(), nsamples, covar, mean, flags, dtype);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), covar);
        } break;
        case hashString("cartToPolar", 11): {
            auto x = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            
            auto y = FOCV_JsiObject::type_from_wrap(runtime, arguments[2]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2])) :
                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            
            auto magnitude = FOCV_JsiObject::type_from_wrap(runtime, arguments[3]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3])) :
                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            
            auto angle = FOCV_JsiObject::type_from_wrap(runtime, arguments[4]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4])) :
                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
            
            if(arguments[5].isBool()) {
                auto angleInDegrees = arguments[5].asBool();
                
                cv::cartToPolar(x, y, magnitude, angle, angleInDegrees);
            } else {
                cv::cartToPolar(x, y, magnitude, angle);
            }
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), magnitude);
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]), angle);
        } break;
        case hashString("checkRange", 10): {
            auto a = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto quiet = arguments[2].asBool();
            auto pos = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            auto minVal = arguments[4].asNumber();
            auto maxVal = arguments[5].asNumber();
            
            cv::checkRange(a, quiet, &pos, minVal, maxVal);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), pos);
        } break;
        case hashString("compare", 7): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            auto cmpop = arguments[4].asNumber();
            
            cv::compare(src1, src2, dst, cmpop);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
        } break;
        case hashString("completeSymm", 12): {
            auto m = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto lowerToUpper = arguments[4].asBool();
            
            cv::completeSymm(m, lowerToUpper);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), m);
        } break;
        case hashString("convertFp16", 11): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            
            cv::convertFp16(src, dst);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("convertScaleAbs", 15): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            
            if(arguments[4].isNumber()) {
                auto alpha = arguments[3].asNumber();
                auto beta = arguments[4].asNumber();
                
                cv::convertScaleAbs(src, dst, alpha, beta);
            } else if(arguments[3].isNumber()) {
                auto alpha = arguments[3].asNumber();
                
                cv::convertScaleAbs(src, dst, alpha);
            } else {
                cv::convertScaleAbs(src, dst);
            }
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("copyMakeBorder", 14): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto top = arguments[3].asNumber();
            auto bottom = arguments[4].asNumber();
            auto left = arguments[5].asNumber();
            auto right = arguments[6].asNumber();
            auto borderType = arguments[7].asNumber();
            auto value = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[8]));
            
            cv::copyMakeBorder(src, dst, top, bottom, left, right, borderType, value);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("copyTo", 6): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
           
            cv::copyTo(src, dst, mask);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("countNonZero", 12): {
            auto src = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
           
            auto result = cv::countNonZero(src);
            value.setProperty(runtime, "value", result);
        } break;
        case hashString("dct", 3): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto flags = arguments[3].asNumber();
           
            cv::dct(src, dst, flags);
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("determinant", 11): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
           
            auto result = cv::determinant(src);
            value.setProperty(runtime, "value", result);
        } break;
        case hashString("dft", 3): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto flags = arguments[3].asNumber();
            auto nonzeroRows = arguments[4].asNumber();
           
            cv::dft(src, dst, flags, nonzeroRows);
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("divide", 6): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            auto scale = arguments[4].asNumber();
       
            if(arguments[5].isNumber()) {
                auto dtype = arguments[5].asNumber();
                
                cv::divide(src1, src2, dst, scale, dtype);
            } else {
                cv::divide(src1, src2, dst, scale);
            }
         
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
        } break;
        case hashString("eigen", 5): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto eigenvalues = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto eigenvectors = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
          
            cv::eigen(src, eigenvalues, eigenvectors);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), eigenvalues);
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), eigenvectors);
        } break;
        case hashString("eigenNonSymmetric", 17): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto eigenvalues = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto eigenvectors = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
          
            cv::eigenNonSymmetric(src, eigenvalues, eigenvectors);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), eigenvalues);
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), eigenvectors);
        } break;
        case hashString("exp", 3): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
          
            cv::exp(src, dst);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("extractChannel", 14): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto coi = arguments[3].asNumber();
          
            cv::extractChannel(src, dst, coi);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("findNonZero", 11): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto idx = FOCV_JsiObject::type_from_wrap(runtime, arguments[2]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2])) :
                FOCV_Storage::get<std::vector<cv::Point>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
          
            cv::findNonZero(src, idx);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), idx);
        } break;
        case hashString("flip", 4): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto flipCode = arguments[3].asNumber();
          
            cv::flip(src, dst, flipCode);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("gemm", 4): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto alpha = arguments[3].asNumber();
            auto src3 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
            auto beta = arguments[5].asNumber();
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[6]));
            auto flags = arguments[7].asNumber();
            
            cv::gemm(src1, src2, alpha, src3, beta, dst, flags);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[6]), dst);
        } break;
        case hashString("getOptimalDFTSize", 17): {
            auto vecsize =  arguments[1].asNumber();
           
            auto result = cv::getOptimalDFTSize(vecsize);
            value.setProperty(runtime, "value", result);
        } break;
        case hashString("hconcat", 7): {
            auto srcs = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
          
            cv::hconcat(srcs, dst);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("idft", 4): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto flags = arguments[3].asNumber();
            auto nonzeroRows = arguments[3].asNumber();
          
            cv::idft(src, dst, flags, nonzeroRows);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("inRange", 7): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto lowerBound = FOCV_Storage::get<cv::Vec3b>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto upperBound = FOCV_Storage::get<cv::Vec3b>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
            
            cv::inRange(src, lowerBound, upperBound, dst);
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]), dst);
        } break;
        case hashString("insertChannel", 13): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto coi = arguments[3].asNumber();
         
            cv::insertChannel(src, dst, coi);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("invert", 6): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto flags = arguments[3].asNumber();
         
            cv::invert(src, dst, flags);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("log", 3): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
      
            cv::log(src, dst);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
        } break;
        case hashString("LUT", 3): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto lut = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
      
            cv::LUT(src, lut, dst);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
        } break;
        case hashString("magnitude", 9): {
            auto x = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            
            auto y = FOCV_JsiObject::type_from_wrap(runtime, arguments[2]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2])) :
                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            
            auto magnitude = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
      
            cv::magnitude(x, y, magnitude);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), magnitude);
        } break;
        case hashString("Mahalanobis", 11): {
            auto x = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            
            auto y = FOCV_JsiObject::type_from_wrap(runtime, arguments[2]) == "mat" ?
                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2])) :
                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            
            auto icovar = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
      
            cv::Mahalanobis(x, y, icovar);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), icovar);
        } break;
        case hashString("max", 3): {
            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
      
            cv::max(src1, src2, dst);
            
            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
        } break;
        case hashString("mean", 4): {
            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
            std::string id = "";
            
            if(arguments[2].isObject()) {
                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
                
                auto scalar = cv::mean(src, mask);
                std::string id = FOCV_Storage::save(scalar);
            } else {
                auto scalar = cv::mean(src);
                std::string id = FOCV_Storage::save(scalar);
            }
            
            return FOCV_JsiObject::wrap(runtime, "scalar", id);
        } break;
    }
    
    return value;
}
