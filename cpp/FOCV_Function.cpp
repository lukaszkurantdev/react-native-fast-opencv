//
//  FOCV_Function.cpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 06/08/2024.
//
#include <iostream>
#include "FOCV_Function.hpp"
#include "FOCV_Storage.hpp"
#include "FOCV_Ids.hpp"
#include <FOCV_JsiObject.hpp>
#include <opencv2/opencv.hpp>
#include "FOCV_FunctionArguments.hpp"

// General idea and this function for hashing is from
// https://mrousavy.com/blog/Hashing-String-Ifs
constexpr uint64_t hashString(const char* str, size_t length) {
  uint64_t hash = 14695981039346656037ull;
  const uint64_t fnv_prime = 1099511628211ull;
 
  for (size_t i = 0; i < length; ++i) {
    hash ^= static_cast<uint64_t>(str[i]);
    hash *= fnv_prime;
  }
 
  return hash;
}

// General idea of invocation switch is from react-native-opencv3 library,
// but it was adapted and optimized.
jsi::Object FOCV_Function::invoke(jsi::Runtime& runtime, const jsi::Value* arguments, size_t count) {
  jsi::Object value(runtime);
  
  FOCV_FunctionArguments args(runtime, arguments, count);
  
  auto functionName = args.asString(0);
  
  try {
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
        
        if (count > 4) {
          auto mask = args.asMatPtr(4);
          if (count > 5) {
            auto dtype = args.asNumber(5);
            
            cv::add(*src1, *src2, *dst, *mask, dtype);
            break;
          }
          cv::add(*src1, *src2, *dst, *mask);
          break;
        }
        cv::add(*src1, *src2, *dst);
      } break;
      case hashString("addWeighted", 11): {
        auto src1 = args.asMatPtr(1);
        auto alpha = args.asNumber(2);
        auto src2 = args.asMatPtr(3);
        auto beta = args.asNumber(4);
        auto gamma = args.asNumber(5);
        auto dst = args.asMatPtr(6);
        
        if (count > 7) {
          auto dtype = args.asNumber(7);
          
          cv::addWeighted(*src1, alpha, *src2, beta, gamma, *dst, dtype);
          break;
        }
        cv::addWeighted(*src1, alpha, *src2, beta, gamma, *dst);
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
        auto dst = args.asMatPtr(3);
        
        if (args.isMat(1)) {
          auto src1 = args.asMatPtr(1);
          
          if(args.isScalar(2)) {
            auto src2 = args.asScalarPtr(2);
            cv::bitwise_and(*src1, *src2, *dst);
            
            if (count > 4) {
              auto mask = args.asMatPtr(4);
              
              cv::bitwise_and(*src1, *src2, *dst, *mask);
              break;
            }
            
          } else {
            auto src2 = args.asMatPtr(2);
            
            if (count > 4) {
              auto mask = args.asMatPtr(4);
              
              cv::bitwise_and(*src1, *src2, *dst, *mask);
              break;
            }
            
            cv::bitwise_and(*src1, *src2, *dst);
          }
        } else {
          auto src1 = args.asScalarPtr(1);
          auto src2 = args.asMatPtr(2);

          
          if (count > 4) {
            auto mask = args.asMatPtr(4);
            
            cv::bitwise_and(*src1, *src2, *dst, *mask);
            break;
          }
          
          cv::bitwise_and(*src1, *src2, *dst);
        }
      } break;
      case hashString("bitwise_not", 11): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        
        if (count > 3) {
          auto mask = args.asMatPtr(3);
          
          cv::bitwise_not(*src, *dst, *mask);
          break;
        }
        cv::bitwise_not(*src, *dst);
      } break;
      case hashString("bitwise_or", 10): {
        auto dst = args.asMatPtr(3);
        
        if (args.isMat(1)) {
          auto src1 = args.asMatPtr(1);
          
          if(args.isScalar(2)) {
            auto src2 = args.asScalarPtr(2);
            cv::bitwise_or(*src1, *src2, *dst);
            
            if (count > 4) {
              auto mask = args.asMatPtr(4);
              
              cv::bitwise_or(*src1, *src2, *dst, *mask);
              break;
            }
            
          } else {
            auto src2 = args.asMatPtr(2);
            
            if (count > 4) {
              auto mask = args.asMatPtr(4);
              
              cv::bitwise_or(*src1, *src2, *dst, *mask);
              break;
            }
            
            cv::bitwise_or(*src1, *src2, *dst);
          }
        } else {
          auto src1 = args.asScalarPtr(1);
          auto src2 = args.asMatPtr(2);
          
          if (count > 4) {
            auto mask = args.asMatPtr(4);
            
            cv::bitwise_or(*src1, *src2, *dst, *mask);
            break;
          }
          
          cv::bitwise_or(*src1, *src2, *dst);
        }
      } break;
      case hashString("bitwise_xor", 11): {
        auto dst = args.asMatPtr(3);
        
        if (args.isMat(1)) {
          auto src1 = args.asMatPtr(1);
          
          if(args.isScalar(2)) {
            auto src2 = args.asScalarPtr(2);
            cv::bitwise_xor(*src1, *src2, *dst);
            
            if (count > 4) {
              auto mask = args.asMatPtr(4);
              
              cv::bitwise_xor(*src1, *src2, *dst, *mask);
              break;
            }
            
          } else {
            auto src2 = args.asMatPtr(2);
            
            if (count > 4) {
              auto mask = args.asMatPtr(4);
              
              cv::bitwise_xor(*src1, *src2, *dst, *mask);
              break;
            }
            
            cv::bitwise_xor(*src1, *src2, *dst);
          }
        } else {
          auto src1 = args.asScalarPtr(1);
          auto src2 = args.asMatPtr(2);
          
          if (count > 4) {
            auto mask = args.asMatPtr(4);
            
            cv::bitwise_xor(*src1, *src2, *dst, *mask);
            break;
          }
          
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
        auto angleInDegrees = (count > 5) ? args.asBool(5) : false;
        if (args.isMat(1)) {
          auto x = args.asMatPtr(1);
          auto y = args.asMatPtr(2);
          auto magnitude = args.asMatPtr(3);
          auto angle = args.asMatPtr(4);
          
          cv::cartToPolar(*x, *y, *magnitude, *angle, angleInDegrees);
        } else {
          auto x = args.asMatVectorPtr(1);
          auto y = args.asMatVectorPtr(2);
          auto magnitude = args.asMatVectorPtr(3);
          auto angle = args.asMatVectorPtr(4);
          
          cv::cartToPolar(*x, *y, *magnitude, *angle, angleInDegrees);
        }
      } break;
      case hashString("checkRange", 10): {
        auto quiet = args.asBool(2);
        auto pos = args.asPointPtr(3);
        auto minVal = args.asNumber(4);
        auto maxVal = args.asNumber(5);
        
        if (args.isMat(1)) {
          auto a = args.asMatPtr(1);
          cv::checkRange(*a, quiet, &(*pos), minVal, maxVal);
        } else {
          auto a = args.asMatVectorPtr(1);
          cv::checkRange(*a, quiet, &(*pos), minVal, maxVal);
        }
      } break;
      case hashString("clone", 5): {
        auto src = args.asMatPtr(1);

        cv::Mat result = (*src).clone();
        std::string id = FOCV_Storage::save(result);
        
        return FOCV_JsiObject::wrap(runtime, "mat", id);
      } break;
        
      case hashString("compare", 7): {
        auto cmpop = args.asNumber(4);
        auto dst = args.asMatPtr(3);
        
        if (args.isMat(1)) {
          auto src1 = args.asMatPtr(1);
          
          if(args.isScalar(2)) {
            auto src2 = args.asScalarPtr(2);
            cv::compare(*src1, *src2, *dst, cmpop);
          } else {
            auto src2 = args.asMatPtr(2);
            cv::compare(*src1, *src2, *dst, cmpop);
          }
        } else {
          auto src1 = args.asScalarPtr(1);
          auto src2 = args.asMatPtr(2);

          cv::compare(*src1, *src2, *dst, cmpop);
        }
       
      } break;
      case hashString("completeSymm", 12): {
        auto lowerToUpper = args.asBool(2);
        
        if (args.isMat(1)) {
          auto m = args.asMatPtr(1);
          cv::completeSymm(*m, lowerToUpper);
        } else {
          auto m = args.asMatVectorPtr(1);
          cv::completeSymm(*m, lowerToUpper);
        }
      } break;
      case hashString("convertFp16", 11): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        
        cv::convertFp16(*src, *dst);
      } break;
      case hashString("convertScaleAbs", 15): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        
        if (count > 3) {
          auto alpha = args.asNumber(3);
          if (count > 4) {
            auto beta = args.asNumber(4);
            
            cv::convertScaleAbs(*src, *dst, alpha, beta);
            break;
          }
          cv::convertScaleAbs(*src, *dst, alpha);
          break;
        }
        cv::convertScaleAbs(*src, *dst);
      } break;
      case hashString("copyMakeBorder", 14): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto top = args.asNumber(3);
        auto bottom = args.asNumber(4);
        auto left = args.asNumber(5);
        auto right = args.asNumber(6);
        auto borderType = args.asNumber(7);
        auto value = args.asScalarPtr(8);
        
        cv::copyMakeBorder(*src, *dst, top, bottom, left, right, borderType, *value);
      } break;
      case hashString("copyTo", 6): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto mask = args.asMatPtr(3);
        
        cv::copyTo(*src, *dst, *mask);
      } break;
      case hashString("countNonZero", 12): {
        if (args.isMat(1)) {
          auto src = args.asMatPtr(1);
          auto result = cv::countNonZero(*src);
          value.setProperty(runtime, "value", result);
        } else {
          auto src = args.asMatVectorPtr(1);
          auto result = cv::countNonZero(*src);
          value.setProperty(runtime, "value", result);
        }
      } break;
      case hashString("crop", 4): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto rect = args.asRectPtr(3);
        
        (*src)(*rect).copyTo(*dst);
      } break;
      case hashString("dct", 3): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto flags = args.asNumber(3);
        
        cv::dct(*src, *dst, flags);
      } break;
      case hashString("determinant", 11): {
        auto src = args.asMatPtr(1);
        
        auto result = cv::determinant(*src);
        value.setProperty(runtime, "value", result);
      } break;
      case hashString("dft", 3): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto flags = args.asNumber(3);
        auto nonzeroRows = args.asNumber(4);
        
        cv::dft(*src, *dst, flags, nonzeroRows);
      } break;
      case hashString("divide", 6): {
        auto src1 = args.asMatPtr(1);
        auto src2 = args.asMatPtr(2);
        auto dst = args.asMatPtr(3);
        auto scale = args.asNumber(4);
        
        if (count > 5) {
          auto dtype = args.asNumber(5);
          
          cv::divide(*src1, *src2, *dst, scale, dtype);
          break;
        }
        cv::divide(*src1, *src2, *dst, scale);
      } break;
      case hashString("eigen", 5): {
        auto src = args.asMatPtr(1);
        auto eigenvalues = args.asMatPtr(2);
        auto eigenvectors = args.asMatPtr(3);
        
        cv::eigen(*src, *eigenvalues, *eigenvectors);
      } break;
      case hashString("eigenNonSymmetric", 17): {
        auto src = args.asMatPtr(1);
        auto eigenvalues = args.asMatPtr(2);
        auto eigenvectors = args.asMatPtr(3);
        
        cv::eigenNonSymmetric(*src, *eigenvalues, *eigenvectors);
      } break;
      case hashString("exp", 3): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        
        cv::exp(*src, *dst);
      } break;
      case hashString("extractChannel", 14): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto coi = args.asNumber(3);
        
        cv::extractChannel(*src, *dst, coi);
      } break;
      case hashString("findNonZero", 11): {
        auto src = args.asMatPtr(1);
        
        if (args.isMat(2)) {
          auto idx = args.asMatPtr(2);
          cv::findNonZero(*src, *idx);
        } else {
          auto idx = args.asPointVectorPtr(2);
          cv::findNonZero(*src, *idx);
        }
      } break;
      case hashString("flip", 4): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto flipCode = args.asNumber(3);
        
        cv::flip(*src, *dst, flipCode);
      } break;
      case hashString("floodFill", 9): {
        auto src = args.asMatPtr(1);
        auto mask = args.asMatPtr(2);
        auto seedPoint = args.asPointPtr(3);
        auto newVal = args.asScalarPtr(4);
        auto rect = args.asRectPtr(5);
        auto loDiff = args.asScalarPtr(6);
        auto upDiff = args.asScalarPtr(7);
        auto flags = args.asNumber(8);
        
        int area = floodFill(*src, *mask, *seedPoint, *newVal, &(*rect), *loDiff, *upDiff, flags);
        value.setProperty(runtime, "value", area);
      } break;
      case hashString("gemm", 4): {
        auto src1 = args.asMatPtr(1);
        auto src2 = args.asMatPtr(2);
        auto alpha = args.asNumber(3);
        auto src3 = args.asMatPtr(4);
        auto beta = args.asNumber(5);
        auto dst = args.asMatPtr(6);
        auto flags = args.asNumber(7);
        
        cv::gemm(*src1, *src2, alpha, *src3, beta, *dst, flags);
      } break;
      case hashString("getOptimalDFTSize", 17): {
        auto vecsize = args.asNumber(1);
        
        auto result = cv::getOptimalDFTSize(vecsize);
        value.setProperty(runtime, "value", result);
      } break;
      case hashString("getRotationMatrix2D", 19): {
        auto center = args.asPoint2fPtr(1);
        auto angle = args.asNumber(2);
        auto scale = args.asNumber(3);
        auto dst = args.asMatPtr(4);
        
        *dst = cv::getRotationMatrix2D(*center, angle, scale);
      } break;
      case hashString("hconcat", 7): {
        auto srcs = args.asMatVectorPtr(1);
        auto dst = args.asMatPtr(2);
        
        cv::hconcat(*srcs, *dst);
      } break;
      case hashString("idft", 4): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto flags = args.asNumber(3);
        auto nonzeroRows = args.asNumber(4);
        
        cv::idft(*src, *dst, flags, nonzeroRows);
      } break;
      case hashString("inRange", 7): {
        auto src = args.asMatPtr(1);
        auto lowerBound = args.asScalarPtr(2);
        auto upperBound = args.asScalarPtr(3);
        auto dst = args.asMatPtr(4);
        
        cv::inRange(*src, *lowerBound, *upperBound, *dst);
      } break;
      case hashString("insertChannel", 13): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto coi = args.asNumber(3);
        
        cv::insertChannel(*src, *dst, coi);
      } break;
      case hashString("invert", 6): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto flags = args.asNumber(3);
        
        cv::invert(*src, *dst, flags);
      } break;
      case hashString("log", 3): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        
        cv::log(*src, *dst);
      } break;
      case hashString("LUT", 3): {
        auto src = args.asMatPtr(1);
        auto lut = args.asMatPtr(2);
        auto dst = args.asMatPtr(3);
        
        cv::LUT(*src, *lut, *dst);
      } break;
      case hashString("magnitude", 9): {
        auto magnitude = args.asMatPtr(3);
        
        if (args.isMat(1)) {
          auto x = args.asMatPtr(1);
          auto y = args.asMatPtr(2);
          cv::magnitude(*x, *y, *magnitude);
        } else {
          auto x = args.asMatVectorPtr(1);
          auto y = args.asMatVectorPtr(2);
          cv::magnitude(*x, *y, *magnitude);
        }
      } break;
      case hashString("Mahalanobis", 11): {
        auto icovar = args.asMatPtr(3);
        
        if (args.isMat(1)) {
          auto x = args.asMatPtr(1);
          auto y = args.asMatPtr(2);
          cv::Mahalanobis(*x, *y, *icovar);
        } else {
          auto x = args.asMatVectorPtr(1);
          auto y = args.asMatVectorPtr(2);
          cv::Mahalanobis(*x, *y, *icovar);
        }
      } break;
      case hashString("max", 3): {
        auto src1 = args.asMatPtr(1);
        auto src2 = args.asMatPtr(2);
        auto dst = args.asMatPtr(3);
        
        cv::max(*src1, *src2, *dst);
      } break;
      case hashString("mean", 4): {
        std::string id;
        auto src = args.asMatPtr(1);
        
        if (count > 2) {
          auto mask = args.asMatPtr(2);
          
          auto scalar = cv::mean(*src, *mask);
          id = FOCV_Storage::save(scalar);
        } else {
          auto scalar = cv::mean(*src);
          id = FOCV_Storage::save(scalar);
        }
        
        return FOCV_JsiObject::wrap(runtime, "scalar", id);
      } break;
      case hashString("meanStdDev", 10): {
        auto src = args.asMatPtr(1);
        auto mean = args.asMatPtr(2);
        auto stddev = args.asMatPtr(3);
        
        if (count > 4) {
          auto mask = args.asMatPtr(4);
          
          cv::meanStdDev(*src, *mean, *stddev, *mask);
          break;
        }
        cv::meanStdDev(*src, *mean, *stddev);
      } break;
      case hashString("min", 3): {
        auto src1 = args.asMatPtr(1);
        auto src2 = args.asMatPtr(2);
        auto dst = args.asMatPtr(3);
        
        cv::min(*src1, *src2, *dst);
      } break;
      case hashString("minMaxLoc", 9): {
        auto src = args.asMatPtr(1);
        double min = 0;
        double max = 0;
        
        Point minLoc; Point maxLoc;
        
        if (count > 2) {
          auto mask = args.asMatPtr(2);
          
          cv::minMaxLoc(*src, &min, &max, &minLoc, &maxLoc, *mask);
        } else {
          cv::minMaxLoc(*src, &min, &max, &minLoc, &maxLoc);
        }
        
        value.setProperty(runtime, "minVal", jsi::Value(min));
        value.setProperty(runtime, "maxVal", jsi::Value(max));
        value.setProperty(runtime, "minX", minLoc.x);
        value.setProperty(runtime, "minY", minLoc.y);
        value.setProperty(runtime, "maxX", maxLoc.x);
        value.setProperty(runtime, "maxY", maxLoc.y);
      } break;
      case hashString("mulSpectrums", 12): {
        auto a = args.asMatPtr(1);
        auto b = args.asMatPtr(2);
        auto c = args.asMatPtr(3);
        auto flags = args.asNumber(4);
        
        if (count > 5) {
          auto conjB = args.asBool(5);
          
          cv::mulSpectrums(*a, *b, *c, flags, conjB);
          break;
        }
        cv::mulSpectrums(*a, *b, *c, flags);
      } break;
      case hashString("multiply", 8): {
        auto src1 = args.asMatPtr(1);
        auto src2 = args.asMatPtr(2);
        auto dst = args.asMatPtr(3);
        auto scale = args.asNumber(4);
        
        if (count > 5) {
          auto dtype = args.asNumber(5);
          
          cv::multiply(*src1, *src2, *dst, scale, dtype);
          break;
        }
        cv::multiply(*src1, *src2, *dst, scale);
      } break;
      case hashString("mulTransposed", 13): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto aTa = args.asBool(3);
        auto delta = args.asMatPtr(4);
        auto scale = args.asNumber(5);
        
        if (count > 6) {
          auto dtype = args.asNumber(6);
          
          cv::mulTransposed(*src, *dst, aTa, *delta, scale, dtype);
          break;
        }
        cv::mulTransposed(*src, *dst, aTa, *delta, scale);
      } break;
      case hashString("norm", 4): {
        auto src = args.asMatPtr(1);
        auto normType = args.asNumber(2);
        double norm = 0;
        
        if (count > 3) {
          auto mask = args.asMatPtr(3);

          norm = cv::norm(*src, normType, *mask);
        } else {
          norm = cv::norm(*src, normType);
        }
        
        value.setProperty(runtime, "norm", jsi::Value(norm));
      } break;
      case hashString("normalize", 9): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto alpha = args.asNumber(3);
        auto normType = args.asNumber(4);
        
        cv::normalize(*src, *dst, alpha, normType);
      } break;
      case hashString("merge", 5): {
        auto src = args.asMatVectorPtr(1);
        auto dst = args.asMatPtr(2);
        
        cv::merge(*src, *dst);
      } break;
      case hashString("patchNaNs", 9): {
        auto alpha = args.asNumber(2);
        
        if (args.isMat(1)) {
          auto a = args.asMatPtr(1);
          cv::patchNaNs(*a, alpha);
        } else {
          auto a = args.asMatVectorPtr(1);
          cv::patchNaNs(*a, alpha);
        }
      } break;
      case hashString("perspectiveTransform", 20): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto m = args.asMatPtr(3);
        
        cv::perspectiveTransform(*src, *dst, *m);
      } break;
      case hashString("phase", 5): {
        auto angle = args.asMatPtr(3);
        auto angleInDegrees = args.asBool(4);
        
        if (args.isMat(1)) {
          auto x = args.asMatPtr(1);
          auto y = args.asMatPtr(2);
          cv::phase(*x, *y, *angle, angleInDegrees);
        } else {
          auto x = args.asMatVectorPtr(1);
          auto y = args.asMatVectorPtr(2);
          cv::phase(*x, *y, *angle, angleInDegrees);
        }
      } break;
      case hashString("pow", 3): {
        auto src = args.asMatPtr(1);
        auto power = args.asNumber(2);
        auto dst = args.asMatPtr(3);
        
        cv::pow(*src, power, *dst);
      } break;
      case hashString("PSNR", 4): {
        auto src1 = args.asMatPtr(1);
        auto src2 = args.asMatPtr(2);
        auto R = args.asNumber(3);
        
        auto result = cv::PSNR(*src1, *src2, R);
        value.setProperty(runtime, "psnr", jsi::Value(result));
      } break;
      case hashString("reduce", 6): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto dim = args.asNumber(3);
        auto rtype = args.asNumber(4);
        auto dtype = args.asNumber(5);
        
        cv::reduce(*src, *dst, dim, rtype, dtype);
      } break;
      case hashString("repeat", 6): {
        auto src = args.asMatPtr(1);
        auto ny = args.asNumber(2);
        auto nx = args.asNumber(3);
        auto dst = args.asMatPtr(4);
        
        cv::repeat(*src, ny, nx, *dst);
      } break;
      case hashString("resize", 6): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto dsize = args.asSizePtr(3);
        auto fx = args.asNumber(4);
        auto fy = args.asNumber(5);
        auto interpolation = args.asNumber(6);
        
        cv::resize(*src, *dst, *dsize, fx, fy, interpolation);
      } break;
      case hashString("rotate", 6): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto code = args.asNumber(3);
        
        cv::rotate(*src, *dst, code);
      } break;
      case hashString("scaleAdd", 8): {
        auto src1 = args.asMatPtr(1);
        auto alpha = args.asNumber(2);
        auto src2 = args.asMatPtr(3);
        auto dst = args.asMatPtr(4);
        
        cv::scaleAdd(*src1, alpha, *src2, *dst);
      } break;
      case hashString("solve", 5): {
        auto src1 = args.asMatPtr(1);
        auto src2 = args.asMatPtr(2);
        auto dst = args.asMatPtr(3);
        auto flags = args.asNumber(4);
        
        auto result = cv::solve(*src1, *src2, *dst, flags);
        value.setProperty(runtime, "resolved", jsi::Value(result));
      } break;
      case hashString("solveCubic", 10): {
        auto coeffs = args.asMatPtr(1);
        auto roots = args.asMatPtr(2);
        
        auto result = cv::solveCubic(*coeffs, *roots);
        value.setProperty(runtime, "value", jsi::Value(result));
      } break;
      case hashString("solvePoly", 9): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto maxIters = args.asNumber(3);
        
        auto result = cv::solvePoly(*src, *dst, maxIters);
        value.setProperty(runtime, "value", jsi::Value(result));
      } break;
      case hashString("sort", 4): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto flags = args.asNumber(3);
        
        cv::sort(*src, *dst, flags);
      } break;
      case hashString("sortIdx", 7): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto flags = args.asNumber(3);
        
        cv::sortIdx(*src, *dst, flags);
      } break;
      case hashString("split", 5): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatVectorPtr(2);
        
        cv::split(*src, *dst);
      } break;
      case hashString("sqrt", 4): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        
        cv::sqrt(*src, *dst);
      } break;
      case hashString("subtract", 8): {
        auto src1 = args.asMatPtr(1);
        auto src2 = args.asMatPtr(2);
        auto dst = args.asMatPtr(3);
        
        if (count > 4) {
          auto mask = args.asMatPtr(4);
          if (count > 5) {
            auto dtype = args.asNumber(5);

            cv::subtract(*src1, *src2, *dst, *mask, dtype);
            break;
          }
          cv::subtract(*src1, *src2, *dst, *mask);
          break;
        }
        cv::subtract(*src1, *src2, *dst);
      } break;
      case hashString("sum", 3): {
        std::string id;
        
        if (args.isMat(1)) {
          auto src = args.asMatPtr(1);
          auto scalar = cv::sum(*src);
          id = FOCV_Storage::save(scalar);
        } else {
          auto src = args.asMatVectorPtr(1);
          auto scalar = cv::sum(*src);
          id = FOCV_Storage::save(scalar);
        }
        
        return FOCV_JsiObject::wrap(runtime, "scalar", id);
      } break;
      case hashString("trace", 5): {
        auto src =  args.asMatPtr(1);
        
        auto scalar = cv::trace(*src);
        std::string id = FOCV_Storage::save(scalar);
        
        return FOCV_JsiObject::wrap(runtime, "scalar", id);
      } break;
      case hashString("transform", 9): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto m = args.asMatPtr(3);
        
        cv::transform(*src, *dst, *m);
      } break;
      case hashString("transpose", 9): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        
        cv::transpose(*src, *dst);
      } break;
      case hashString("vconcat", 7): {
        auto src = args.asMatVectorPtr(1);
        auto dst = args.asMatPtr(2);
        
        cv::vconcat(*src, *dst);
      } break;
      case hashString("cvtColor", 8): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto code = args.asNumber(3);
        
        if (count > 4) {
          auto dsnCn = args.asNumber(4);
          
          cv::cvtColor(*src, *dst, code, dsnCn);
          break;
        }
        cv::cvtColor(*src, *dst, code);
      } break;
      case hashString("cvtColorTwoPlane", 16): {
        auto src1 = args.asMatPtr(1);
        auto src2 = args.asMatPtr(2);
        auto dst = args.asMatPtr(3);
        auto code = args.asNumber(4);
        
        cv::cvtColorTwoPlane(*src1, *src2, *dst, code);
      } break;
      case hashString("demosaicing", 11): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto code = args.asNumber(3);
        
        if (count > 4) {
          auto dsnCn = args.asNumber(4);
          
          cv::demosaicing(*src, *dst, code, dsnCn);
          break;
        }
        cv::demosaicing(*src, *dst, code);
      } break;
      case hashString("applyColorMap", 13): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto colormap = args.asNumber(3);
        
        cv::applyColorMap(*src, *dst, colormap);
      } break;
      case hashString("arrowedLine", 11): {
        auto img = args.asMatPtr(1);
        auto point1 = args.asPointPtr(2);
        auto point2 = args.asPointPtr(3);
        auto color = args.asScalarPtr(4);
        auto thickness = args.asNumber(5);
        auto line_type = args.asNumber(6);
        
        cv::arrowedLine(*img, *point1, *point2, *color, thickness, line_type);
      } break;
      case hashString("circle", 6): {
        auto img = args.asMatPtr(1);
        auto center = args.asPointPtr(2);
        auto radius = args.asNumber(3);
        auto color = args.asScalarPtr(4);
        auto thickness = args.asNumber(5);
        auto line_type = args.asNumber(6);
        
        cv::circle(*img, *center, radius, *color, thickness, line_type);
      } break;
      case hashString("clipLine", 8): {
        auto size = args.asSizePtr(1);
        auto point1 = args.asPointPtr(2);
        auto point2 = args.asPointPtr(3);
        
        auto result = cv::clipLine(*size, *point1, *point2);
        value.setProperty(runtime, "value", jsi::Value(result));
      } break;
      case hashString("drawContours", 12): {
        auto img = args.asMatPtr(1);
        auto contours = args.asMatVectorPtr(2);
        auto contourIdx = args.asNumber(3);
        auto color = args.asScalarPtr(4);
        auto thickness = args.asNumber(5);
        auto line_type = args.asNumber(6);
        
        cv::drawContours(*img, *contours, contourIdx, *color, thickness, line_type);
      } break;
      case hashString("drawMarker", 10): {
        auto img = args.asMatPtr(1);
        auto position = args.asPointPtr(2);
        auto color = args.asScalarPtr(3);
        auto markerType = args.asNumber(4);
        auto markerSize = args.asNumber(5);
        auto thickness = args.asNumber(6);
        auto line_type = args.asNumber(7);
        
        cv::drawMarker(*img, *position, *color, markerType, markerSize, thickness, line_type);
      } break;
      case hashString("ellipse", 7): {
        auto img = args.asMatPtr(1);
        auto center = args.asPointPtr(2);
        auto axes = args.asSizePtr(3);
        auto angle = args.asNumber(4);
        auto startAngle = args.asNumber(5);
        auto endAngle = args.asNumber(6);
        auto color = args.asScalarPtr(7);
        auto thickness = args.asNumber(8);
        auto line_type = args.asNumber(9);
        
        cv::ellipse(*img, *center, *axes, angle, startAngle, endAngle, *color, thickness, line_type);
      } break;
      case hashString("fillConvexPoly", 14): {
        auto img = args.asMatPtr(1);
        auto pts = args.asMatVectorPtr(2);
        auto color = args.asScalarPtr(3);
        auto line_type = args.asNumber(4);
        
        cv::fillConvexPoly(*img, *pts, *color, line_type);
      } break;
      case hashString("fillPoly", 8): {
        auto img = args.asMatPtr(1);
        auto pts = args.asMatVectorPtr(2);
        auto color = args.asScalarPtr(3);
        auto line_type = args.asNumber(4);
        
        cv::fillPoly(*img, *pts, *color, line_type);
      } break;
      case hashString("line", 4): {
        auto img = args.asMatPtr(1);
        auto point1 = args.asPointPtr(2);
        auto point2 = args.asPointPtr(3);
        auto color = args.asScalarPtr(4);
        auto thickness = args.asNumber(5);
        auto line_type = args.asNumber(6);
        
        cv::line(*img, *point1, *point2, *color, thickness, line_type);
      } break;
      case hashString("polylines", 9): {
        auto img = args.asMatPtr(1);
        auto pts = args.asMatVectorPtr(2);
        auto isClosed = args.asBool(3);
        auto color = args.asScalarPtr(4);
        auto thickness = args.asNumber(5);
        auto line_type = args.asNumber(6);
        
        cv::polylines(*img, *pts, isClosed, *color, thickness, line_type);
      } break;
      case hashString("rectangle", 9): {
        auto img = args.asMatPtr(1);
        auto point1 = args.asPointPtr(2);
        auto point2 = args.asPointPtr(3);
        auto color = args.asScalarPtr(4);
        auto thickness = args.asNumber(5);
        auto line_type = args.asNumber(6);
        
        cv::rectangle(*img, *point1, *point2, *color, thickness, line_type);
      } break;
      case hashString("Canny", 5): {
        auto image = args.asMatPtr(1);
        auto edges = args.asMatPtr(2);
        auto threshold1 = args.asNumber(3);
        auto threshold2 = args.asNumber(4);
        
        cv::Canny(*image, *edges, threshold1, threshold2);
      } break;
      case hashString("cornerHarris", 12): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto blockSize = args.asNumber(3);
        auto ksize = args.asNumber(4);
        auto k = args.asNumber(5);
        
        cv::cornerHarris(*src, *dst, blockSize, ksize, k);
      } break;
      case hashString("cornerMinEigenVal", 17): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto blockSize = args.asNumber(3);
        
        cv::cornerMinEigenVal(*src, *dst, blockSize);
      } break;
      case hashString("goodFeaturesToTrack", 19): {
        auto image = args.asMatPtr(1);
        auto corners = args.asMatPtr(2);
        auto maxCorners = args.asNumber(3);
        auto qualityLevel = args.asNumber(4);
        auto minDistance = args.asNumber(5);
        
        cv::goodFeaturesToTrack(*image, *corners, maxCorners, qualityLevel, minDistance);
      } break;
      case hashString("HoughCircles", 12): {
        auto image = args.asMatPtr(1);
        auto circles = args.asMatPtr(2);
        auto method = args.asNumber(3);
        auto dp = args.asNumber(4);
        auto minDist = args.asNumber(5);
        
        if (count > 6) {
          auto param1 = args.asNumber(6);
          if (count > 7) {
            auto param2 = args.asNumber(7);

            cv::HoughCircles(*image, *circles, method, dp, minDist, param1, param2);
            break;
          }
          cv::HoughCircles(*image, *circles, method, dp, minDist, param1);
          break;
        }
        cv::HoughCircles(*image, *circles, method, dp, minDist);
      } break;
      case hashString("HoughLines", 10): {
        auto image = args.asMatPtr(1);
        auto lines = args.asMatPtr(2);
        auto rho = args.asNumber(3);
        auto theta = args.asNumber(4);
        auto threshold = args.asNumber(5);
        
        cv::HoughLines(*image, *lines, rho, theta, threshold);
      } break;
      case hashString("HoughLinesP", 11): {
        auto image = args.asMatPtr(1);
        auto lines = args.asMatPtr(2);
        auto rho = args.asNumber(3);
        auto theta = args.asNumber(4);
        auto threshold = args.asNumber(5);
        
        cv::HoughLinesP(*image, *lines, rho, theta, threshold);
      } break;
      case hashString("bilateralFilter", 15): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto d = args.asNumber(3);
        auto sigmaColor = args.asNumber(4);
        auto sigmaSpace = args.asNumber(5);
        auto borderType = args.asNumber(6);
        
        cv::bilateralFilter(*src, *dst, d, sigmaColor, sigmaSpace, borderType);
      } break;
      case hashString("blur", 4): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto ksize = args.asSizePtr(3);
        auto anchor = args.asPointPtr(4);
        auto borderType = args.asNumber(5);
        
        cv::blur(*src, *dst, *ksize, *anchor, borderType);
      } break;
      case hashString("boxFilter", 9): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto ddepth = args.asNumber(3);
        auto ksize = args.asSizePtr(4);
        auto anchor = args.asPointPtr(5);
        auto normalize = args.asBool(6);
        auto borderType = args.asNumber(7);
        
        cv::boxFilter(*src, *dst, ddepth, *ksize, *anchor, normalize, borderType);
      } break;
      case hashString("buildPyramid", 12): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto maxlevel = args.asNumber(3);
        auto borderType = args.asNumber(4);
        
        cv::buildPyramid(*src, *dst, maxlevel, borderType);
      } break;
      case hashString("dilate", 6): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto kernel = args.asMatPtr(3);
        auto anchor = args.asPointPtr(4);
        auto iterations = args.asNumber(5);
        auto borderType = args.asNumber(6);
        auto borderValue = args.asScalarPtr(7);
        
        cv::dilate(*src, *dst, *kernel, *anchor, iterations, borderType, *borderValue);
      } break;
      case hashString("erode", 5): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto kernel = args.asMatPtr(3);
        auto anchor = args.asPointPtr(4);
        auto iterations = args.asNumber(5);
        auto borderType = args.asNumber(6);
        auto borderValue = args.asScalarPtr(7);
        
        cv::erode(*src, *dst, *kernel, *anchor, iterations, borderType, *borderValue);
      } break;
      case hashString("filter2D", 8): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto ddepth = args.asNumber(3);
        auto kernel = args.asMatPtr(4);
        auto anchor = args.asPointPtr(5);
        auto delat = args.asNumber(6);
        auto borderType = args.asNumber(7);
        
        cv::filter2D(*src, *dst, ddepth, *kernel, *anchor, delat, borderType);
      } break;
      case hashString("GaussianBlur", 12): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto ksize = args.asSizePtr(3);
        auto sigmaX = args.asNumber(4);
        
        if (count > 5) {
          auto sigmaY = args.asNumber(5);
          if (count > 6) {
            auto borderType = args.asNumber(6);

            cv::GaussianBlur(*src, *dst, *ksize, sigmaX, sigmaY, borderType);
            break;
          }
          cv::GaussianBlur(*src, *dst, *ksize, sigmaX, sigmaY);
          break;
        }
        cv::GaussianBlur(*src, *dst, *ksize, sigmaX);
      } break;
      case hashString("getGaborKernel", 14): {
        auto ksize = args.asSizePtr(1);
        auto sigma = args.asNumber(2);
        auto theta = args.asNumber(3);
        auto lambd = args.asNumber(4);
        auto gamma = args.asNumber(5);
        auto psi = args.asNumber(6);
        auto ktype = args.asNumber(7);
        
        cv::Mat result = cv::getGaborKernel(*ksize, sigma, theta, lambd, gamma, psi, ktype);
        std::string id = FOCV_Storage::save(result);
        
        return FOCV_JsiObject::wrap(runtime, "mat", id);
      } break;
      case hashString("getGaussianKernel", 17): {
        auto ksize = args.asNumber(1);
        auto sigma = args.asNumber(2);
        auto ktype = args.asNumber(3);
        
        cv::Mat result = cv::getGaussianKernel(ksize, sigma, ktype);
        std::string id = FOCV_Storage::save(result);
        
        return FOCV_JsiObject::wrap(runtime, "mat", id);
      } break;
      case hashString("getPerspectiveTransform", 23): {
        auto src = args.asPoint2fVectorPtr(1);
        auto dest = args.asPoint2fVectorPtr(2);
        auto solveMethod = args.asNumber(3);

        cv::Mat result = cv::getPerspectiveTransform(*src, *dest, solveMethod);
        std::string id = FOCV_Storage::save(result);

        return FOCV_JsiObject::wrap(runtime, "mat", id);
      } break;
      case hashString("getStructuringElement", 21): {
        std::string id;
        auto shape = args.asNumber(1);
        auto ksize = args.asSizePtr(2);

        if (count > 3) {
          auto anchor = args.asPointPtr(3);

          cv::Mat result = cv::getStructuringElement(shape, *ksize, *anchor);
          id = FOCV_Storage::save(result);
        } else {
          cv::Mat result = cv::getStructuringElement(shape, *ksize);
          id = FOCV_Storage::save(result);
        }

        return FOCV_JsiObject::wrap(runtime, "mat", id);
      } break;
      case hashString("Laplacian", 9): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto ddepth = args.asNumber(3);
        auto ksize = args.asNumber(4);
        auto scale = args.asNumber(5);
        auto delta = args.asNumber(6);
        auto borderType = args.asNumber(7);
        
        cv::Laplacian(*src, *dst, ddepth, ksize, scale, delta, borderType);
      } break;
      case hashString("medianBlur", 10): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto ksize = args.asNumber(3);
        
        cv::medianBlur(*src, *dst, ksize);
      } break;
      case hashString("morphologyDefaultBorderValue", 28): {
        auto scalar = cv::morphologyDefaultBorderValue();
        std::string id = FOCV_Storage::save(scalar);

        return FOCV_JsiObject::wrap(runtime, "scalar", id);
      } break;
      case hashString("morphologyEx", 12): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto op = args.asNumber(3);
        auto kernel = args.asMatPtr(4);
        
        if (count > 5) {
          auto anchor = args.asPointPtr(5);
          if (count > 6) {
            auto iterations = args.asNumber(6);
            if (count > 7) {
              auto borderType = args.asNumber(7);
              if (count > 8) {
                auto borderValue = args.asScalarPtr(8);

                cv::morphologyEx(*src, *dst, op, *kernel, *anchor, iterations, borderType, *borderValue);
                break;
              }
              cv::morphologyEx(*src, *dst, op, *kernel, *anchor, iterations, borderType);
              break;
            }
            cv::morphologyEx(*src, *dst, op, *kernel, *anchor, iterations);
            break;
          }
          cv::morphologyEx(*src, *dst, op, *kernel, *anchor);
          break;
        }
        cv::morphologyEx(*src, *dst, op, *kernel);
      } break;
      case hashString("adaptiveThreshold", 17): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto maxValue = args.asNumber(3);
        auto adaptiveMethod = args.asNumber(4);
        auto thresholdType = args.asNumber(5);
        auto blockSize = args.asNumber(6);
        auto C = args.asNumber(7);
        
        cv::adaptiveThreshold(*src, *dst, maxValue, adaptiveMethod, thresholdType, blockSize, C);
      } break;
      case hashString("distanceTransform", 17): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto distanceType = args.asNumber(3);
        auto maskSize = args.asNumber(4);
        
        cv::distanceTransform(*src, *dst, distanceType, maskSize);
      } break;
      case hashString("integral", 8): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        
        cv::integral(*src, *dst);
      } break;
      case hashString("Sobel", 5): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto ddepth = args.asNumber(3);
        auto dx = args.asNumber(4);
        auto dy = args.asNumber(5);
        auto ksize = args.asNumber(6);
        auto scale = args.asNumber(7);
        auto delta = args.asNumber(8);
        auto borderType = args.asNumber(9);

        cv::Sobel(*src, *dst, ddepth, dx, dy, ksize, scale, delta, borderType);
      } break;
      case hashString("threshold", 9): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto thresh = args.asNumber(3);
        auto maxval = args.asNumber(4);
        auto type = args.asNumber(5);
        
        cv::threshold(*src, *dst, thresh, maxval, type);
      } break;
      case hashString("matchTemplate", 13): {
        auto image = args.asMatPtr(1);
        auto templ = args.asMatPtr(2);
        auto result = args.asMatPtr(3);
        auto method = args.asNumber(4);
        auto mask = args.asMatPtr(5);

        cv::matchTemplate(*image, *templ, *result, method, *mask);
      } break;
      case hashString("phaseCorrelate", 14): {
        std::string id;
        auto src1 = args.asMatPtr(1);
        auto src2 = args.asMatPtr(2);
        double response = 0;

        if (count > 3) {
          auto window = args.asMatPtr(3);

          cv::Point2f result = cv::phaseCorrelate(*src1, *src2, *window, &response);
          id = FOCV_Storage::save(result);
        } else {
          cv::Point2f result = cv::phaseCorrelate(*src1, *src2, cv::noArray(), &response);
          id = FOCV_Storage::save(result);
        }

        value.setProperty(runtime, "phaseShift", FOCV_JsiObject::wrap(runtime, "point2f", id));
        value.setProperty(runtime, "response", jsi::Value(response));
      } break;
      case hashString("approxPolyDP", 12): {
        auto epsilon = args.asNumber(3);
        auto closed = args.asBool(4);

        if (args.isMat(1)) {
            auto curve = args.asMatPtr(1);
            if (args.isMat(2)) {
                auto approxCurve = args.asMatPtr(2);
                cv::approxPolyDP(*curve, *approxCurve, epsilon, closed);
            } else {
                auto approxCurve = args.asPointVectorPtr(2);
                cv::approxPolyDP(*curve, *approxCurve, epsilon, closed);
            }
        } else if (args.isMatVector(1)) {
            auto curve = args.asMatVectorPtr(1);
            if (args.isMat(2)) {
                auto approxCurve = args.asMatPtr(2);
                cv::approxPolyDP(*curve, *approxCurve, epsilon, closed);
            } else {
                auto approxCurve = args.asPointVectorPtr(2);
                cv::approxPolyDP(*curve, *approxCurve, epsilon, closed);
            }
        } else {
            auto curve = args.asPointVectorPtr(1);
            if (args.isMat(2)) {
                auto approxCurve = args.asMatPtr(2);
                cv::approxPolyDP(*curve, *approxCurve, epsilon, closed);
            } else {
                auto approxCurve = args.asPointVectorPtr(2);
                cv::approxPolyDP(*curve, *approxCurve, epsilon, closed);
            }
        }
      } break;
      case hashString("arcLength", 9): {
        auto closed = args.asBool(2);
        
        if (args.isMat(1)) {
          auto curve = args.asMatPtr(1);
          auto result = cv::arcLength(*curve, closed);
          value.setProperty(runtime, "value", jsi::Value(result));
        } else if (args.isMatVector(1)) {
          auto curve = args.asMatVectorPtr(1);
          auto result = cv::arcLength(*curve, closed);
          value.setProperty(runtime, "value", jsi::Value(result));
        } else {
          auto curve = args.asPointVectorPtr(1);
          auto result = cv::arcLength(*curve, closed);
          value.setProperty(runtime, "value", jsi::Value(result));
        }
      } break;
      case hashString("boundingRect", 12): {
        cv::Rect rect;
        
        if (args.isMat(1)) {
          rect = cv::boundingRect(*args.asMatPtr(1));
        } else if (args.isMatVector(1)) {
          rect = cv::boundingRect(*args.asMatVectorPtr(1));
        } else {
          rect = cv::boundingRect(*args.asPointVectorPtr(1));
        }
        
        std::string id = FOCV_Storage::save(rect);
        
        return FOCV_JsiObject::wrap(runtime, "rect", id);
      } break;
      case hashString("connectedComponents", 19): {
        auto image = args.asMatPtr(1);
        auto labels = args.asMatPtr(2);
        
        auto result = cv::connectedComponents(*image, *labels);
        value.setProperty(runtime, "value", jsi::Value(result));
      } break;
      case hashString("connectedComponentsWithStats", 28): {
        auto image = args.asMatPtr(1);
        auto labels = args.asMatPtr(2);
        auto stats = args.asMatPtr(3);
        auto centroids = args.asMatPtr(4);
        
        auto result = cv::connectedComponentsWithStats(*image, *labels, *stats, *centroids);
        value.setProperty(runtime, "value", jsi::Value(result));
      } break;
      case hashString("contourArea", 11): {
        auto oriented = (count > 2) ? args.asBool(2) : false;
        
        if (args.isMat(1)) {
          auto src = args.asMatPtr(1);
          value.setProperty(runtime, "value", contourArea(*src, oriented));
        } else {
          auto src = args.asPointVectorPtr(1);
          value.setProperty(runtime, "value", contourArea(*src, oriented));
        }
      } break;
      case hashString("convexHull", 10): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        
        cv::convexHull(*src, *dst);
      } break;
      case hashString("convexityDefects", 16): {
        auto contour = args.asMatPtr(1);
        auto convexHull = args.asMatPtr(2);
        auto convexityDefects = args.asMatPtr(3);
        
        cv::convexityDefects(*contour, *convexHull, *convexityDefects);
      } break;
      case hashString("findContours", 12): {
        auto src = args.asMatPtr(1);
        auto mode = args.asNumber(3);
        auto method = args.asNumber(4);
        
        if (args.isMatVector(2)) {
          auto dst = args.asMatVectorPtr(2);
          cv::findContours(*src, *dst, mode, method);
        } else {
          auto dst = args.asPointVectorOfVectorsPtr(2);
          cv::findContours(*src, *dst, mode, method);
        }
      } break;
      case hashString("findContoursWithHierarchy", 25): {
        auto src = args.asMatPtr(1);
        auto hierarchy = args.asMatPtr(3);
        auto mode = args.asNumber(4);
        auto method = args.asNumber(5);
        
        if (args.isMatVector(2)) {
          auto dst = args.asMatVectorPtr(2);
          cv::findContours(*src, *dst, *hierarchy, mode, method);
        } else {
          auto dst = args.asPointVectorOfVectorsPtr(2);
          cv::findContours(*src, *dst, *hierarchy, mode, method);
        }
        
      } break;
      case hashString("fitLine", 7): {
        auto points = args.asMatPtr(1);
        auto line = args.asMatPtr(2);
        auto disType = args.asNumber(3);
        auto param = args.asNumber(4);
        auto reps = args.asNumber(5);
        auto aeps = args.asNumber(6);
        
        cv::fitLine(*points, *line, disType, param, reps, aeps);
      } break;
      case hashString("isContourConvex", 15): {
        auto contour = args.asMatPtr(1);
        
        value.setProperty(runtime, "value", jsi::Value(cv::isContourConvex(*contour)));
      } break;
      case hashString("matchShapes", 11): {
        auto contour1 = args.asMatPtr(1);
        auto contour2 = args.asMatPtr(2);
        auto method = args.asNumber(3);
        auto parameter = args.asNumber(4);
        
        auto result = cv::matchShapes(*contour1, *contour2, method, parameter);
        value.setProperty(runtime, "value", jsi::Value(result));
      } break;
      case hashString("minAreaRect", 11): {
        auto src = args.asMatPtr(1);
        
        auto rect = cv::minAreaRect(*src);
        
        auto id = FOCV_Storage::save(rect);
        return FOCV_JsiObject::wrap(runtime, "rotated_rect", id);
      } break;
      case hashString("convertTo", 9): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto rtype = args.asNumber(3);

        if (count > 4) {
          auto alpha = args.asNumber(4);
          if (count > 5) {
            auto beta = args.asNumber(5);

            (*src).convertTo(*dst, rtype, alpha, beta);
            break;
          }
          (*src).convertTo(*dst, rtype, alpha);
          break;
        }
        (*src).convertTo(*dst, rtype);
      } break;
      case hashString("warpAffine", 10): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto rotation = args.asMatPtr(3);
        auto size = args.asSizePtr(4);
        
        cv::warpAffine(*src, *dst, *rotation, *size);
      } break;
      case hashString("warpPerspective", 15): {
        auto src = args.asMatPtr(1);
        auto dst = args.asMatPtr(2);
        auto M = args.asMatPtr(3);
        auto size = args.asSizePtr(4);
        auto flags = args.asNumber(5);
        auto borderMode = args.asNumber(6);
        auto borderValue = args.asScalarPtr(7);

        cv::warpPerspective(*src, *dst, *M, *size, flags, borderMode, *borderValue);
      } break;
    }
  } catch (cv::Exception& e) {
    std::string message(e.what());
    std::cout << "Fast OpenCV Invoke Error: " << message << "\n";
    throw std::runtime_error("Fast OpenCV Error: " + message);
  }
    
  return value;
}
