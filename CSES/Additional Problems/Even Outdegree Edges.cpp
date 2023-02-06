#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> ans;

struct Edge {
    int u, v, id; Edge() {}
    Edge(int _u, int _v, int _id) :
            u(_u), v(_v), id(_id){}
};

struct Node { int outDeg = 0; vector<Edge> edges; };

struct Graph {
    vector<Node> nodes;
    int n;

    Graph(int _n) : n(_n) { nodes.resize(n); }

    void addEdge(int u, int v, int id) {
        Edge e1(u, v, id); nodes[u].edges.push_back(e1);
        Edge e2(v, u, id); nodes[v].edges.push_back(e2);
    }

    void dfs(int u, int p, vector<bool>& vis){
        vis[u] = true;
        for(auto &e : nodes[u].edges){
            if (e.v == p){ continue; }
            if (vis[e.v]){
                if (ans[e.id].first == -1){
                    ans[e.id] = {e.v, e.u};
                    nodes[e.v].outDeg++;
                }
            }
            else{
                dfs(e.v, u, vis);
                if (nodes[e.v].outDeg % 2 == 0){
                    ans[e.id] = {e.u, e.v};
                    nodes[u].outDeg++;
                }
                else{
                    ans[e.id] = {e.v, e.u};
                    nodes[e.v].outDeg++;
                }
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m; cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        g.addEdge(u, v, i);
    }

    ans.resize(m, {-1,-1});
    vector<bool> vis(n, false);
    for(int i = 0; i < n; i++) {
        if (!vis[i]) {
            g.dfs(i, -1, vis);
            if (g.nodes[i].outDeg % 2 == 1){
                cout << "IMPOSSIBLE" << '\n';
                return 0;
            }
        }
    }

    for(auto &p : ans){ cout << p.first + 1 << " " << p.second + 1 << '\n'; }
}