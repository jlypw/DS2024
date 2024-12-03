#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <climits>
#include <functional>

using namespace std;

// ͼ�����ݽṹ
class Graph {
public:
    int V; // ͼ�Ľڵ���
    vector<list<int> > adj; // �ڽӱ��ʾ��ͼ

    Graph(int V); // ���캯������ʼ���ڵ���
    void addEdge(int u, int v); // ��������
    void addDirectedEdge(int u, int v); // ��������

    void BFS(int start); // ������ȱ���
    void DFS(int start); // ������ȱ���
    void Dijkstra(int start); // ���·���㷨��Dijkstra��
    void Prim(); // ��С�������㷨��Prim��
};

// ͼ�Ĺ��캯��
Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

// ��������
void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// ��������
void Graph::addDirectedEdge(int u, int v) {
    adj[u].push_back(v);
}

// ������ȱ�����BFS��
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

// ������ȱ�����DFS��
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

// Dijkstra �㷨�����·����
void Graph::Dijkstra(int start) {
    vector<int> dist(V, INT_MAX);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v : adj[u]) {
            int weight = 1; // ���ڼ���Ȩͼ��Ȩֵ��Ϊ1
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

// Prim �㷨����С��������
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
            int weight = 1; // ������Ȩͼ��ȨֵΪ1
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
    // ����ͼ����
    Graph g(5);

    // ��������
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    // ������ȱ�����BFS��
    cout << "BFS starting from node 0: ";
    g.BFS(0);

    // ������ȱ�����DFS��
    cout << "DFS starting from node 0: ";
    g.DFS(0);

    // Dijkstra �㷨�����·����
    g.Dijkstra(0);

    // Prim �㷨����С��������
    g.Prim();

    return 0;
}

