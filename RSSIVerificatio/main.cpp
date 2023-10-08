#include <iostream>
#include <vector>
#include <cmath>

struct SignalSource {
    double x;
    double y;
    double rssi;
};

struct Device {
    double x;
    double y;
};

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// 计算权重，考虑距离和信号强度
double calculateWeight(double measuredRssi, double estimatedRssi, double distance) {
    double alpha = 2.0; // 距离和信号强度之间的关系参数
    double beta = 10.0; // 误差项的权重参数

    // 使用带有权重的距离来计算权重
    double weight = exp(-(measuredRssi - estimatedRssi) / alpha) / (beta * distance);
    return weight;
}

// RSSI定位算法
Device rssiLocalization(const std::vector<SignalSource>& sources) {
    // 初始化设备位置为原点
    Device device = {0.0, 0.0};

    // 迭代次数
    const int maxIterations = 10;

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        double totalWeight = 0.0;
        double weightedX = 0.0;
        double weightedY = 0.0;

        for (const SignalSource& source : sources) {
            double d = distance(device.x, device.y, source.x, source.y);
            double estimatedRssi = -2.0 * log(d) - 30.0; // 估计信号强度，考虑距离和路径损耗

            // 计算权重
            double weight = calculateWeight(source.rssi, estimatedRssi, d);

            // 更新加权均值
            totalWeight += weight;
            weightedX += weight * source.x;
            weightedY += weight * source.y;
        }

        // 更新设备位置
        device.x = weightedX / totalWeight;
        device.y = weightedY / totalWeight;
    }

    return device;
}

int main() {
    std::vector<SignalSource> sources = {
            {1.0, 0.0, -50.0},
            {0.0, 1.0, -55.0},
            {-1.0, 0.0, -60.0}
    };

    Device estimatedDevice = rssiLocalization(sources);

    std::cout << "Estimated Device Location: (" << estimatedDevice.x << ", " << estimatedDevice.y << ")\n";

    return 0;
}
