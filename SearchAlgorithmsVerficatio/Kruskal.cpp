#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>

// 并查集数据结构用于维护图的各个连通分量
class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    // 构造函数，初始化n个元素的并查集
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // 查找元素x的根节点，路径压缩优化
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // 合并元素x和元素y所在的集合
    void unite(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);

        if (xRoot != yRoot) {
            // 按秩合并优化，将秩小的根节点连接到秩大的根节点上
            if (rank[xRoot] < rank[yRoot]) {
                parent[xRoot] = yRoot;
            } else if (rank[xRoot] > rank[yRoot]) {
                parent[yRoot] = xRoot;
            } else {
                parent[yRoot] = xRoot;
                rank[xRoot]++;
            }
        }
    }

    // 判断元素x和元素y是否属于同一集合
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

// 克鲁斯卡尔算法实现
std::vector<std::tuple<int, int, int>> kruskal(int n, std::vector<std::tuple<int, int, int>>& edges) {
    std::vector<std::tuple<int, int, int>> result; // 用于存储最小生成树的边
    UnionFind uf(n); // 初始化并查集

    // 根据边的权重对所有边进行排序
    std::sort(edges.begin(), edges.end(), [](const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b) {
        return std::get<2>(a) < std::get<2>(b);
    });

    // 遍历每条边，决定是否添加到最小生成树中
    for (const auto& edge : edges) {
        int u, v, weight;
        std::tie(u, v, weight) = edge;

        // 如果当前边的两个顶点属于不同的连通分量，则添加该边
        if (!uf.connected(u, v)) {
            uf.unite(u, v);
            result.push_back(edge);
        }
    }

    return result;
}

int main() {
    // 图的顶点数和边
    int n = 4;
    std::vector<std::tuple<int, int, int>> edges = {
            {0, 1, 10},
            {0, 2, 6},
            {0, 3, 5},
            {1, 3, 15},
            {2, 3, 4}
    };

    // 执行克鲁斯卡尔算法
    std::vector<std::tuple<int, int, int>> mst = kruskal(n, edges);

    // 输出最小生成树的边
    std::cout << "Edges in the Minimum Spanning Tree:" << std::endl;
    for (auto& edge : mst) {
        int u, v, weight;
        std::tie(u, v, weight) = edge;
        std::cout << "(" << u << ", " << v << ") - " << weight << std::endl;
    }

    return 0;
}
