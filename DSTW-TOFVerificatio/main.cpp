#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

// 定义信号源结构体，包含信号源的位置
struct SignalSource {
    double x;
    double y;
};

// 定义接收器结构体，包含接收器的位置
struct Receiver {
    double x;
    double y;
};

// 生成指定范围内的随机浮点数
double generateRandomDouble(double min, double max) {
    return min + static_cast<double>(rand()) / (RAND_MAX / (max - min));
}

// 计算两点之间的距离
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// 模拟信号传播和测量，考虑误差模型
double simulateDS_TW_TOF(const SignalSource& source, const Receiver& receiver, double distanceError) {
    // 模拟信号在往返过程中的传播时间
    double speedOfLight = 299792458.0; // 光速（米/秒）
    double distanceToSource = distance(source.x, source.y, receiver.x, receiver.y);

    // 添加距离误差模型，考虑了距离的非线性误差
    double trueDistance = 2.0 * distanceToSource;
    double measurementError = generateRandomDouble(-distanceError, distanceError);
    double measuredDistance = trueDistance + measurementError;

    double timeOfFlight = (measuredDistance) / speedOfLight;

    return timeOfFlight;
}

// DS-TW-TOF定位算法，考虑多个接收器
SignalSource dsTwTofLocalization(const std::vector<Receiver>& receivers, double distanceError) {
    SignalSource source = {0.0, 0.0};

    // 初始化估计位置
    double estimatedX = 0.0;
    double estimatedY = 0.0;

    // 遍历每对接收器
    for (size_t i = 0; i < receivers.size(); ++i) {
        for (size_t j = i + 1; j < receivers.size(); ++j) {
            const Receiver& receiver1 = receivers[i];
            const Receiver& receiver2 = receivers[j];

            // 模拟测量两次时间差，考虑距离误差
            double timeDifference1 = simulateDS_TW_TOF(source, receiver1, distanceError);
            double timeDifference2 = simulateDS_TW_TOF(source, receiver2, distanceError);

            // 根据时间差估算距离
            double distance1 = (timeDifference1 * 299792458.0) / 2.0;
            double distance2 = (timeDifference2 * 299792458.0) / 2.0;

            // 使用加权平均估算位置
            double weight1 = 1.0 / (distance1 * distance1); // 权重与距离的倒数成正比
            double weight2 = 1.0 / (distance2 * distance2);

            estimatedX += (receiver1.x * weight1 + receiver2.x * weight2) / (weight1 + weight2);
            estimatedY += (receiver1.y * weight1 + receiver2.y * weight2) / (weight1 + weight2);
        }
    }

    source.x = estimatedX;
    source.y = estimatedY;

    return source;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // 初始化随机数生成器

    // 创建四个接收器，包括位置
    std::vector<Receiver> receivers = {
            {1.0, 0.0},
            {0.0, 1.0},
            {-1.0, 0.0},
            {0.0, -1.0}
    };

    double distanceError = 0.01; // 距离误差模型的标准差

    // 使用DS-TW-TOF定位算法估算信号源位置
    SignalSource estimatedSource = dsTwTofLocalization(receivers, distanceError);

    std::cout << "Estimated Source Location: (" << estimatedSource.x << ", " << estimatedSource.y << ")\n";

    return 0;
}
