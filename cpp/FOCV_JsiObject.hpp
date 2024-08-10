//
//  FOCV_JsiObject.hpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 10/08/2024.
//

#ifndef FOCV_JsiObject_hpp
#define FOCV_JsiObject_hpp

#include <stdio.h>
#include <jsi/jsilib.h>
#include <jsi/jsi.h>

using namespace facebook;

class FOCV_JsiObject {
public:
    static jsi::Object wrap(jsi::Runtime& runtime, std::string type, std::string id);
    static std::string id_from_wrap(jsi::Runtime& runtime, const jsi::Value& wrap);
    static std::string type_from_wrap(jsi::Runtime& runtime, const jsi::Value& wrap);
};

#endif /* FOCV_JsiObject_hpp */
