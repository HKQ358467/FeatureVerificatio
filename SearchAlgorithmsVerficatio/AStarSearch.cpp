#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

// 网格行数和列数
const int ROW = 5;
const int COL = 5;

// 方向移动（上下左右）
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

// 节点结构体
struct Node {
    int x, y; // 节点在网格中的位置
    int g, f; // g(n)是起点到当前点的成本，f(n)是g(n)加上启发式估计h(n)
    Node *parent; // 父节点指针

    Node(int x, int y, int g, int f, Node *p) : x(x), y(y), g(g), f(f), parent(p) {}

    // 重载<操作符，优先队列需要
    bool operator<(const Node& rhs) const {
        return f > rhs.f;
    }

    // 用于unordered_map的哈希函数
    struct HashFunction {
        size_t operator()(const Node& node) const {
            return node.x * COL + node.y;
        }
    };

    // 用于unordered_map比较节点是否相同
    struct Equal {
        bool operator()(const Node& a, const Node& b) const {
            return a.x == b.x && a.y == b.y;
        }
    };
};

// 检查点是否在网格内并且可通过
bool isValid(int x, int y, int grid[][COL]) {
    return (x >= 0) && (x < ROW) && (y >= 0) && (y < COL) && (grid[x][y] == 0);
}

// 启发式函数，使用曼哈顿距离
int heuristic(int x, int y, int goalX, int goalY) {
    return abs(x - goalX) + abs(y - goalY);
}

// 用来追踪回溯路径
void tracePath(Node *node) {
    vector<pair<int, int>> path;
    while (node != nullptr) {
        path.push_back({node->x, node->y});
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    for (auto &p : path) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << endl;
}

// A*算法搜索
void aStarSearch(int grid[][COL], int startX, int startY, int goalX, int goalY) {
    if (!isValid(startX, startY, grid) || !isValid(goalX, goalY, grid)) {
        cout << "Start or goal is invalid or blocked." << endl;
        return;
    }

    // openList是可以探索的节点
    priority_queue<Node> openList;
    // inOpenList用来检查节点是否已经在openList中
    unordered_map<Node, bool, Node::HashFunction, Node::Equal> inOpenList;

    Node *initialNode = new Node(startX, startY, 0, heuristic(startX, startY, goalX, goalY), nullptr);
    openList.push(*initialNode);
    inOpenList[*initialNode] = true;

    while (!openList.empty()) {
        Node currentNode = openList.top();
        openList.pop();

        // 到达目标节点
        if (currentNode.x == goalX && currentNode.y == goalY) {
            cout << "Path found: ";
            tracePath(&currentNode);
            return;
        }

        // 探索当前节点的所有邻居
        for (int i = 0; i < 4; i++) {
            int nextX = currentNode.x + dx[i];
            int nextY = currentNode.y + dy[i];

            if (isValid(nextX, nextY, grid)) {
                Node nextNode(nextX, nextY, currentNode.g + 1, 0, new Node(currentNode));
                nextNode.f = nextNode.g + heuristic(nextX, nextY, goalX, goalY);

                // 如果不在openList中或在openList中但有更好的g值，则更新openList
                if (!inOpenList[nextNode] || inOpenList[nextNode] && nextNode.g < openList.top().g) {
                    openList.push(nextNode);
                    inOpenList[nextNode] = true;
                }
            }
        }
    }

    cout << "No path found." << endl;
}

int main() {
    int grid[ROW][COL] = {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 1},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 1, 0}
    };

    int startX = 0, startY = 0;
    int goalX = 4, goalY = 4;

    aStarSearch(grid, startX, startY, goalX, goalY);

    return 0;
}
