#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

// 定义信号源结构体，包含信号源的位置
struct SignalSource {
    double x;
    double y;
};

// 定义接收器结构体，包含接收器的位置和相对到达时间差
struct Receiver {
    double x;
    double y;
    double timeDifference;
};

// 生成指定范围内的随机浮点数（用于模拟噪声）
double generateRandomDouble(double min, double max) {
    return min + static_cast<double>(rand()) / (RAND_MAX / (max - min));
}

// 计算两点之间的距离
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// 添加噪声和误差到时间差数据
void addNoiseAndError(std::vector<Receiver>& receivers) {
    const double noiseRange = 0.01; // 噪声范围
    const double errorRange = 0.02; // 误差范围

    for (Receiver& receiver : receivers) {
        receiver.timeDifference += generateRandomDouble(-noiseRange, noiseRange);
        receiver.x += generateRandomDouble(-errorRange, errorRange);
        receiver.y += generateRandomDouble(-errorRange, errorRange);
    }
}

// PDOA定位算法
SignalSource pdoaLocalization(const std::vector<Receiver>& receivers) {
    SignalSource source = {0.0, 0.0};

    // 初始化估计位置
    double estimatedX = 0.0;
    double estimatedY = 0.0;

    // 权重之和
    double totalWeight = 0.0;

    // 遍历每对接收器
    for (size_t i = 0; i < receivers.size(); ++i) {
        for (size_t j = i + 1; j < receivers.size(); ++j) {
            const Receiver& receiver1 = receivers[i];
            const Receiver& receiver2 = receivers[j];

            // 计算两个接收器之间的距离
            double d = distance(receiver1.x, receiver1.y, receiver2.x, receiver2.y);

            // 计算两个接收器之间的传播速度差异
            double speedOfSound = 343.0; // 声速（米/秒）
            double deltaT = receiver1.timeDifference - receiver2.timeDifference;

            // 使用权重来计算估计位置
            double weight = 1.0 / (d * d); // 权重与距离的倒数成正比
            totalWeight += weight;

            estimatedX += (receiver1.x + receiver2.x) / 2 + (receiver1.x - receiver2.x) * deltaT * speedOfSound / (2 * d) * weight;
            estimatedY += (receiver1.y + receiver2.y) / 2 + (receiver1.y - receiver2.y) * deltaT * speedOfSound / (2 * d) * weight;
        }
    }

    source.x = estimatedX / totalWeight;
    source.y = estimatedY / totalWeight;

    return source;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // 初始化随机数生成器

    // 创建三个接收器，包括位置和相对到达时间差
    std::vector<Receiver> receivers = {
        {1.0, 0.0, 0.01},
        {0.0, 1.0, 0.02},
        {-1.0, 0.0, 0.03}
    };

    // 添加噪声和误差到时间差数据
    addNoiseAndError(receivers);

    // 使用PDOA定位算法估算信号源位置
    SignalSource estimatedSource = pdoaLocalization(receivers);

    std::cout << "Estimated Source Location: (" << estimatedSource.x << ", " << estimatedSource.y << ")\n";

    return 0;
}
