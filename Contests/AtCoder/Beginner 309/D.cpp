#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v; int w; Edge() {}
    Edge(int _u, int _v, int _w = 1) :
            u(_u), v(_v), w(_w) {}
};

struct Node { vector<Edge> edges; };

struct Graph {
    vector<Node> nodes;
    int n;

    Graph(int _n) : n(_n) { nodes.resize(n); }

    void addEdge(int u, int v) {
        Edge e1(u, v); nodes[u].edges.push_back(e1);
        Edge e2(v, u); nodes[v].edges.push_back(e2);
    }

    vector<int> getDist(int u){
        vector<int> dist(n, -1);
        dist[u] = 0;

        queue<int> q; vector<bool> vis(n, false);
        q.push(u); vis[u] = true;
        while(!q.empty()){
            int cur = q.front(); q.pop();
            for(auto &e : nodes[cur].edges){
                if (!vis[e.v]){
                    vis[e.v] = true; q.push(e.v);
                    dist[e.v] = dist[cur] + 1;
                }
            }
        }
        return dist;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n1, n2, m; cin >> n1 >> n2 >> m;
    Graph g(n1 + n2);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        g.addEdge(u, v);
    }

    auto d1 = g.getDist(0), d2 = g.getDist(n1+n2-1);
    cout << 1 + *max_element(d1.begin(), d1.end()) + *max_element(d2.begin(), d2.end()) << '\n';
}