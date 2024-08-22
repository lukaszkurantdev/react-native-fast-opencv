//
//  FOCV_Storage.cpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 05/08/2024.
//

#include "FOCV_Storage.hpp"

std::unordered_map<std::string, std::any> FOCV_Storage::items = std::unordered_map<std::string, std::any>();

void FOCV_Storage::clear() {
  items.clear();
}