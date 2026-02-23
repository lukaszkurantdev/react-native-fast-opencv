//
//  FOCV_Storage.hpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 05/08/2024.
//

#ifndef FOCV_Storage_hpp
#define FOCV_Storage_hpp

#include <stdio.h>
#include <any>
#include <set>
#include "UUID.hpp"

#ifdef __cplusplus
    #include <opencv2/opencv.hpp>
#endif

class FOCV_Storage {
public:
private:
    static std::unordered_map<std::string, std::any> items;

public:
    template <typename T>
    static std::shared_ptr<T> get(std::string key);

    template <typename T>
    static std::string save(T &item);

    template <typename T>
    static std::string save(std::string key, T &item);

    static void clear(const std::set<std::string> &ids_to_keep);
    static void release(const std::set<std::string> &ids_to_release);
};

template <typename T>
std::string FOCV_Storage::save(T &item) {
    std::string key = uuid::generate_uuid_v4();

    items.insert_or_assign(key, std::make_shared<T>(item));

    return key;
}

template <typename T>
std::string FOCV_Storage::save(std::string key, T &item) {
    items.insert_or_assign(key, std::make_shared<T>(item));

    return key;
}

template <typename T>
std::shared_ptr<T> FOCV_Storage::get(std::string key) {
    if (!items.contains(key)) {
        throw std::runtime_error("Fast OpenCV Error: Object with id '" + key + "' not found in storage!");
    }

    return std::any_cast<std::shared_ptr<T>>(items.at(key));
}


#endif /* FOCV_Storage_hpp */
