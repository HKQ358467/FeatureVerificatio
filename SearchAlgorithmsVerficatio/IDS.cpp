#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// 定义图的边
struct Edge {
    int to; // 目标节点
};

// 使用邻接表表示图
using Graph = vector<vector<Edge>>;

// 深度限制的深度优先搜索
bool DLS(int node, int goal, const Graph &graph, vector<bool> &visited, int limit) {
    if (node == goal) { // 检查当前节点是否为目标节点
        return true;
    }
    if (limit <= 0) { // 达到深度限制
        return false;
    }
    visited[node] = true; // 标记当前节点为已访问
    for (const auto &edge : graph[node]) {
        if (!visited[edge.to]) {
            if (DLS(edge.to, goal, graph, visited, limit - 1)) {
                return true;
            }
        }
    }
    return false;
}

// 迭代加深搜索
bool IDS(int start, int goal, const Graph &graph, int maxDepth) {
    for (int depth = 0; depth <= maxDepth; ++depth) {
        vector<bool> visited(graph.size(), false); // 初始化访问标记
        if (DLS(start, goal, graph, visited, depth)) {
            cout << "Found goal at depth: " << depth << endl;
            return true;
        }
    }
    return false;
}

int main() {
    // 构建图
    Graph graph = {
            {{1}, {2}}, // 节点0连接到节点1和节点2
            {{2}, {3}}, // 节点1连接到节点2和节点3
            {{3}},      // 节点2连接到节点3
            {}          // 节点3没有边
    };

    int start = 0; // 起始节点
    int goal = 3;  // 目标节点
    int maxDepth = 3; // 最大深度限制

    if (!IDS(start, goal, graph, maxDepth)) {
        cout << "Goal not found within depth limit." << endl;
    }

    return 0;
}
