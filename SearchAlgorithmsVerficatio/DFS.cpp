#include <iostream>
#include <list>
#include <vector>

// 类Graph用于表示图
class Graph {
public:
    Graph(int V);               // 构造函数
    void addEdge(int v, int w); // 用于添加边的函数
    void DFS(int v);            // 用于深度优先搜索的函数

private:
    int V;                           // 图的顶点数
    std::vector<bool> visited;       // 记录顶点是否被访问过的向量
    std::list<int>* adj;             // 邻接表
    void DFSUtil(int v);             // DFS的辅助函数
};

Graph::Graph(int V) {
    this->V = V;                // 初始化顶点数
    adj = new std::list<int>[V]; // 创建顶点的邻接表
    visited.resize(V, false);    // 将所有顶点初始化为未访问
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // 在v的邻接表中添加一个连接到w的边
}

// DFS遍历的辅助函数
void Graph::DFSUtil(int v) {
    // 标记当前节点为已访问并打印
    visited[v] = true;
    std::cout << v << " ";

    // 递归地访问所有未标记的邻居
    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            DFSUtil(neighbor);
        }
    }
}

// DFS遍历的主函数
void Graph::DFS(int v) {
    // 清除先前的访问记录
    std::fill(visited.begin(), visited.end(), false);
    // 从顶点v开始递归遍历
    DFSUtil(v);
}

// 主函数
int main() {
    // 创建一个图实例
    Graph g(4);

    // 向图中添加边
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    // 从顶点2开始深度优先搜索
    std::cout << "Depth First Traversal (starting from vertex 2) \n";
    g.DFS(2);

    return 0;
}
