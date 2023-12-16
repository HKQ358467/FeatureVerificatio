#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x, y;

    Point() : x(0.0), y(0.0) {}
    Point(double _x, double _y) : x(_x), y(_y) {}
};

double euclideanDistance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

Point meanShift(const Point& point, const std::vector<Point>& data, double bandwidth) {
    Point shiftedPoint;
    double totalWeight = 0.0;

    for (const Point& dataPoint : data) {
        double distance = euclideanDistance(point, dataPoint);
        double weight = std::exp(-(distance * distance) / (2.0 * bandwidth * bandwidth));

        shiftedPoint.x += weight * dataPoint.x;
        shiftedPoint.y += weight * dataPoint.y;
        totalWeight += weight;
    }

    shiftedPoint.x /= totalWeight;
    shiftedPoint.y /= totalWeight;

    return shiftedPoint;
}

void meanShiftClustering(std::vector<Point>& data, double bandwidth, double shiftThreshold) {
    std::vector<Point> shiftedPoints = data;

    for (int iteration = 0; iteration < 10; ++iteration) {  // 迭代次数
        for (Point& point : shiftedPoints) {
            Point shiftedPoint = meanShift(point, data, bandwidth);
            double shiftDistance = euclideanDistance(point, shiftedPoint);

            if (shiftDistance > shiftThreshold) {
                point = shiftedPoint;
            }
        }
    }

    // TODO: 对shiftedPoints进行进一步处理，将相近的点合并成簇等操作
    // 这里简化处理，直接输出shiftedPoints
    std::cout << "Mean Shift Clusters:\n";
    for (const Point& point : shiftedPoints) {
        std::cout << "(" << point.x << ", " << point.y << ")\n";
    }
}

int main() {
    // 生成一些随机二维数据
    std::vector<Point> data = {
            {1.0, 2.0}, {1.5, 1.8}, {5.0, 8.0},
            {8.0, 8.0}, {1.0, 0.6}, {9.0, 11.0},
            {8.0, 2.0}, {10.0, 2.0}, {9.0, 3.0}
    };

    double bandwidth = 3.0;  // 带宽
    double shiftThreshold = 0.1;  // 移动阈值

    meanShiftClustering(data, bandwidth, shiftThreshold);

    return 0;
}
