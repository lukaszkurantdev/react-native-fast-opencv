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
#include "FOCV_FunctionArguments.hpp"

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
    
    FOCV_FunctionArguments args(runtime, arguments);
    
    std::string functionName = args.asString(0);
    
    switch (hashString(functionName.c_str(), functionName.size())) {
        case hashString("absdiff", 7): {
            auto src1 = args.asMatPtr(1);
            auto src2 = args.asMatPtr(2);
            auto dst = args.asMatPtr(3);
            
            cv::absdiff(*src1, *src2, *dst);
        } break;
        case hashString("add", 3): {
            auto src1 = args.asMatPtr(1);
            auto src2 = args.asMatPtr(2);
            auto dst = args.asMatPtr(3);
            
            if(args.isNumber(5)) {
                auto mask = args.asMatPtr(4);
                auto dtype = args.asNumber(5);
                
                cv::add(*src1, *src2, *dst, *mask, dtype);
            } else if(args.isObject(4)) {
                auto mask = args.asMatPtr(4);
                
                cv::add(*src1, *src2, *dst, *mask);
            } else {
                cv::add(*src1, *src2, *dst);
            }
        } break;
        case hashString("addWeighted", 11): {
            auto src1 = args.asMatPtr(1);
            auto alpha = args.asNumber(2);
            auto src2 = args.asMatPtr(3);
            auto beta = args.asNumber(4);
            auto gamma = args.asNumber(5);
            auto dst = args.asMatPtr(6);
            
            if(args.isNumber(7)) {
                auto dtype = args.asNumber(7);
                
                cv::addWeighted(*src1, alpha, *src2, beta, gamma, *dst, dtype);
            } else {
                cv::addWeighted(*src1, alpha, *src2, beta, gamma, *dst);
            }
        } break;
        case hashString("batchDistance", 13): {
            auto src1 = args.asMatPtr(1);
            auto src2 = args.asMatPtr(2);
            auto dist = args.asMatPtr(3);
            auto dtype = args.asNumber(4);
            auto nidx = args.asMatPtr(5);
            auto normType = args.asNumber(6);
            auto K = args.asNumber(7);
            auto mask = args.asMatPtr(8);
            auto update = args.asNumber(9);
            auto crosscheck = args.asNumber(10);
            
            cv::batchDistance(*src1, *src2, *dist, dtype, *nidx, normType, K, *mask, update, crosscheck);
        } break;
        case hashString("bitwise_and", 11): {
            auto src1 = args.asMatPtr(1);
            auto src2 = args.asMatPtr(2);
            auto dst = args.asMatPtr(3);
            
            if(args.isObject(4)) {
                auto mask = args.asMatPtr(4);
                
                cv::bitwise_and(*src1, *src2, *dst, *mask);
            } else {
                cv::bitwise_and(*src1, *src2, *dst);
            }
        } break;
        case hashString("bitwise_not", 11): {
            auto src1 = args.asMatPtr(1);
            auto dst = args.asMatPtr(2);
            
            if(args.isObject(3)) {
                auto mask = args.asMatPtr(3);
                
                cv::bitwise_not(*src1, *dst, *mask);
            } else {
                cv::bitwise_not(*src1, *dst);
            }
        } break;
        case hashString("bitwise_or", 10): {
            auto src1 = args.asMatPtr(1);
            auto src2 = args.asMatPtr(2);
            auto dst = args.asMatPtr(3);
            
            if(args.isObject(4)) {
                auto mask = args.asMatPtr(4);
                
                cv::bitwise_or(*src1, *src2, *dst, *mask);
            } else {
                cv::bitwise_or(*src1, *src2, *dst);
            }
        } break;
        case hashString("bitwise_xor", 11): {
            auto src1 = args.asMatPtr(1);
            auto src2 = args.asMatPtr(2);
            auto dst = args.asMatPtr(3);
            
            if(args.isObject(4)) {
                auto mask = args.asMatPtr(4);
                
                cv::bitwise_xor(*src1, *src2, *dst, *mask);
            } else {
                cv::bitwise_xor(*src1, *src2, *dst);
            }
        } break;
        case hashString("borderInterpolate", 17): {
            auto p = args.asNumber(1);
            auto len = args.asNumber(2);
            auto borderType = args.asNumber(3);
            
            auto result = cv::borderInterpolate(p, len, borderType);
            value.setProperty(runtime, "value", result);
        } break;
        case hashString("calcCovarMatrix", 15): {
            auto samples = args.asMatVectorPtr(1);
            auto nsamples = args.asNumber(2);
            auto covar = args.asMatPtr(3);
            auto mean = args.asMatPtr(4);
            auto flags = args.asNumber(5);
            auto dtype = args.asNumber(6);
            
            cv::calcCovarMatrix((*samples).data(), nsamples, *covar, *mean, flags, dtype);
        } break;
        case hashString("cartToPolar", 11): {
            if(args.isMat(1)) {
                auto x = args.asMatPtr(1);
                auto y = args.asMatPtr(2);
                auto magnitude = args.asMatPtr(3);
                auto angle = args.asMatPtr(4);
                
                if(args.isBool(5)) {
                    auto angleInDegrees = args.asBool(5);
                    
                    cv::cartToPolar(*x, *y, *magnitude, *angle, angleInDegrees);
                } else {
                    cv::cartToPolar(*x, *y, *magnitude, *angle);
                }
            } else {
                auto x = args.asMatVectorPtr(1);
                auto y = args.asMatVectorPtr(2);
                auto magnitude = args.asMatVectorPtr(3);
                auto angle = args.asMatVectorPtr(4);
                
                if(args.isBool(5)) {
                    auto angleInDegrees = args.asBool(5);
                    
                    cv::cartToPolar(*x, *y, *magnitude, *angle, angleInDegrees);
                } else {
                    cv::cartToPolar(*x, *y, *magnitude, *angle);
                }
            }
        } break;
        case hashString("checkRange", 10): {
            auto quiet = args.asBool(2);
            auto pos = args.asPointPtr(3);
            auto minVal = args.asNumber(2);
            auto maxVal = args.asNumber(2);
            
            if(args.isMat(1)) {
                auto a = args.asMatPtr(1);
                cv::checkRange(*a, quiet, &(*pos), minVal, maxVal);
            } else {
                auto a = args.asMatVectorPtr(1);
                cv::checkRange(*a, quiet, &(*pos), minVal, maxVal);
            }
        } break;
//        case hashString("compare", 7): {
//            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto cmpop = arguments[4].asNumber();
//            
//            cv::compare(src1, src2, dst, cmpop);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
//        } break;
//        case hashString("completeSymm", 12): {
//            auto m = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto lowerToUpper = arguments[4].asBool();
//            
//            cv::completeSymm(m, lowerToUpper);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), m);
//        } break;
//        case hashString("convertFp16", 11): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            
//            cv::convertFp16(src, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("convertScaleAbs", 15): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            
//            if(arguments[4].isNumber()) {
//                auto alpha = arguments[3].asNumber();
//                auto beta = arguments[4].asNumber();
//                
//                cv::convertScaleAbs(src, dst, alpha, beta);
//            } else if(arguments[3].isNumber()) {
//                auto alpha = arguments[3].asNumber();
//                
//                cv::convertScaleAbs(src, dst, alpha);
//            } else {
//                cv::convertScaleAbs(src, dst);
//            }
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("copyMakeBorder", 14): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto top = arguments[3].asNumber();
//            auto bottom = arguments[4].asNumber();
//            auto left = arguments[5].asNumber();
//            auto right = arguments[6].asNumber();
//            auto borderType = arguments[7].asNumber();
//            auto value = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[8]));
//            
//            cv::copyMakeBorder(src, dst, top, bottom, left, right, borderType, value);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("copyTo", 6): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//           
//            cv::copyTo(src, dst, mask);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("countNonZero", 12): {
//            auto src = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//           
//            auto result = cv::countNonZero(src);
//            value.setProperty(runtime, "value", result);
//        } break;
//        case hashString("dct", 3): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto flags = arguments[3].asNumber();
//           
//            cv::dct(src, dst, flags);
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("determinant", 11): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//           
//            auto result = cv::determinant(src);
//            value.setProperty(runtime, "value", result);
//        } break;
//        case hashString("dft", 3): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto flags = arguments[3].asNumber();
//            auto nonzeroRows = arguments[4].asNumber();
//           
//            cv::dft(src, dst, flags, nonzeroRows);
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("divide", 6): {
//            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto scale = arguments[4].asNumber();
//       
//            if(arguments[5].isNumber()) {
//                auto dtype = arguments[5].asNumber();
//                
//                cv::divide(src1, src2, dst, scale, dtype);
//            } else {
//                cv::divide(src1, src2, dst, scale);
//            }
//         
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
//        } break;
//        case hashString("eigen", 5): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto eigenvalues = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto eigenvectors = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//          
//            cv::eigen(src, eigenvalues, eigenvectors);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), eigenvalues);
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), eigenvectors);
//        } break;
//        case hashString("eigenNonSymmetric", 17): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto eigenvalues = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto eigenvectors = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//          
//            cv::eigenNonSymmetric(src, eigenvalues, eigenvectors);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), eigenvalues);
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), eigenvectors);
//        } break;
//        case hashString("exp", 3): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//          
//            cv::exp(src, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("extractChannel", 14): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto coi = arguments[3].asNumber();
//          
//            cv::extractChannel(src, dst, coi);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("findNonZero", 11): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto idx = FOCV_JsiObject::type_from_wrap(runtime, arguments[2]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2])) :
//                FOCV_Storage::get<std::vector<cv::Point>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//          
//            cv::findNonZero(src, idx);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), idx);
//        } break;
//        case hashString("flip", 4): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto flipCode = arguments[3].asNumber();
//          
//            cv::flip(src, dst, flipCode);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("gemm", 4): {
//            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto alpha = arguments[3].asNumber();
//            auto src3 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto beta = arguments[5].asNumber();
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[6]));
//            auto flags = arguments[7].asNumber();
//            
//            cv::gemm(src1, src2, alpha, src3, beta, dst, flags);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[6]), dst);
//        } break;
//        case hashString("getOptimalDFTSize", 17): {
//            auto vecsize =  arguments[1].asNumber();
//           
//            auto result = cv::getOptimalDFTSize(vecsize);
//            value.setProperty(runtime, "value", result);
//        } break;
//        case hashString("hconcat", 7): {
//            auto srcs = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//          
//            cv::hconcat(srcs, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("idft", 4): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto flags = arguments[3].asNumber();
//            auto nonzeroRows = arguments[3].asNumber();
//          
//            cv::idft(src, dst, flags, nonzeroRows);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("inRange", 7): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto lowerBound = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto upperBound = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            
//            cv::inRange(src, lowerBound, upperBound, dst);
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]), dst);
//        } break;
//        case hashString("insertChannel", 13): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto coi = arguments[3].asNumber();
//         
//            cv::insertChannel(src, dst, coi);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("invert", 6): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto flags = arguments[3].asNumber();
//         
//            cv::invert(src, dst, flags);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("log", 3): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//      
//            cv::log(src, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("LUT", 3): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto lut = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//      
//            cv::LUT(src, lut, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
//        } break;
//        case hashString("magnitude", 9): {
//            auto x = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            
//            auto y = FOCV_JsiObject::type_from_wrap(runtime, arguments[2]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            
//            auto magnitude = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//      
//            cv::magnitude(x, y, magnitude);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), magnitude);
//        } break;
//        case hashString("Mahalanobis", 11): {
//            auto x = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            
//            auto y = FOCV_JsiObject::type_from_wrap(runtime, arguments[2]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            
//            auto icovar = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//      
//            cv::Mahalanobis(x, y, icovar);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), icovar);
//        } break;
//        case hashString("max", 3): {
//            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//      
//            cv::max(src1, src2, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
//        } break;
//        case hashString("mean", 4): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            std::string id = "";
//            
//            if(arguments[2].isObject()) {
//                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//                
//                auto scalar = cv::mean(src, mask);
//                std::string id = FOCV_Storage::save(scalar);
//            } else {
//                auto scalar = cv::mean(src);
//                std::string id = FOCV_Storage::save(scalar);
//            }
//            
//            return FOCV_JsiObject::wrap(runtime, "scalar", id);
//        } break;
//        case hashString("meanStdDev", 10): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto mean = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto stddev = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            
//            if(arguments[4].isObject()) {
//                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//                
//                cv::meanStdDev(src, mean, stddev, mask);
//            } else {
//                cv::meanStdDev(src, mean, stddev);
//            }
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), mean);
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), stddev);
//        } break;
//        case hashString("min", 3): {
//            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//          
//            cv::min(src1, src2, dst);
//
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
//        } break;
//        case hashString("minMaxLoc", 9): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            double min = 0;
//            double max = 0;
//            
//            if(arguments[2].isObject()) {
//                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//              
//                cv::minMaxIdx(src, &min, &max, NULL, NULL, mask);
//
//            } else {
//                cv::minMaxIdx(src, &min, &max);
//            }
//            
//            value.setProperty(runtime, "minVal", jsi::Value(min));
//            value.setProperty(runtime, "maxVal", jsi::Value(max));
//        } break;
//        case hashString("mulSpectrums", 12): {
//            auto a = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto b = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto c = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto flags = arguments[4].asNumber();
//            
//            if(arguments[5].isBool()) {
//                auto conjB = arguments[5].asBool();
//              
//                cv::mulSpectrums(a, b, c, flags, conjB);
//            } else {
//                cv::mulSpectrums(a, b, c, flags);
//            }
//
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), c);
//        } break;
//        case hashString("multiply", 8): {
//            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto scale = arguments[4].asNumber();
//           
//            if(arguments[5].isNumber()) {
//                auto dtype = arguments[5].asNumber();
//              
//                cv::multiply(src1, src2, dst, scale, dtype);
//            } else {
//                cv::multiply(src1, src2, dst, scale);
//            }
//
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
//        } break;
//        case hashString("mulTransposed", 13): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto aTa = arguments[3].asBool();
//            auto delta = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto scale = arguments[5].asNumber();
//           
//            if(arguments[6].isNumber()) {
//                auto dtype = arguments[6].asNumber();
//              
//                cv::mulTransposed(src, dst, aTa, delta, scale, dtype);
//            } else {
//                cv::mulTransposed(src, dst, aTa, delta, scale);
//            }
//
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("norm", 4): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto normType = arguments[2].asNumber();
//            double norm = 0;
//            
//            if(arguments[3].isObject()) {
//                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//              
//                norm = cv::norm(src, normType, mask);
//
//            } else {
//                norm = cv::norm(src, normType);
//            }
//            
//            value.setProperty(runtime, "norm", jsi::Value(norm));
//        } break;
//        case hashString("normalize", 9): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto alpha = arguments[3].asNumber();
//            auto normType = arguments[4].asNumber();
//           
//            cv::normalize(src, dst, alpha, normType);
//
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("patchNaNs", 9): {
//            auto a = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto alpha = arguments[2].asNumber();
//      
//            cv::patchNaNs(a, alpha);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), a);
//        } break;
//        case hashString("perspectiveTransform", 20): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto m = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//      
//            cv::perspectiveTransform(src, dst, m);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("phase", 5): {
//            auto x = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            
//            auto y = FOCV_JsiObject::type_from_wrap(runtime, arguments[2]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            
//            auto angle = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto angleInDegrees = arguments[2].asBool();
//            
//            cv::phase(x, y, angle, angleInDegrees);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), angle);
//        } break;
//        case hashString("pow", 3): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto power = arguments[2].asNumber();
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            
//            cv::pow(src, power, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
//        } break;
//        case hashString("PSNR", 3): {
//            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto R = arguments[3].asNumber();
//          
//            auto result = cv::PSNR(src1, src2, R);
//            
//            value.setProperty(runtime, "psnr", jsi::Value(result));
//        } break;
//        case hashString("reduce", 6): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto dim = arguments[3].asNumber();
//            auto rtype = arguments[4].asNumber();
//            auto dtype = arguments[5].asNumber();
//            
//            cv::reduce(src, dst, dim, rtype, dtype);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("repeat", 6): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto ny = arguments[2].asNumber();
//            auto nx = arguments[3].asNumber();
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//           
//            cv::repeat(src, ny, nx, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]), dst);
//        } break;
//        case hashString("scaleAdd", 8): {
//            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto alpha = arguments[2].asNumber();
//            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//           
//            cv::scaleAdd(src1, alpha, src2, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]), dst);
//        } break;
//        case hashString("solve", 5): {
//            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto flags = arguments[4].asNumber();
//         
//            auto result = cv::solve(src1, src2, dst, flags);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
//            
//            value.setProperty(runtime, "resolved", jsi::Value(result));
//        } break;
//        case hashString("solveCubic", 10): {
//            auto coeffs = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto roots = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//         
//            auto result = cv::solveCubic(coeffs, roots);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), roots);
//            
//            value.setProperty(runtime, "value", jsi::Value(result));
//        } break;
//        case hashString("solvePoly", 9): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto maxIters = arguments[3].asNumber();
//         
//            auto result = cv::solvePoly(src, dst, maxIters);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//            
//            value.setProperty(runtime, "value", jsi::Value(result));
//        } break;
//        case hashString("sort", 4): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto flags = arguments[3].asNumber();
//         
//            cv::sort(src, dst, flags);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("sortIdx", 7): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto flags = arguments[3].asNumber();
//         
//            cv::sortIdx(src, dst, flags);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("split", 5): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            
//            cv::split(src, dst);
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("sqrt", 4): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            
//            cv::sqrt(src, dst);
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("subtract", 8): {
//            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            
//            if(arguments[5].isNumber()) {
//                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//                auto dtype = arguments[5].asNumber();
//                
//                cv::subtract(src1, src2, dst, mask, dtype);
//            } else if(arguments[4].isObject()) {
//                auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//                
//                cv::subtract(src1, src2, dst, mask);
//            } else {
//                cv::subtract(src1, src2, dst);
//            }
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
//        } break;
//        case hashString("sum", 3): {
//            auto src = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//          
//            auto scalar = cv::sum(src);
//            std::string id = FOCV_Storage::save(scalar);
//          
//            return FOCV_JsiObject::wrap(runtime, "scalar", id);
//        } break;
//        case hashString("trace", 5): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//          
//            auto scalar = cv::trace(src);
//            std::string id = FOCV_Storage::save(scalar);
//          
//            return FOCV_JsiObject::wrap(runtime, "scalar", id);
//        } break;
//        case hashString("transform", 9): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto m = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//          
//            cv::transform(src, dst, m);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("transpose", 9): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//          
//            cv::transpose(src, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("vconcat", 7): {
//            auto src = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//          
//            cv::hconcat(src, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
        case hashString("cvtColor", 8): {
            auto src = args.asMatPtr(1);
            auto dst = args.asMatPtr(2);
            auto code = args.asNumber(3);

            if(args.isNumber(4)) {
                auto dsnCn = args.asNumber(4);
                
                cv::cvtColor(*src, *dst, code, dsnCn);
            } else {
                cv::cvtColor(*src, *dst, code);
            }
        } break;
//        case hashString("cvtColorTwoPlane", 16): {
//            auto src1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto src2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto code = arguments[4].getNumber();
//            
//            cv::cvtColorTwoPlane(src1, src2, dst, code);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), dst);
//        } break;
//        case hashString("demosaicing", 11): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto code = arguments[3].getNumber();
//            
//            if(arguments[4].isNumber()) {
//                auto dsnCn = arguments[4].getNumber();
//                
//                cv::demosaicing(src, dst, code, dsnCn);
//            } else {
//                cv::demosaicing(src, dst, code);
//            }
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("applyColorMap", 13): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto colormap = arguments[3].getNumber();
//            
//            cv::applyColorMap(src, dst, colormap);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("arrowedLine", 11): {
//            auto img = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto point1 = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto point2 = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto color = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto thickness = arguments[5].getNumber();
//            auto line_type = arguments[6].getNumber();
//            
//            cv::arrowedLine(img, point1, point2, color, thickness, line_type);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), img);
//        } break;
//        case hashString("circle", 6): {
//            auto img = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto center = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto radius = arguments[3].getNumber();
//            auto color = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto thickness = arguments[5].getNumber();
//            auto line_type = arguments[6].getNumber();
//            
//            cv::circle(img, center, radius, color, thickness, line_type);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), img);
//        } break;
//        case hashString("clipLine", 8): {
//            auto size = FOCV_Storage::get<cv::Size>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto point1 = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto point2 = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            
//            auto result = cv::clipLine(size, point1, point2);
//            
//            value.setProperty(runtime, "value", jsi::Value(result));
//        } break;
//        case hashString("drawContours", 12): {
//            auto img = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto contours = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto contourIdx = arguments[3].getNumber();
//            auto color = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto thickness = arguments[5].getNumber();
//            auto line_type = arguments[6].getNumber();
//            
//            cv::drawContours(img, contours, contourIdx, color, thickness, line_type);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), img);
//        } break;
//        case hashString("drawMarker", 10): {
//            auto img = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto position = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto color = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto markerType = arguments[4].getNumber();
//            auto markerSize = arguments[5].getNumber();
//            auto thickness = arguments[6].getNumber();
//            auto line_type = arguments[7].getNumber();
//            
//            cv::drawMarker(img, position, color, markerType, markerSize, thickness, line_type);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), img);
//        } break;
//        case hashString("ellipse", 7): {
//            auto img = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto center = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto axes = FOCV_Storage::get<cv::Size>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto angle = arguments[4].getNumber();
//            auto startAngle = arguments[5].getNumber();
//            auto endAngle = arguments[6].getNumber();
//            auto color = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[7]));
//            auto thickness = arguments[8].getNumber();
//            auto line_type = arguments[9].getNumber();
//            
//            cv::ellipse(img, center, axes, angle, startAngle, endAngle, color, thickness, line_type);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), img);
//        } break;
//        case hashString("fillConvexPoly", 14): {
//            auto img = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto pts = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto color = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto line_type = arguments[4].getNumber();
//            
//            cv::fillConvexPoly(img, pts, color, line_type);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), img);
//        } break;
//        case hashString("fillPoly", 8): {
//            auto img = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto pts = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto color = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto line_type = arguments[4].getNumber();
//            
//            cv::fillPoly(img, pts, color, line_type);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), img);
//        } break;
//        case hashString("line", 4): {
//            auto img = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto point1 = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto point2 = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto color = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto thickness = arguments[5].getNumber();
//            auto line_type = arguments[6].getNumber();
//            
//            cv::line(img, point1, point2, color, thickness, line_type);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), img);
//        } break;
//        case hashString("polylines", 9): {
//            auto img = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto pts = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto isClosed = arguments[3].getBool();
//            auto color = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto thickness = arguments[5].getNumber();
//            auto line_type = arguments[6].getNumber();
//            
//            cv::polylines(img, pts, isClosed, color, thickness, line_type);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), img);
//        } break;
//        case hashString("rectangle", 9): {
//            auto img = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto point1 = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto point2 = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto color = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto thickness = arguments[5].getNumber();
//            auto line_type = arguments[6].getNumber();
//            
//            cv::rectangle(img, point1, point2, color, thickness, line_type);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]), img);
//        } break;
//        case hashString("Canny", 5): {
//            auto image = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto edges = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto threshold1 = arguments[3].getNumber();
//            auto threshold2 = arguments[4].getNumber();
//            
//            cv::Canny(image, edges, threshold1, threshold2);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), edges);
//        } break;
//        case hashString("cornerHarris", 12): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto blockSize = arguments[3].getNumber();
//            auto ksize = arguments[4].getNumber();
//            auto k = arguments[5].getNumber();
//            
//            cv::cornerHarris(src, dst, blockSize, ksize, k);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("cornerMinEigenVal", 17): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto blockSize = arguments[3].getNumber();
//            
//            cv::cornerMinEigenVal(src, dst, blockSize);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("goodFeaturesToTrack", 19): {
//            auto image = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto corners = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto maxCorners = arguments[3].getNumber();
//            auto qualityLevel = arguments[4].getNumber();
//            auto minDistance = arguments[5].getNumber();
//            
//            cv::goodFeaturesToTrack(image, corners, maxCorners, qualityLevel, minDistance);
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), corners);
//        } break;
//        case hashString("HoughCircles", 12): {
//            auto image = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto circles = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto method = arguments[3].getNumber();
//            auto dp = arguments[4].getNumber();
//            auto minDist = arguments[5].getNumber();
//            
//            if(arguments[7].isNumber()) {
//                auto param1 = arguments[6].asNumber();
//                auto param2 = arguments[7].asNumber();
//                
//                cv::HoughCircles(image, circles, method, dp, minDist, param1, param2);
//            } else if(arguments[4].isObject()) {
//                auto param1 = arguments[6].asNumber();
//                
//                cv::HoughCircles(image, circles, method, dp, minDist, param1);
//            } else {
//                cv::HoughCircles(image, circles, method, dp, minDist);
//            }
//  
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), circles);
//        } break;
//        case hashString("HoughLines", 10): {
//            auto image = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto lines = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto rho = arguments[3].getNumber();
//            auto theta = arguments[4].getNumber();
//            auto threshold = arguments[5].getNumber();
//          
//            cv::HoughLines(image, lines, rho, theta, threshold);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), lines);
//        } break;
//        case hashString("HoughLinesP", 11): {
//            auto image = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto lines = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto rho = arguments[3].getNumber();
//            auto theta = arguments[4].getNumber();
//            auto threshold = arguments[5].getNumber();
//          
//            cv::HoughLinesP(image, lines, rho, theta, threshold);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), lines);
//        } break;
//        case hashString("bilateralFilter", 15): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto d = arguments[3].getNumber();
//            auto sigmaColor = arguments[4].getNumber();
//            auto sigmaSpace = arguments[5].getNumber();
//            auto borderType = arguments[6].getNumber();
//          
//            cv::bilateralFilter(src, dst, d, sigmaColor, sigmaSpace, borderType);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("blur", 4): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto ksize = FOCV_Storage::get<cv::Size>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto anchor = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto borderType = arguments[5].getNumber();
//          
//            cv::blur(src, dst, ksize, anchor, borderType);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("boxFilter", 9): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto ddepth = arguments[3].getNumber();
//            auto ksize = FOCV_Storage::get<cv::Size>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto anchor = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[5]));
//            auto normalize = arguments[6].getBool();
//            auto borderType = arguments[7].getNumber();
//          
//            cv::boxFilter(src, dst, ddepth, ksize, anchor, normalize, borderType);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("buildPyramid", 12): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto maxlevel = arguments[3].getNumber();
//            auto borderType = arguments[4].getNumber();
//          
//            cv::buildPyramid(src, dst, maxlevel, borderType);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("dilate", 6): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto kernel = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto anchor = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto iterations = arguments[5].getNumber();
//            auto borderType = arguments[6].getNumber();
//            auto borderValue = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[7]));
//            
//            cv::dilate(src, dst, kernel, anchor, iterations, borderType, borderValue);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("erode", 5): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto kernel = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto anchor = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto iterations = arguments[5].getNumber();
//            auto borderType = arguments[6].getNumber();
//            auto borderValue = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[7]));
//            
//            cv::erode(src, dst, kernel, anchor, iterations, borderType, borderValue);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("filter2D", 8): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto ddepth = arguments[3].getNumber();
//            auto kernel = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto anchor = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[5]));
//            auto delat = arguments[6].getNumber();
//            auto borderType = arguments[7].getNumber();
//            
//            cv::filter2D(src, dst, ddepth, kernel, anchor, delat, borderType);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("GaussianBlur", 12): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto ksize = FOCV_Storage::get<cv::Size>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto sigmaX = arguments[4].getNumber();
//            auto sigmaY = arguments[5].getNumber();
//            auto borderType = arguments[6].getNumber();
//            
//            cv::GaussianBlur(src, dst, ksize, sigmaX, sigmaY, borderType);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("getGaborKernel", 14): {
//            auto ksize = FOCV_Storage::get<cv::Size>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto sigma = arguments[2].getNumber();
//            auto theta = arguments[3].getNumber();
//            auto lambd = arguments[4].getNumber();
//            auto gamma = arguments[5].getNumber();
//            auto psi = arguments[6].getNumber();
//            auto ktype = arguments[7].getNumber();
//            
//            cv::Mat result = cv::getGaborKernel(ksize, sigma, theta, lambd, gamma, psi, ktype);
//            std::string id = FOCV_Storage::save(result);
//          
//            return FOCV_JsiObject::wrap(runtime, "mat", id);
//        } break;
//        case hashString("getGaussianKernel", 17): {
//            auto ksize = arguments[2].getNumber();
//            auto sigma = arguments[3].getNumber();
//            auto ktype = arguments[4].getNumber();
//            
//            cv::Mat result = cv::getGaussianKernel(ksize, sigma, ktype);
//            std::string id = FOCV_Storage::save(result);
//          
//            return FOCV_JsiObject::wrap(runtime, "mat", id);
//        } break;
//        case hashString("Laplacian", 9): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto ddepth = arguments[3].getNumber();
//            auto ksize = arguments[4].getNumber();
//            auto scale = arguments[5].getNumber();
//            auto delta = arguments[6].getNumber();
//            auto borderType = arguments[7].getNumber();
//            
//            cv::Laplacian(src, dst, ddepth, ksize, scale, delta, borderType);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("medianBlur", 10): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto ksize = arguments[3].getNumber();
//          
//            cv::medianBlur(src, dst, ksize);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("morphologyEx", 12): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto op = arguments[3].getNumber();
//            auto kernel = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//            auto anchor = FOCV_Storage::get<cv::Point>(FOCV_JsiObject::id_from_wrap(runtime, arguments[5]));
//            auto iterations = arguments[6].getNumber();
//            auto borderType = arguments[7].getNumber();
//            auto borderValue = FOCV_Storage::get<cv::Scalar>(FOCV_JsiObject::id_from_wrap(runtime, arguments[8]));
//          
//            cv::morphologyEx(src, dst, op, kernel, anchor, iterations, borderType, borderValue);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("adaptiveThreshold", 17): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto maxValue = arguments[3].getNumber();
//            auto adaptiveMethod = arguments[4].getNumber();
//            auto thresholdType = arguments[5].getNumber();
//            auto blockSize = arguments[6].getNumber();
//            auto C = arguments[7].getNumber();
//          
//            cv::adaptiveThreshold(src, dst, maxValue, adaptiveMethod, thresholdType, blockSize, C);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("distanceTransform", 17): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto distanceType = arguments[3].getNumber();
//            auto maskSize = arguments[4].getNumber();
//          
//            cv::distanceTransform(src, dst, distanceType, maskSize);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("integral", 8): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//          
//            cv::integral(src, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("threshold", 9): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto thresh = arguments[3].getNumber();
//            auto maxval = arguments[4].getNumber();
//            auto type = arguments[5].getNumber();
//          
//            cv::threshold(src, dst, thresh, maxval, type);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("matchTemplate", 13): {
//            auto image = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto templ = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto result = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto method = arguments[4].getNumber();
//            auto mask = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[5]));
//
//            cv::matchTemplate(image, templ, result, method, mask);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), result);
//        } break;
//        case hashString("approxPolyDP", 12): {
//            auto curve = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto approxCurve = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto epsilon = arguments[3].getNumber();
//            auto closed = arguments[4].getBool();
//
//            cv::approxPolyDP(curve, approxCurve, epsilon, closed);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), approxCurve);
//        } break;
//        case hashString("arcLength", 9): {
//            auto curve = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat" ?
//                FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])) :
//                FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto closed = arguments[2].getBool();
//
//            auto result = cv::arcLength(curve, closed);
//            value.setProperty(runtime, "value", jsi::Value(result));
//        } break;
//        case hashString("boundingRect", 12): {
//            cv::Rect rect;
//            if(FOCV_JsiObject::type_from_wrap(runtime, arguments[1]) == "mat") {
//                rect = cv::boundingRect(FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])));
//            } else {
//                rect = cv::boundingRect(FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1])));
//            }
//            
//            std::string id = FOCV_Storage::save(rect);
//            
//            return FOCV_JsiObject::wrap(runtime, "rect", id);
//        } break;
//        case hashString("connectedComponents", 19): {
//            auto image = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto labels = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//
//            auto result = cv::connectedComponents(image, labels);
//            value.setProperty(runtime, "value", jsi::Value(result));
//        } break;
//        case hashString("connectedComponentsWithStats", 28): {
//            auto image = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto labels = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto stats = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//            auto centroids = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[4]));
//
//            auto result = cv::connectedComponentsWithStats(image, labels, stats, centroids);
//            value.setProperty(runtime, "value", jsi::Value(result));
//        } break;
//        case hashString("contourArea", 11): {
//            auto type = FOCV_JsiObject::type_from_wrap(runtime, arguments[1]);
//            auto id = FOCV_JsiObject::id_from_wrap(runtime, arguments[1]);
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto oriented = arguments[2].getBool();
//            
//            value.setProperty(runtime, "value", contourArea(src, oriented));
//        } break;
//        case hashString("convexHull", 10): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//          
//            cv::convexHull(src, dst);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("convexityDefects", 16): {
//            auto contour = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto convexHull = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto convexityDefects = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]));
//          
//            cv::convexityDefects(contour, convexHull, convexityDefects);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), convexHull);
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[3]), convexityDefects);
//        } break;
//        case hashString("findContours", 12): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto dst = FOCV_Storage::get<std::vector<cv::Mat>>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto mode = arguments[3].getNumber();
//            auto method = arguments[4].getNumber();
//
//            cv::findContours(src, dst, mode, method);
//
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), dst);
//        } break;
//        case hashString("fitLine", 7): {
//            auto points = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto line = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]));
//            auto disType = arguments[3].getNumber();
//            auto param = arguments[4].getNumber();
//            auto reps = arguments[5].getNumber();
//            auto aeps = arguments[6].getNumber();
//
//            cv::fitLine(points, line, disType, param, reps, aeps);
//            
//            FOCV_Storage::save(FOCV_JsiObject::id_from_wrap(runtime, arguments[2]), line);
//        } break;
//        case hashString("isContourConvex", 15): {
//            auto contour = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//
//            value.setProperty(runtime, "value", jsi::Value(cv::isContourConvex(contour)));
//        } break;
//        case hashString("matchShapes", 11): {
//            auto contour1 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto contour2 = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            auto method = arguments[4].getNumber();
//            auto parameter = arguments[5].getNumber();
//            
//            auto result = cv::matchShapes(contour1, contour2, method, parameter);
//
//            value.setProperty(runtime, "value", jsi::Value(result));
//        } break;
//        case hashString("minAreaRect", 11): {
//            auto src = FOCV_Storage::get<cv::Mat>(FOCV_JsiObject::id_from_wrap(runtime, arguments[1]));
//            
//            auto rect = cv::minAreaRect(src);
//
//            auto id = FOCV_Storage::save(rect);
//            return FOCV_JsiObject::wrap(runtime, "rotated_rect", id);
//        } break;
    }
    
    return value;
}
