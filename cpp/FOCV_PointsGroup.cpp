//
//  FOCV_PointsGroup.cpp
//  react-native-fast-opencv
//
//  Created by Łukasz Kurant on 04/08/2024.
//

#include "FOCV_PointsGroup.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <opencv2/opencv.hpp>

std::unordered_map<std::string, std::vector<cv::Point>> FOCV_PointsGroup::_groups = std::unordered_map<std::string, std::vector<cv::Point>>();

void FOCV_PointsGroup::clear() {
    _groups.clear();
}

std::string FOCV_PointsGroup::saveGroup(std::vector<cv::Point> group) {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string tmp = boost::uuids::to_string(uuid);
    
    _groups.insert_or_assign(tmp, group);
    
    return tmp;
}

std::string FOCV_PointsGroup::saveGroup(std::string name, std::vector<cv::Point> group) {
    _groups.insert_or_assign(name, group);
    
    return name;
}

std::vector<cv::Point> FOCV_PointsGroup::getGroup(std::string id) {
    // Validation
    return _groups.at(id);
}
