#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <random>
#include <cassert>

// 代表一个高斯分布
struct Gaussian {
    std::vector<double> mean;
    std::vector<std::vector<double>> covariance;
    double weight;

    // 计算多维高斯分布的概率密度函数
    double probabilityDensity(const std::vector<double>& x) const {
        assert(mean.size() == x.size());
        size_t dimension = x.size();
        double det = 1; // 协方差矩阵的行列式
        std::vector<double> xMinusMu(dimension);
        for (size_t i = 0; i < dimension; ++i) {
            xMinusMu[i] = x[i] - mean[i];
            det *= covariance[i][i]; // 为简单起见，这里假设协方差矩阵是对角阵
        }
        double coeff = 1 / std::sqrt(std::pow(2 * M_PI, dimension) * det);
        double expVal = 0;
        for (size_t i = 0; i < dimension; ++i) {
            expVal += std::pow(xMinusMu[i], 2) / covariance[i][i];
        }
        return coeff * std::exp(-0.5 * expVal);
    }
};

// 用于存储数据点和其对应的权重（隐变量）
struct DataPoint {
    std::vector<double> value;
    std::vector<double> weights;
};

// GMM聚类算法的实现
class GMM {
private:
    std::vector<Gaussian> gaussians;
    std::vector<DataPoint> dataPoints;
    size_t dimension;
    size_t numberOfGaussians;

    void initializeGaussians() {
        for (auto& gaussian : gaussians) {
            gaussian.mean = std::vector<double>(dimension, 0);
            gaussian.covariance = std::vector<std::vector<double>>(dimension, std::vector<double>(dimension, 0));
            gaussian.weight = 1.0 / numberOfGaussians;

            for (size_t i = 0; i < dimension; ++i) {
                gaussian.mean[i] = (rand() % 1000) / 1000.0; // 随机初始化均值
                gaussian.covariance[i][i] = 1; // 初始化为单位矩阵
            }
        }
    }

    // E步：计算数据点的权重
    void expectationStep() {
        for (auto& dataPoint : dataPoints) {
            double totalWeight = 0;
            for (size_t j = 0; j < numberOfGaussians; ++j) {
                dataPoint.weights[j] = gaussians[j].weight * gaussians[j].probabilityDensity(dataPoint.value);
                totalWeight += dataPoint.weights[j];
            }
            for (size_t j = 0; j < numberOfGaussians; ++j) {
                dataPoint.weights[j] /= totalWeight;
            }
        }
    }

    // M步：更新高斯分布的参数
    void maximizationStep() {
        for (size_t j = 0; j < numberOfGaussians; ++j) {
            double weightSum = 0;
            std::vector<double> newMean(dimension, 0);
            std::vector<std::vector<double>> newCovariance(dimension, std::vector<double>(dimension, 0));

            for (auto& dataPoint : dataPoints) {
                weightSum += dataPoint.weights[j];
                for (size_t i = 0; i < dimension; ++i) {
                    newMean[i] += dataPoint.weights[j] * dataPoint.value[i];
                }
            }

            for (size_t i = 0; i < dimension; ++i) {
                newMean[i] /= weightSum;
            }

            for (auto& dataPoint : dataPoints) {
                for (size_t i = 0; i < dimension; ++i) {
                    double diff = dataPoint.value[i] - newMean[i];
                    newCovariance[i][i] += dataPoint.weights[j] * diff * diff;
                }
            }

            for (size_t i = 0; i < dimension; ++i) {
                newCovariance[i][i] /= weightSum;
            }

            gaussians[j].mean = newMean;
            gaussians[j].covariance = newCovariance;
            gaussians[j].weight = weightSum / dataPoints.size();
        }
    }

public:
    GMM(size_t numGaussians, size_t dim) : numberOfGaussians(numGaussians), dimension(dim) {
        gaussians.resize(numberOfGaussians);
        initializeGaussians();
    }

    void addDataPoint(const std::vector<double>& point) {
        assert(point.size() == dimension);
        dataPoints.push_back({point, std::vector<double>(numberOfGaussians, 0)});
    }

    void fit(size_t iterations) {
        for (size_t i = 0; i < iterations; ++i) {
            expectationStep();
            maximizationStep();
        }
    }

    void printGaussians() const {
        for (const auto& gaussian : gaussians) {
            std::cout << "Gaussian with weight " << gaussian.weight << ":\n";
            std::cout << "Mean: [";
            for (const auto& m : gaussian.mean) {
                std::cout << m << " ";
            }
            std::cout << "]\n";
            std::cout << "Covariance Matrix: [\n";
            for (const auto& row : gaussian.covariance) {
                for (const auto& val : row) {
                    std::cout << val << " ";
                }
                std::cout << "\n";
            }
            std::cout << "]\n\n";
        }
    }
};

int main() {
    // 设置随机种子
    srand(static_cast<unsigned int>(time(nullptr)));

    // 创建GMM实例
    GMM gmm(2, 2); // 假设有两个高斯分布，每个分布是二维的

    // 添加一些数据点
    gmm.addDataPoint({0.5, 0.2});
    gmm.addDataPoint({0.2, 0.3});
    gmm.addDataPoint({0.9, 0.7});
    gmm.addDataPoint({0.3, 0.8});

    // 运行GMM算法
    gmm.fit(10); // 迭代10次

    // 打印高斯分布的参数
    gmm.printGaussians();

    return 0;
}
