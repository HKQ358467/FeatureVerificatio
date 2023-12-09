#include <iostream>
#include <vector>
#include <cmath>

// 定义数据点结构
struct Point {
    double x, y;
};

// DBSCAN算法类
class DBSCAN {
public:
    DBSCAN(double eps, int minPts, const std::vector<Point> &points);

    // 执行DBSCAN算法
    void run();

    // 获取聚类结果
    const std::vector<int> &getClusterResult() const {
        return clusterResult;
    }

private:
    // 计算两点之间的欧氏距离
    double calculateDistance(const Point &point1, const Point &point2) const;

    // 获取指定点的邻域内的点
    std::vector<int> getNeighbors(int pointIndex) const;

    // 将点标记为核心点，并将其密度可达的点加入簇中
    bool expandCluster(int pointIndex, int clusterId);

    double epsilon;  // 邻域半径
    int minPoints;   // 最小点数
    const std::vector<Point> &data;  // 数据集
    std::vector<int> clusterResult;  // 聚类结果
};

DBSCAN::DBSCAN(double eps, int minPts, const std::vector<Point> &points)
        : epsilon(eps), minPoints(minPts), data(points), clusterResult(points.size(), -1) {}

void DBSCAN::run() {
    int clusterId = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        if (clusterResult[i] == -1) {  // 未分类的点
            if (expandCluster(i, clusterId)) {
                clusterId++;
            }
        }
    }
}

double DBSCAN::calculateDistance(const Point &point1, const Point &point2) const {
    return std::sqrt(std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2));
}

std::vector<int> DBSCAN::getNeighbors(int pointIndex) const {
    std::vector<int> neighbors;
    for (size_t i = 0; i < data.size(); ++i) {
        if (i != pointIndex && calculateDistance(data[i], data[pointIndex]) <= epsilon) {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

bool DBSCAN::expandCluster(int pointIndex, int clusterId) {
    std::vector<int> seeds = getNeighbors(pointIndex);
    if (seeds.size() < minPoints) {
        clusterResult[pointIndex] = -2;  // 标记为噪声点
        return true;
    }

    // 将点标记为核心点，并将其密度可达的点加入簇中
    clusterResult[pointIndex] = clusterId;
    for (size_t i = 0; i < seeds.size(); ++i) {
        int currentPoint = seeds[i];
        if (clusterResult[currentPoint] == -1 || clusterResult[currentPoint] == -2) {
            if (clusterResult[currentPoint] == -1) {
                seeds.push_back(currentPoint);
            }
            clusterResult[currentPoint] = clusterId;
        }
    }
    return true;
}

int main() {
    // 定义一些数据点
    std::vector<Point> points = {{1,  2},
                                 {2,  2},
                                 {2,  3},
                                 {8,  7},
                                 {8,  8},
                                 {25, 80}};

    // 创建DBSCAN对象
    DBSCAN dbscan(5.0, 2, points);

    // 执行DBSCAN算法
    dbscan.run();

    // 获取聚类结果
    const std::vector<int> &clusterResult = dbscan.getClusterResult();

    // 打印聚类结果
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << "Point (" << points[i].x << ", " << points[i].y << ") belongs to cluster " << clusterResult[i]
                  << std::endl;
    }

    return 0;
}
