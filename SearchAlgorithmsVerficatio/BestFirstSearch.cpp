#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <functional>

struct Node {
    int x, y; // 节点在网格中的位置
    int cost; // 到达该节点的成本（本示例中未使用，但在复杂场景下可能需要）
    int distance; // 启发式函数评估的从当前节点到目标节点的距离
    Node *parent; // 指向父节点的指针，用于重建路径

    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

// 启发式函数：计算曼哈顿距离
int heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

// 检查是否可以在网格中移动到新的位置
bool canMove(int x, int y, const std::vector<std::vector<int>>& grid) {
    // 检查是否在网格边界内以及是否为障碍物
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == 0;
}

// 重建路径：从终点回溯到起点
void reconstructPath(Node* node) {
    std::vector<std::pair<int, int>> path;
    while (node) {
        path.push_back({node->x, node->y});
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    for (auto& p : path) {
        std::cout << "(" << p.first << ", " << p.second << ") ";
    }
}

// 最佳优先搜索算法
void bestFirstSearch(const std::vector<std::vector<int>>& grid, int startX, int startY, int goalX, int goalY) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;
    std::unordered_map<int, bool> visited;
    frontier.push({startX, startY, 0, heuristic(startX, startY, goalX, goalY), nullptr});

    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();

        if (current.x == goalX && current.y == goalY) {
            std::cout << "Path found: ";
            reconstructPath(&current);
            return;
        }

        visited[current.x * 1000 + current.y] = true;

        std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (auto& dir : directions) {
            int newX = current.x + dir.first;
            int newY = current.y + dir.second;

            if (canMove(newX, newY, grid) && !visited[newX * 1000 + newY]) {
                frontier.push({newX, newY, 0, heuristic(newX, newY, goalX, goalY), new Node(current)});
            }
        }
    }

    std::cout << "Path not found." << std::endl;
}

int main() {
    std::vector<std::vector<int>> grid = {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0}
    };

    bestFirstSearch(grid, 0, 0, 4, 4);

    return 0;
}
