#include <iostream>
#include <cmath>

const double EARTH_RADIUS = 6371.0; // 地球半径（单位：公里）

struct GeoPoint {
    double latitude;  // 纬度（单位：度）
    double longitude; // 经度（单位：度）
    double altitude;  // 高度（单位：米）
};

// 将角度转换为弧度
double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// 校验经纬度是否在有效范围内
bool isValidLatitude(double latitude) {
    return (latitude >= -90.0 && latitude <= 90.0);
}

bool isValidLongitude(double longitude) {
    return (longitude >= -180.0 && longitude <= 180.0);
}

// 计算两个点之间的距离（单位：公里）
double calculateDistance(const GeoPoint& point1, const GeoPoint& point2) {
    double lat1 = degreesToRadians(point1.latitude);
    double lon1 = degreesToRadians(point1.longitude);
    double lat2 = degreesToRadians(point2.latitude);
    double lon2 = degreesToRadians(point2.longitude);

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1) * cos(lat2) *
               sin(dLon / 2) * sin(dLon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS * c;
}

// 计算方位角、俯仰角和距离
bool  calculateAzimuthElevationDistance(const GeoPoint& observer, const GeoPoint& target, double& azimuth, double& elevation, double& distance) {
    double lat1 = degreesToRadians(observer.latitude);
    double lon1 = degreesToRadians(observer.longitude);
    double lat2 = degreesToRadians(target.latitude);
    double lon2 = degreesToRadians(target.longitude);
    if (!isValidLatitude(observer.latitude) || !isValidLongitude(observer.longitude) ||
        !isValidLatitude(target.latitude) || !isValidLongitude(target.longitude)) {
        return false; // 返回false表示输入的经纬度不在有效范围内
    }
    double dLon = lon2 - lon1;

    azimuth = atan2(sin(dLon), cos(lat1) * tan(lat2) - sin(lat1) * cos(dLon));
    azimuth = fmod(azimuth + 2 * M_PI, 2 * M_PI); // 调整方位角为0到360度范围

    double dAltitude = target.altitude - observer.altitude;
    distance = calculateDistance(observer, target);
    elevation = atan2(dAltitude, distance);
    elevation = degreesToRadians(elevation); // 将俯仰角从弧度转换为度
    return true; // 返回true表示计算成功
}

int main() {
    GeoPoint observer;
    GeoPoint target;
    double azimuth, elevation, distance;

    // 输入观测点和被观测点的经纬高信息
    std::cout << "观测点信息：" << std::endl;
    std::cout << "纬度（度）：";
    std::cin >> observer.latitude;
    std::cout << "经度（度）：";
    std::cin >> observer.longitude;
    std::cout << "高度（米）：";
    std::cin >> observer.altitude;

    std::cout << "被观测点信息：" << std::endl;
    std::cout << "纬度（度）：";
    std::cin >> target.latitude;
    std::cout << "经度（度）：";
    std::cin >> target.longitude;
    std::cout << "高度（米）：";
    std::cin >> target.altitude;

    // 计算方位角、俯仰角和距离
    if (!calculateAzimuthElevationDistance(observer, target, azimuth, elevation, distance)) {
        std::cout << "输入的经纬度不在有效范围内" << std::endl;
        return 1;
    }
    // 输出结果
    std::cout << "方位角（度）：" << azimuth << std::endl;
    std::cout << "俯仰角（度）：" << elevation << std::endl;
    std::cout << "距离（公里）：" << distance << std::endl;

    return 0;
}