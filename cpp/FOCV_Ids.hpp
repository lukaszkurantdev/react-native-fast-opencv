//
//  FOCV_Ids.hpp
//
//  Created by Łukasz Kurant on 04/08/2024.
//

#ifndef FOCV_Ids_hpp
#define FOCV_Ids_hpp

#include <stdio.h>
#include <jsi/jsilib.h>
#include <jsi/jsi.h>

class FOCV_Ids {
private:
    std::vector<std::string> ids;
    
public:
    void push(std::string id);
    facebook::jsi::Array toJsiArray(facebook::jsi::Runtime& runtime, std::string type);
};

#endif /* FOCV_Ids_hpp */
