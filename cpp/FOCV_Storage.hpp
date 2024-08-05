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
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#ifdef __cplusplus
    #include <opencv2/opencv.hpp>
#endif

class FOCV_Storage {
public:
private:
    static std::unordered_map<std::string, std::any> items;
    
public:
    template <typename T>
    static T get(std::string key);
    
    template <typename T>
    static std::string save(T &item);
    
    template <typename T>
    static std::string save(std::string key, T &item);
    
    static void clear();
};

std::unordered_map<std::string, std::any> FOCV_Storage::items = std::unordered_map<std::string, std::any>();

void FOCV_Storage::clear() {
    items.clear();
}

template <typename T>
std::string FOCV_Storage::save(T &item) {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string key = boost::uuids::to_string(uuid);
    
    items.insert_or_assign(key, item);
    
    return key;
}

template <typename T>
std::string FOCV_Storage::save(std::string key, T &item) {
    items.insert_or_assign(key, item);
    
    return key;
}

template <typename T>
T FOCV_Storage::get(std::string key) {
    if(!items.contains(key)) {
//        Error here!
    }
    
    return std::any_cast<T>(items.at(key));
}


#endif /* FOCV_Storage_hpp */
