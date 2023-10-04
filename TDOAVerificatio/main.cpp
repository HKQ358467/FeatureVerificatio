#include <iostream>
#include <vector>
#include <cmath>
#include <random> // 用于生成高斯噪声

struct Receiver {
    double x;
    double y;
    double time;
};

struct Source {
    double x;
    double y;
};

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

Source tdoaLocalization(const std::vector<Receiver>& receivers) {
    Source source = {0.0, 0.0};
    const double learningRate = 0.01;
    const int maxIterations = 1000;
    const double convergenceThreshold = 0.001; // 收敛阈值

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::normal_distribution<double> noise(0.0, 0.1); // 均值0，标准差0.1的高斯噪声

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        double gradientX = 0.0;
        double gradientY = 0.0;
        double maxGradient = 0.0;

        for (const Receiver& receiver : receivers) {
            double d = distance(source.x, source.y, receiver.x, receiver.y);
            double error = receiver.time - d + noise(generator); // 添加噪声

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

        // 收敛条件
        if (maxGradient < convergenceThreshold) {
            break;
        }
    }

    return source;
}

int main() {
    std::vector<Receiver> receivers = {
            {1.0, 0.0, 1.0},
            {0.0, 1.0, 2.0},
            {-1.0, 0.0, 3.0}
    };

    Source estimatedSource = tdoaLocalization(receivers);

    std::cout << "Estimated Source Location: (" << estimatedSource.x << ", " << estimatedSource.y << ")\n";

    return 0;
}
