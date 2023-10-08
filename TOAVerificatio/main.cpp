#include <iostream>
#include <cmath>

// 表示Wi-Fi访问点的结构体
struct AccessPoint {
    double x;  // x坐标
    double y;  // y坐标
    int rssi;  // 接收信号强度
};

// 计算两个点之间的距离
double calculateDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

// 估算设备的位置
void estimateLocation(AccessPoint ap1, AccessPoint ap2, AccessPoint ap3) {
    // 计算三个AP之间的距离
    double d1 = calculateDistance(ap1.x, ap1.y, ap2.x, ap2.y);
    double d2 = calculateDistance(ap2.x, ap2.y, ap3.x, ap3.y);
    double d3 = calculateDistance(ap3.x, ap3.y, ap1.x, ap1.y);

    // 使用三边定位法计算设备位置
    double x = (d1 * ap1.x + d2 * ap2.x + d3 * ap3.x) / (d1 + d2 + d3);
    double y = (d1 * ap1.y + d2 * ap2.y + d3 * ap3.y) / (d1 + d2 + d3);

    std::cout << "估计的设备位置：(" << x << ", " << y << ")" << std::endl;
}

int main() {
    // 模拟三个Wi-Fi访问点
    AccessPoint ap1 = {0.0, 0.0, -50};  // (0, 0)处的信号强度为-50 dBm
    AccessPoint ap2 = {10.0, 0.0, -60};  // (10, 0)处的信号强度为-60 dBm
    AccessPoint ap3 = {0.0, 10.0, -70};  // (0, 10)处的信号强度为-70 dBm

    // 估算设备位置
    estimateLocation(ap1, ap2, ap3);

    return 0;
}
