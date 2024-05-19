#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional> // 用于 std::function
#include <climits> // 用于 INT_MAX

using namespace std;

// 定义图的边
struct Edge {
    int to;     // 目标节点
    int weight; // 边的权重
};

// 定义启发式函数类型
using HeuristicFunction = function<int(int)>;

// 贪婪最佳优先搜索算法
void greedyBestFirstSearch(int start, int goal, const vector<vector<Edge>>& graph, const HeuristicFunction& heuristic) {
    // 优先队列，根据启发式值排序节点
    auto cmp = [&](int left, int right) { return heuristic(left) > heuristic(right); };
    priority_queue<int, vector<int>, decltype(cmp)> frontier(cmp);

    // 来自起始节点的起始点
    frontier.push(start);

    // 用于跟踪访问过的节点
    unordered_map<int, bool> visited;

    // 路径重建
    unordered_map<int, int> cameFrom;
    cameFrom[start] = -1; // 起始点没有前驱

    while (!frontier.empty()) {
        int current = frontier.top();
        frontier.pop();

        if (current == goal) {
            // 找到目标，重建路径
            vector<int> path;
            for (int at = goal; at != -1; at = cameFrom[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            cout << "Found path: ";
            for (int node : path) {
                cout << node << " ";
            }
            cout << endl;
            return;
        }

        // 标记当前节点为已访问
        if (visited[current]) continue;
        visited[current] = true;

        for (const auto& edge : graph[current]) {
            int next = edge.to;
            if (!visited[next]) {
                frontier.push(next);
                if (cameFrom.find(next) == cameFrom.end()) { // 如果next未被访问过
                    cameFrom[next] = current;
                }
            }
        }
    }

    cout << "No path found." << endl;
}

// 主函数
int main() {
    // 示例图的节点和边
    vector<vector<Edge>> graph = {
            { {1, 1}, {2, 1} }, // 0 连接到 1 和 2
            { {2, 1}, {3, 1} }, // 1 连接到 2 和 3
            { {3, 1} },        // 2 连接到 3
            {}                 // 3 是目标节点
    };

    // 简单的启发式函数示例：所有节点到目标的启发式值为0（这在实践中可能不是最佳选择）
    HeuristicFunction heuristic = [](int node) { return 0; };

    greedyBestFirstSearch(0, 3, graph, heuristic); // 从节点0开始，目标是节点3

    return 0;
}
