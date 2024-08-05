//
//  FOCV_Mat.cpp
//
//  Created by Łukasz Kurant on 03/08/2024.
//

#include "FOCV_Mat.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <opencv2/opencv.hpp>

std::unordered_map<std::string, cv::Mat> FOCV_Mat::_matrices = std::unordered_map<std::string, cv::Mat>();

void FOCV_Mat::clear() {
    FOCV_Mat::_matrices.clear();
}

std::string FOCV_Mat::saveMat(cv::Mat mat) {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string tmp = boost::uuids::to_string(uuid);
    
    FOCV_Mat::_matrices.insert_or_assign(tmp, mat);
    
    return tmp;
}

std::string FOCV_Mat::saveMat(std::string name, cv::Mat mat) {
    FOCV_Mat::_matrices.insert_or_assign(name, mat);
    
    return name;
}

std::string FOCV_Mat::createMat() {
    cv::Mat mat;
    return saveMat(mat);
}

std::string FOCV_Mat::createMat(std::string name) {
    cv::Mat mat;
    return saveMat(name, mat);
}

std::string FOCV_Mat::createMat(int rows, int cols, uint8_t* buffer) {
    cv::Mat mat(rows, cols, CV_8UC3, buffer);
    return saveMat(mat);
}

cv::Mat FOCV_Mat::getMat(std::string id) {
    // Validation
    return FOCV_Mat::_matrices.at(id);
}
