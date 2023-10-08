#include <iostream>
#include <vector>
#include <cmath>
#include <random> // 用于生成高斯噪声

struct Receiver {
    double x;
    double y;
    double angle;
};

struct Source {
    double x;
    double y;
};

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

Source aoaLocalization(const std::vector<Receiver>& receivers) {
    Source source = {0.0, 0.0};
    const int numSources = 2; // 假设有两个发射源
    const double learningRate = 0.01;
    const int maxIterations = 1000;
    const double convergenceThreshold = 0.001; // 收敛阈值

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::normal_distribution<double> noise(0.0, 0.1); // 均值0，标准差0.1的高斯噪声

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        double maxGradient = 0.0;

        // 更新每个发射源的位置
        for (int i = 0; i < numSources; ++i) {
            double gradientX = 0.0;
            double gradientY = 0.0;

            for (const Receiver& receiver : receivers) {
                double d = distance(source.x, source.y, receiver.x, receiver.y);
                double error = receiver.angle - atan2(receiver.y - source.y, receiver.x - source.x) + noise(generator); // 添加噪声

                double dx = (source.x - receiver.x) / d;
                double dy = (source.y - receiver.y) / d;

                gradientX += error * dx;
                gradientY += error * dy;

                // 计算最大梯度值
                double gradMag = sqrt(gradientX * gradientX + gradientY * gradientY);
                if (gradMag > maxGradient) {
                    maxGradient = gradMag;
                }
            }

            source.x -= learningRate * gradientX;
            source.y -= learningRate * gradientY;
        }

        // 收敛条件
        if (maxGradient < convergenceThreshold) {
            break;
        }
    }

    return source;
}

int main() {
    std::vector<Receiver> receivers = {
            {1.0, 0.0, 30.0 * M_PI / 180.0},
            {0.0, 1.0, 45.0 * M_PI / 180.0},
            {-1.0, 0.0, 60.0 * M_PI / 180.0}
    };

    Source estimatedSource = aoaLocalization(receivers);

    std::cout << "Estimated Source Location: (" << estimatedSource.x << ", " << estimatedSource.y << ")\n";

    return 0;
}
