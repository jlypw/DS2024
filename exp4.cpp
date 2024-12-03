#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <climits>
#include <functional>

using namespace std;

// 图的数据结构
class Graph {
public:
    int V; // 图的节点数
    vector<list<int> > adj; // 邻接表表示的图

    Graph(int V); // 构造函数，初始化节点数
    void addEdge(int u, int v); // 添加无向边
    void addDirectedEdge(int u, int v); // 添加有向边

    void BFS(int start); // 广度优先遍历
    void DFS(int start); // 深度优先遍历
    void Dijkstra(int start); // 最短路径算法（Dijkstra）
    void Prim(); // 最小生成树算法（Prim）
};

// 图的构造函数
Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

// 添加无向边
void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// 添加有向边
void Graph::addDirectedEdge(int u, int v) {
    adj[u].push_back(v);
}

// 广度优先遍历（BFS）
void Graph::BFS(int start) {
    vector<bool> visited(V, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

// 深度优先遍历（DFS）
void Graph::DFS(int start) {
    vector<bool> visited(V, false);
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();
        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";
        }

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                s.push(neighbor);
            }
        }
    }
    cout << endl;
}

// Dijkstra 算法（最短路径）
void Graph::Dijkstra(int start) {
    vector<int> dist(V, INT_MAX);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v : adj[u]) {
            int weight = 1; // 对于简单无权图，权值设为1
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest distances from node " << start << ": ";
    for (int i = 0; i < V; i++) {
        cout << (dist[i] == INT_MAX ? -1 : dist[i]) << " ";
    }
    cout << endl;
}

// Prim 算法（最小生成树）
void Graph::Prim() {
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;

        for (int v : adj[u]) {
            int weight = 1; // 对于无权图，权值为1
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    cout << "Edges in the Minimum Spanning Tree: " << endl;
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << endl;
    }
}

int main() {
    // 创建图对象
    Graph g(5);

    // 添加无向边
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    // 广度优先遍历（BFS）
    cout << "BFS starting from node 0: ";
    g.BFS(0);

    // 深度优先遍历（DFS）
    cout << "DFS starting from node 0: ";
    g.DFS(0);

    // Dijkstra 算法（最短路径）
    g.Dijkstra(0);

    // Prim 算法（最小生成树）
    g.Prim();

    return 0;
}

