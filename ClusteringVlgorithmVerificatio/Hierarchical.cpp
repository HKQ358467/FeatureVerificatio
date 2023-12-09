#include <iostream>
#include <vector>
#include <cmath>

// 定义数据点的结构
struct Point {
    double x, y;
};

// 定义簇的结构
struct Cluster {
    Point centroid;
    std::vector<Point> points;
};

// 计算两个点之间的欧氏距离
double calculateDistance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// 计算簇的质心
Point calculateCentroid(const Cluster& cluster) {
    Point centroid = {0.0, 0.0};
    for (const auto& point : cluster.points) {
        centroid.x += point.x;
        centroid.y += point.y;
    }
    centroid.x /= cluster.points.size();
    centroid.y /= cluster.points.size();
    return centroid;
}

// 层次聚类算法
std::vector<Cluster> hierarchicalClustering(const std::vector<Point>& data) {
    // 初始化每个数据点为一个簇
    std::vector<Cluster> clusters;
    for (const auto& point : data) {
        clusters.push_back({point, {point}});
    }

    // 合并最相似的簇，直到只剩一个簇
    while (clusters.size() > 1) {
        double minDistance = std::numeric_limits<double>::max();
        int mergeIdx1 = -1, mergeIdx2 = -1;

        // 找到最相似的两个簇
        for (int i = 0; i < clusters.size(); ++i) {
            for (int j = i + 1; j < clusters.size(); ++j) {
                double distance = calculateDistance(clusters[i].centroid, clusters[j].centroid);
                if (distance < minDistance) {
                    minDistance = distance;
                    mergeIdx1 = i;
                    mergeIdx2 = j;
                }
            }
        }

        // 合并簇
        Cluster mergedCluster;
        mergedCluster.points = clusters[mergeIdx1].points;
        mergedCluster.points.insert(mergedCluster.points.end(),
                                    clusters[mergeIdx2].points.begin(),
                                    clusters[mergeIdx2].points.end());
        mergedCluster.centroid = calculateCentroid(mergedCluster);

        // 移除已合并的簇
        clusters.erase(clusters.begin() + mergeIdx2);
        clusters[mergeIdx1] = mergedCluster;
    }

    return clusters;
}

int main() {
    // 构造示例数据
    std::vector<Point> data = {{1.0, 2.0}, {2.0, 3.0}, {8.0, 7.0}, {3.0, 4.0}, {7.0, 6.0}, {5.0, 6.0}};

    // 执行层次聚类
    std::vector<Cluster> result = hierarchicalClustering(data);

    // 打印聚类结果
    for (int i = 0; i < result.size(); ++i) {
        std::cout << "Cluster " << i + 1 << " (Centroid: " << result[i].centroid.x
                  << ", " << result[i].centroid.y << "): ";
        for (const auto& point : result[i].points) {
            std::cout << "(" << point.x << ", " << point.y << ") ";
        }
        std::cout << "\n";
    }

    return 0;
}
