#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include<algorithm>

using namespace std;

// 定义图的边
struct Edge {
    int to;       // 目标节点
    int cost;     // 边的权重
    Edge(int t, int c) : to(t), cost(c) {}
};

// 使用邻接表表示图
using Graph = vector<vector<Edge>>;

// 用来比较优先队列中的边
struct CompareEdge {
    bool operator()(const Edge &a, const Edge &b) {
        return a.cost > b.cost; // 优先队列应该返回成本最低的边
    }
};

// 均匀成本搜索
bool UniformCostSearch(const Graph &graph, int start, int goal, unordered_map<int, int> &cameFrom, unordered_map<int, int> &costSoFar) {
    priority_queue<Edge, vector<Edge>, CompareEdge> frontier; // 边的优先队列
    frontier.emplace(start, 0);
    costSoFar[start] = 0;
    cameFrom[start] = -1; // 使用-1来表示起始节点没有前导节点

    while (!frontier.empty()) {
        Edge currentEdge = frontier.top();
        int current = currentEdge.to;
        frontier.pop();

        if (current == goal) {
            // 找到目标节点，退出搜索
            return true;
        }

        // 遍历当前节点的所有邻居
        for (const Edge &nextEdge : graph[current]) {
            int next = nextEdge.to;
            int newCost = costSoFar[current] + nextEdge.cost;

            // 如果下一个节点没有访问过，或者我们找到了一条更便宜的路径到达这个节点
            if (!costSoFar.count(next) || newCost < costSoFar[next]) {
                costSoFar[next] = newCost;
                frontier.emplace(next, newCost);
                cameFrom[next] = current; // 记录节点来向，以便重建路径
            }
        }
    }

    return false; // 如果没有找到路径，则返回false
}

void ReconstructPath(int start, int goal, unordered_map<int, int> &cameFrom) {
    if (cameFrom.find(goal) == cameFrom.end()) {
        cout << "No path found from " << start << " to " << goal << endl;
        return;
    }
    vector<int> path;
    int current = goal;
    while (current != start) {
        path.push_back(current);
        current = cameFrom[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (auto it = path.begin(); it != path.end(); ++it) {
        cout << *it;
        if (next(it) != path.end()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    Graph graph = {
            {Edge(1, 2), Edge(2, 5)}, // 节点0连接到节点1和节点2，权重分别是2和5
            {Edge(2, 1), Edge(3, 4)}, // 节点1连接到节点2和节点3，权重分别是1和4
            {Edge(3, 1)},             // 节点2连接到节点3，权重是1
            {}                        // 节点3没有连接到其他节点
    };

    int start = 0; // 起始节点
    int goal = 3;  // 目标节点
    unordered_map<int, int> cameFrom;
    unordered_map<int, int> costSoFar;

    bool found = UniformCostSearch(graph, start, goal, cameFrom, costSoFar);
    if (found) {
        cout << "Cost to reach goal: " << costSoFar[goal] << endl;
        ReconstructPath(start, goal, cameFrom);
    } else {
        cout << "No path found from " << start << " to " << goal << endl;
    }

    return 0;
}
