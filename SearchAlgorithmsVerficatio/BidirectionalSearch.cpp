#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>

// 图的简单表示法，使用邻接表
using Graph = std::unordered_map<int, std::vector<int>>;

// 辅助函数，用于构建路径
std::vector<int> buildPath(std::unordered_map<int, int>& prev, int start, int end) {
    std::vector<int> path;
    for (int at = end; at != start; at = prev[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

// 双向搜索算法
// 返回一个从 start 到 goal 的路径（如果找到了的话）
std::vector<int> bidirectionalSearch(const Graph& graph, int start, int goal) {
    // 用于记录从起点开始访问的节点
    std::unordered_map<int, int> prev_from_start;
    // 用于记录从终点开始访问的节点
    std::unordered_map<int, int> prev_from_goal;

    // 从两个方向都进行广度优先搜索
    std::queue<int> queue_from_start;
    std::queue<int> queue_from_goal;

    // 用于标记节点是否被访问过
    std::unordered_set<int> visited_from_start;
    std::unordered_set<int> visited_from_goal;

    // 初始化
    queue_from_start.push(start);
    visited_from_start.insert(start);
    prev_from_start[start] = -1; // 使用 -1 表示起始节点没有前驱节点

    queue_from_goal.push(goal);
    visited_from_goal.insert(goal);
    prev_from_goal[goal] = -1; // 同样使用 -1 表示目标节点没有前驱节点

    while (!queue_from_start.empty() && !queue_from_goal.empty()) {
        // 从起点开始的搜索
        int current_from_start = queue_from_start.front();
        queue_from_start.pop();
        for (int neighbor : graph.at(current_from_start)) {
            if (visited_from_start.find(neighbor) == visited_from_start.end()) {
                queue_from_start.push(neighbor);
                visited_from_start.insert(neighbor);
                prev_from_start[neighbor] = current_from_start;

                // 如果这个邻居节点在对面的搜索中已经访问过了，这意味着我们找到了连接路径
                if (visited_from_goal.find(neighbor) != visited_from_goal.end()) {
                    // 合并路径，并返回结果
                    auto path_from_start = buildPath(prev_from_start, start, neighbor);
                    auto path_from_goal = buildPath(prev_from_goal, goal, neighbor);
                    path_from_goal.pop_back(); // 移除重复的中间节点
                    path_from_start.insert(path_from_start.end(), path_from_goal.rbegin(), path_from_goal.rend());
                    return path_from_start;
                }
            }
        }

        // 从终点开始的搜索
        int current_from_goal = queue_from_goal.front();
        queue_from_goal.pop();
        for (int neighbor : graph.at(current_from_goal)) {
            if (visited_from_goal.find(neighbor) == visited_from_goal.end()) {
                queue_from_goal.push(neighbor);
                visited_from_goal.insert(neighbor);
                prev_from_goal[neighbor] = current_from_goal;

                // 如果这个邻居节点在起点的搜索中已经访问过了，这意味着我们找到了连接路径
                if (visited_from_start.find(neighbor) != visited_from_start.end()) {
                    // 合并路径，并返回结果
                    auto path_from_goal = buildPath(prev_from_goal, goal, neighbor);
                    auto path_from_start = buildPath(prev_from_start, start, neighbor);
                    path_from_start.pop_back(); // 移除重复的中间节点
                    path_from_goal.insert(path_from_goal.end(), path_from_start.rbegin(), path_from_start.rend());
                    return path_from_goal;
                }
            }
        }
    }

    // 如果没有路径被找到，返回空路径
    return {};
}

int main() {
    // 创建一个图
    Graph graph = {
            {0, {1, 3}},
            {1, {0, 2, 3}},
            {2, {1}},
            {3, {0, 1, 4}},
            {4, {3}}
    };

    int start = 0; // 起始节点
    int goal = 4;  // 目标节点

    auto path = bidirectionalSearch(graph, start, goal);

    // 输出路径
    if (!path.empty()) {
        std::cout << "Path found: ";
        for (int i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i < path.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "No path found from " << start << " to " << goal << std::endl;
    }

    return 0;
}
