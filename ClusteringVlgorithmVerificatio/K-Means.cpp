#include <iostream>
#include <vector>
#include <cmath>

// 定义数据点结构
struct Point {
    double x;
    double y;
};

// 定义簇结构
struct Cluster {
    Point centroid;
    std::vector<Point> points;
};

// 计算两点之间的欧氏距离
double distance(Point p1, Point p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

// 将点分配给最近的簇
void assignToClusters(const std::vector<Point>& data, std::vector<Cluster>& clusters) {
    for (auto& cluster : clusters) {
        cluster.points.clear();
    }

    for (const auto& point : data) {
        double minDist = std::numeric_limits<double>::max();
        Cluster* closestCluster = nullptr;

        for (auto& cluster : clusters) {
            double dist = distance(point, cluster.centroid);
            if (dist < minDist) {
                minDist = dist;
                closestCluster = &cluster;
            }
        }

        if (closestCluster != nullptr) {
            closestCluster->points.push_back(point);
        }
    }
}

// 更新簇的质心
void updateCentroids(std::vector<Cluster>& clusters) {
    for (auto& cluster : clusters) {
        if (!cluster.points.empty()) {
            double sumX = 0.0, sumY = 0.0;
            for (const auto& point : cluster.points) {
                sumX += point.x;
                sumY += point.y;
            }
            cluster.centroid.x = sumX / cluster.points.size();
            cluster.centroid.y = sumY / cluster.points.size();
        }
    }
}

// 打印簇的信息
void printClusters(const std::vector<Cluster>& clusters) {
    int clusterNum = 1;
    for (const auto& cluster : clusters) {
        std::cout << "Cluster " << clusterNum << " (Centroid: " << cluster.centroid.x << ", " << cluster.centroid.y << "): ";
        for (const auto& point : cluster.points) {
            std::cout << "(" << point.x << ", " << point.y << ") ";
        }
        std::cout << std::endl;
        clusterNum++;
    }
    std::cout << std::endl;
}

int main() {
    // 数据集
    std::vector<Point> data = { {1.0, 2.0}, {2.0, 3.0}, {5.0, 8.0}, {6.0, 7.0}, {8.0, 2.0}, {9.0, 5.0} };

    // 初始化簇
    std::vector<Cluster> clusters = { { {1.0, 2.0}, {} }, { {8.0, 2.0}, {} } };

    // 执行K均值聚类
    const int maxIterations = 100;
    for (int iter = 0; iter < maxIterations; ++iter) {
        assignToClusters(data, clusters);
        updateCentroids(clusters);

        // 输出当前簇的信息
        std::cout << "Iteration " << iter + 1 << ":\n";
        printClusters(clusters);
    }

    return 0;
}
