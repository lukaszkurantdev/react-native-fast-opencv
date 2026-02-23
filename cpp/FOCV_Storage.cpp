//
//  FOCV_Storage.cpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 05/08/2024.
//

#include "FOCV_Storage.hpp"
#include <set>

std::unordered_map<std::string, std::any> FOCV_Storage::items = std::unordered_map<std::string, std::any>();

void FOCV_Storage::clear(const std::set<std::string> &ids_to_keep) {
  for (auto it = items.begin(); it != items.end();) {
    auto id = it->first;
    if (ids_to_keep.find(id) != ids_to_keep.end()) {
      it++;
    } else {
      it = items.erase(it);
    }
  }
}

void FOCV_Storage::release(const std::set<std::string>& ids_to_release) {
  for (const auto& id : ids_to_release) {
    auto it = items.find(id);
    if (it != items.end()) {
      items.erase(it);
    }
  }
}
