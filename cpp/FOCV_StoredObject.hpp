//
//  FOCV_StoredObject.hpp
//
//  Created by Łukasz Kurant on 04/08/2024.
//

#ifndef FOCV_StoredObject_hpp
#define FOCV_StoredObject_hpp

#include <stdio.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#ifdef __cplusplus
    #include <opencv2/opencv.hpp>
#endif

template<typename T>
class FOCV_StoredObject {
private:
    std::unordered_map<std::string, T> _items;
    
public:
    FOCV_StoredObject();
    ~FOCV_StoredObject();
    
    void clear();
    
    std::string save(T &item);
    std::string save(std::string &key, T &item);
    
    T get(std::string key);
};


template <typename T>
FOCV_StoredObject<T>::FOCV_StoredObject() {
    _items = std::unordered_map<std::string, T>();
}

template <typename T>
FOCV_StoredObject<T>::~FOCV_StoredObject() {
    clear();
}


template <typename T>
void FOCV_StoredObject<T>::clear() {
    _items.clear();
}

template <typename T>
std::string FOCV_StoredObject<T>::save(T &item) {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string tmp = boost::uuids::to_string(uuid);
    
    _items.insert_or_assign(tmp, item);
    
    return tmp;
}

template <typename T>
std::string FOCV_StoredObject<T>::save(std::string &name, T &item) {
    _items.insert_or_assign(name, item);
    
    return name;
}


template <typename T>
T FOCV_StoredObject<T>::get(std::string id) {
    if(!_items.contains(id)) {
//        Error here!
    }
    
    return _items.at(id);
}


#endif /* FOCV_StoredObject_hpp */
