#include <iostream>
#include <cmath>

// 常量定义
const double pi = 3.14159265358979323846;
const double radiusEarth = 6371000.0; // 地球半径，单位：米

// 度转弧度
double degToRad(double degrees) {
    return degrees * pi / 180.0;
}

// 弧度转度
double radToDeg(double radians) {
    return radians * 180.0 / pi;
}

// 通过经纬度和高度计算ECEF坐标
void geodeticToECEF(double lat, double lon, double h, double& x, double& y, double& z) {
    double latRad = degToRad(lat);
    double lonRad = degToRad(lon);

    // 计算ECEF坐标
    x = (radiusEarth + h) * cos(latRad) * cos(lonRad);
    y = (radiusEarth + h) * cos(latRad) * sin(lonRad);
    z = (radiusEarth + h) * sin(latRad);
}

// 计算方位角和俯仰角
void calculateAzimuthElevation(double observerLat, double observerLon, double observerHeight,
                               double satelliteLon, double satelliteLat, double satelliteHeight,
                               double& azimuth, double& elevation) {
    // 计算观测点和卫星的ECEF坐标
    double observerX, observerY, observerZ, satelliteX, satelliteY, satelliteZ;
    geodeticToECEF(observerLat, observerLon, observerHeight, observerX, observerY, observerZ);
    geodeticToECEF(satelliteLat, satelliteLon, satelliteHeight, satelliteX, satelliteY, satelliteZ);

    // 计算观测点到卫星的相对ECEF向量
    double dx = satelliteX - observerX;
    double dy = satelliteY - observerY;
    double dz = satelliteZ - observerZ;

    // 计算方位角和俯仰角
    azimuth = atan2(dy, dx);
    double distance = sqrt(dx * dx + dy * dy + dz * dz);
    elevation = asin(dz / distance);

    // 转换为度
    azimuth = radToDeg(azimuth);
    if (azimuth < 0) {
        azimuth += 360; // 将负值转换成0-360度
    }
    elevation = radToDeg(elevation);
}

int main() {
    double observerLat, observerLon, observerHeight;
    double satelliteLat, satelliteLon, satelliteHeight;

    // 从键盘接收参数
    std::cout << "Enter observer's latitude (degrees): ";
    std::cin >> observerLat;
    std::cout << "Enter observer's longitude (degrees): ";
    std::cin >> observerLon;
    std::cout << "Enter observer's height (meters): ";
    std::cin >> observerHeight;

    std::cout << "Enter satellite's longitude (degrees): ";
    std::cin >> satelliteLon;
    std::cout << "Enter satellite's latitude (degrees): ";
    std::cin >> satelliteLat;
    std::cout << "Enter satellite's height (meters above Earth's surface): ";
    std::cin >> satelliteHeight;

    double azimuth, elevation;
    calculateAzimuthElevation(observerLat, observerLon, observerHeight,
                              satelliteLon, satelliteLat, satelliteHeight,
                              azimuth, elevation);

    std::cout << "Azimuth: " << azimuth << " degrees" << std::endl;
    std::cout << "Elevation: " << elevation << " degrees" << std::endl;

    return 0;
}
