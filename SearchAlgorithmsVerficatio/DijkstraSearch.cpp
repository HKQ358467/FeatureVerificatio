#include <iostream>
#include <vector>
#include <limits> // 用于表示无穷大
#include <queue>  // 用于实现优先队列

using namespace std;

// 定义无穷大
const int INF = numeric_limits<int>::max();

// 边的结构体
struct Edge
{
    int to;     // 边的目标顶点
    int weight; // 边的权重
    Edge(int t, int w) : to(t), weight(w)
    {}
};

// 优先队列的元素，需要进行比较的
struct Node
{
    int vertex;
    int distance;

    bool operator<(const Node &node) const
    {
        return distance > node.distance; // 最小堆
    }
};

// 迪杰斯特拉算法函数
void dijkstra(const vector<vector<Edge>> &graph, int src)
{
    int n = graph.size();
    vector<int> dist(n, INF); // 距离数组，初始化为无穷大
    vector<bool> visited(n, false); // 访问数组，初始化为未访问

    priority_queue<Node> pq; // 优先队列，用于选择最短未访问节点
    pq.push({src, 0}); // 放入源点，距离为0
    dist[src] = 0; // 源点到自身的最短距离是0

    while (!pq.empty())
    {
        // 选择未访问的最小距离顶点
        int u = pq.top().vertex;
        pq.pop();

        // 若已访问则跳过
        if (visited[u])
            continue;

        // 标记为已访问
        visited[u] = true;

        // 遍历所有邻接顶点
        for (auto &edge: graph[u])
        {
            int v = edge.to;
            int weight = edge.weight;

            // 如果找到更短的路径，则更新
            if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({v, dist[v]});
            }
        }
    }

    // 打印结果
    cout << "Vertex Distance from Source" << endl;
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << (dist[i] == INF ? -1 : dist[i]) << endl;
}

int main()
{
    // 构建图的示例
    int V = 5;
    vector<vector<Edge>> graph(V);

    // 添加边
    graph[0].push_back(Edge(1, 9));
    graph[0].push_back(Edge(2, 6));
    graph[0].push_back(Edge(3, 5));
    graph[0].push_back(Edge(4, 3));

    graph[1].push_back(Edge(2, 2));
    graph[2].push_back(Edge(3, 4));

    // 调用迪杰斯特拉算法
    dijkstra(graph, 0);

    return 0;
}
