#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

// 定义节点结构体，包含节点的位置
struct Node {
    double x;
    double y;
};

// 生成指定范围内的随机浮点数（用于模拟噪声）
double generateRandomDouble(double min, double max) {
    return min + static_cast<double>(rand()) / (RAND_MAX / (max - min));
}

// 计算两点之间的距离
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// 模拟往返时间测量，包括噪声和误差
double simulateRoundTripTimeMeasurement(const Node& node, double speedOfLight, double noiseStdDev, double measurementErrorStdDev) {
    // 假设目标设备在(0, 0)位置
    double targetX = 0.0;
    double targetY = 0.0;

    // 计算距离
    double d = distance(node.x, node.y, targetX, targetY);

    // 计算传播时间（不包括噪声和误差）
    double propagationTime = d / speedOfLight;

    // 模拟噪声，假设噪声符合正态分布
    double noise = generateRandomDouble(-noiseStdDev, noiseStdDev);

    // 模拟测量误差，假设误差符合正态分布
    double error = generateRandomDouble(-measurementErrorStdDev, measurementErrorStdDev);

    // 添加噪声和误差到传播时间
    return propagationTime + noise + error;
}

// SSTW-TOF定位算法
Node sstwTofLocalization(const std::vector<Node>& nodes, double speedOfLight, double noiseStdDev, double measurementErrorStdDev) {
    Node target = {0.0, 0.0};

    // 初始化估计位置
    double estimatedX = 0.0;
    double estimatedY = 0.0;

    // 权重之和
    double totalWeight = 0.0;

    // 遍历每对节点
    for (size_t i = 0; i < nodes.size(); ++i) {
        for (size_t j = i + 1; j < nodes.size(); ++j) {
            const Node& node1 = nodes[i];
            const Node& node2 = nodes[j];

            // 计算节点1到目标的往返时间
            double roundTripTime1 = simulateRoundTripTimeMeasurement(node1, speedOfLight, noiseStdDev, measurementErrorStdDev);

            // 计算节点2到目标的往返时间
            double roundTripTime2 = simulateRoundTripTimeMeasurement(node2, speedOfLight, noiseStdDev, measurementErrorStdDev);

            // 计算时间差
            double timeDifference = roundTripTime1 - roundTripTime2;

            // 根据时间差和传播速度估算目标位置
            double weight = 1.0 / (timeDifference * timeDifference); // 权重与时间差的倒数成正比
            totalWeight += weight;

            estimatedX += (timeDifference * speedOfLight * (node1.x - node2.x)) / 2 * weight;
            estimatedY += (timeDifference * speedOfLight * (node1.y - node2.y)) / 2 * weight;
        }
    }

    target.x = estimatedX / totalWeight;
    target.y = estimatedY / totalWeight;

    return target;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // 初始化随机数生成器

    // 创建多个节点，包括位置
    std::vector<Node> nodes = {
            {1.0, 0.0},
            {0.0, 1.0},
            {-1.0, 0.0},
            {0.0, -1.0}
    };

    // 声速（光速）为约299,792,458米/秒
    double speedOfLight = 299792458.0;

    // 噪声和测量误差的标准差（用于模拟噪声和误差）
    double noiseStdDev = 1e-10;
    double measurementErrorStdDev = 1e-10;

    // 使用SSTW-TOF定位算法估算目标位置
    Node estimatedTarget = sstwTofLocalization(nodes, speedOfLight, noiseStdDev, measurementErrorStdDev);

    std::cout << "Estimated Target Location: (" << estimatedTarget.x << ", " << estimatedTarget.y << ")\n";

    return 0;
}
