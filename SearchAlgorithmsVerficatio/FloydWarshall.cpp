#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义无穷大的值，用于初始化距离
const int INF = 1e9;

// 弗洛伊德算法实现
void floydWarshall(vector<vector<int>>& graph) {
    int V = graph.size(); // 图中顶点的数量
    vector<vector<int>> dist(V, vector<int>(V, INF)); // dist数组，存储各对顶点之间的最短距离

    // 初始化距离矩阵，对角线为0，其他为边的权重或无穷大
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j) {
                dist[i][j] = 0; // 同一个顶点的最短距离是0
            } else if (graph[i][j]) {
                dist[i][j] = graph[i][j]; // 有直接边的顶点之间的距离是边的权重
            }
        }
    }

    // 弗洛伊德算法的三重循环
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                // 更新dist[i][j]为顶点i到顶点k再到顶点j的路径与当前dist[i][j]的较小值
                if (dist[i][k] < INF && dist[k][j] < INF) { // 避免整数溢出
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 输出结果
    cout << "The shortest distances between every pair of vertices:" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // 图的邻接矩阵表示，0表示自身，INF表示不直接相连
    vector<vector<int>> graph = {
            {0,   5,   INF, 10},
            {INF, 0,   3,   INF},
            {INF, INF, 0,   1},
            {INF, INF, INF, 0}
    };

    // 执行弗洛伊德算法
    floydWarshall(graph);

    return 0;
}
