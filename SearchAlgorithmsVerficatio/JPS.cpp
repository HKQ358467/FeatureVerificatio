#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cmath>

// 表示网格上一个点的简单结构体
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}

    // 重载==运算符，用于比较两个点是否相同
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    // 重载<运算符，用于存储于std::set中
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

// 为Point结构体实现一个哈希函数，以便将其用作unordered_map的键
namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };
}

// 简单的网格类，包含障碍物信息
class Grid {
public:
    int width, height;
    std::vector<std::vector<bool>> obstacles;

    Grid(int width, int height) : width(width), height(height), obstacles(width, std::vector<bool>(height, false)) {}

    // 设置障碍物
    void setObstacle(int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            obstacles[x][y] = true;
        }
    }

    // 检查点是否可通行
    bool isWalkable(int x, int y) const {
        return x >= 0 && x < width && y >= 0 && y < height && !obstacles[x][y];
    }
};

// JPS算法实现的核心部分
class JPS {
public:
    static std::vector<Point> findPath(const Grid& grid, Point start, Point end) {
        // 路径结果
        std::vector<Point> path;
        // 这里我们直接从起点跳到终点，没有中间步骤，仅作为示范
        if (grid.isWalkable(end.x, end.y)) {
            path.push_back(start);
            path.push_back(end);
        }
        return path;
    }
};

int main() {
    // 创建一个10x10的网格
    Grid grid(10, 10);
    // 设置一些障碍物
    grid.setObstacle(2, 3);
    grid.setObstacle(2, 4);
    grid.setObstacle(2, 5);

    // 定义起点和终点
    Point start(0, 0), end(9, 9);

    // 使用JPS寻找路径
    auto path = JPS::findPath(grid, start, end);

    // 打印路径
    for (auto& point : path) {
        std::cout << "(" << point.x << ", " << point.y << ") ";
    }

    return 0;
}
