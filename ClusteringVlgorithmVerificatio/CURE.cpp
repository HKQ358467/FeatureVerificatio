#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>

// 表示数据点
struct Point {
    std::vector<double> coordinates;

    double distanceTo(const Point& other) const {
        double sum = 0.0;
        for (size_t i = 0; i < coordinates.size(); ++i) {
            sum += (coordinates[i] - other.coordinates[i]) * (coordinates[i] - other.coordinates[i]);
        }
        return std::sqrt(sum);
    }
};

// 表示一个簇
struct Cluster {
    std::vector<Point> points;
    std::vector<Point> representatives;
};

// CURE算法实现
class CURE {
private:
    std::vector<Cluster> clusters;

    // 合并两个簇
    void mergeClusters(size_t clusterIndex1, size_t clusterIndex2) {
        // 将cluster2的点合并到cluster1
        clusters[clusterIndex1].points.insert(
                clusters[clusterIndex1].points.end(),
                clusters[clusterIndex2].points.begin(),
                clusters[clusterIndex2].points.end()
        );
        // 移除cluster2
        clusters.erase(clusters.begin() + clusterIndex2);
    }

    // 选择代表点
    void selectRepresentatives(Cluster& cluster, size_t numRepresentatives) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, cluster.points.size() - 1);

        // 随机选择代表点
        while (cluster.representatives.size() < numRepresentatives) {
            size_t index = distrib(gen);
            cluster.representatives.push_back(cluster.points[index]);
        }
    }

public:
    explicit CURE(std::vector<Point> points, size_t numClusters, size_t numRepresentatives) {
        // 初始时每个数据点是一个簇
        for (const auto& point : points) {
            clusters.push_back({std::vector<Point>{point}, std::vector<Point>{}});
        }

        // 选择每个簇的代表点
        for (auto& cluster : clusters) {
            selectRepresentatives(cluster, numRepresentatives);
        }

        // 层次聚类直到只剩下numClusters个簇
        while (clusters.size() > numClusters) {
            double minDistance = std::numeric_limits<double>::max();
            std::pair<size_t, size_t> minPair;

            // 寻找最近的簇对
            for (size_t i = 0; i < clusters.size(); ++i) {
                for (size_t j = i + 1; j < clusters.size(); ++j) {
                    double distance = std::numeric_limits<double>::max();
                    for (const auto& rep1 : clusters[i].representatives) {
                        for (const auto& rep2 : clusters[j].representatives) {
                            distance = std::min(distance, rep1.distanceTo(rep2));
                        }
                    }
                    if (distance < minDistance) {
                        minDistance = distance;
                        minPair = {i, j};
                    }
                }
            }

            // 合并最近的簇对
            mergeClusters(minPair.first, minPair.second);
        }
    }

    void printClusters() {
        for (size_t i = 0; i < clusters.size(); ++i) {
            std::cout << "Cluster " << i + 1 << ":\n";
            for (const auto& point : clusters[i].points) {
                std::cout << "(";
                for (size_t j = 0; j < point.coordinates.size(); ++j) {
                    std::cout << point.coordinates[j];
                    if (j < point.coordinates.size() - 1) std::cout << ", ";
                }
                std::cout << ")\n";
            }
            std::cout << "Representatives:\n";
            for (const auto& rep : clusters[i].representatives) {
                std::cout << "(";
                for (size_t j = 0; j < rep.coordinates.size(); ++j) {
                    std::cout << rep.coordinates[j];
                    if (j < rep.coordinates.size() - 1) std::cout << ", ";
                }
                std::cout << ")\n";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    // 创建一些示例数据点
    std::vector<Point> points = {
            {{0.1, 0.2}},
            {{0.2, 0.1}},
            {{0.3, 0.3}},
            {{0.4, 0.5}},
            {{5.1, 5.2}},
            {{5.2, 5.1}},
            {{5.3, 5.3}}
    };

    // 执行CURE算法
    CURE cure(points, 2, 2); // 参数：数据点，目标簇的数目，每个簇的代表点数目

    // 打印结果
    cure.printClusters();

    return 0;
}
