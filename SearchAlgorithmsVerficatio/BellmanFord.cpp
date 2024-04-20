#include <iostream>
#include <vector>
#include <limits>

// 定义无穷大为一个极大的值，这里使用了int类型的最大值
const int INF = std::numeric_limits<int>::max();

// 边的结构体，包含起点u，终点v和权重w
struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

// 图的类，包含顶点数n和边的集合edges
class Graph {
public:
    int n; // 顶点数
    std::vector<Edge> edges; // 边的集合

    // 构造函数，初始化顶点数
    Graph(int n) : n(n) {}

    // 添加边到图中
    void addEdge(int u, int v, int w) {
        edges.emplace_back(u, v, w);
    }

    // 贝尔曼-福特算法实现
    bool bellmanFord(int source, std::vector<int>& distances) {
        // 初始化距离表，除了源点置为0，其余都为INF
        distances.assign(n, INF);
        distances[source] = 0;

        // 进行n-1轮松弛操作，确保找到所有最短路径
        for (int i = 0; i < n - 1; ++i) {
            for (const Edge& e : edges) {
                if (distances[e.u] < INF && distances[e.v] > distances[e.u] + e.w) {
                    distances[e.v] = distances[e.u] + e.w;
                }
            }
        }

        // 检测负权回路：如果第n轮仍然能松弛任何边，说明存在负权回路
        for (const Edge& e : edges) {
            if (distances[e.u] < INF && distances[e.v] > distances[e.u] + e.w) {
                return false; // 存在负权回路
            }
        }

        return true; // 不存在负权回路
    }
};

int main() {
    // 创建一个图的实例
    Graph g(5); // 图中有5个顶点
    g.addEdge(0, 1, -1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 2, 5);
    g.addEdge(3, 1, 1);
    g.addEdge(4, 3, -3);

    std::vector<int> distances;
    if (g.bellmanFord(0, distances)) {
        std::cout << "Vertex\tDistance from Source\n";
        for(int i = 0; i < distances.size(); ++i) {
            std::cout << i << "\t\t" << distances[i] << "\n";
        }
    } else {
        std::cout << "Graph contains negative weight cycle\n";
    }

    return 0;
}

