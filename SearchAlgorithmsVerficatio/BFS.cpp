#include <iostream>
#include <list>
#include <queue>
#include <vector>

// Graph类代表一个有向图
class Graph {
public:
    Graph(int V);               // 构造函数
    void addEdge(int v, int w); // 添加边到图中
    void BFS(int s);            // 从给定源点s开始的BFS

private:
    int V;                       // 顶点的数量
    std::list<int>* adj;         // 邻接表
};

Graph::Graph(int V) {
    this->V = V;
    adj = new std::list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // 将w添加到v的链表中
}

void Graph::BFS(int s) {
    // 所有顶点最初都未访问过
    std::vector<bool> visited(V, false);

    // 创建一个队列用于BFS
    std::queue<int> queue;

    // 标记当前节点为已访问并入队
    visited[s] = true;
    queue.push(s);

    // 当队列非空时继续搜索
    while (!queue.empty()) {
        // 从队列前面移除一个顶点并打印它
        s = queue.front();
        std::cout << s << " ";
        queue.pop();

        // 获取所有邻接顶点
        for (auto i = adj[s].begin(); i != adj[s].end(); ++i) {
            // 如果一个邻接顶点未访问过，将其标记为已访问并入队
            if (!visited[*i]) {
                visited[*i] = true;
                queue.push(*i);
            }
        }
    }
}

// 主函数
int main() {
    // 创建一个图的实例
    Graph g(4);

    // 向图中添加边
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    // 从顶点2开始进行广度优先搜索
    std::cout << "Following is Breadth First Traversal "
              << "(starting from vertex 2) \n";
    g.BFS(2);

    return 0;
}
