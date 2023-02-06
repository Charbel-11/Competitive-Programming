#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> ans;

struct Edge {
    int u, v, id; Edge() {}
    Edge(int _u, int _v, int _id) :
            u(_u), v(_v), id(_id){}
};

struct Node { vector<Edge> edges; };

struct Graph {
    vector<Node> nodes;
    int n; bool hasBridge = false;

    Graph(int _n) : n(_n) { nodes.resize(n); }

    void addEdge(int u, int v, int id) {
        Edge e1(u, v, id);
        nodes[u].edges.push_back(e1);
        Edge e2(v, u, id);
        nodes[v].edges.push_back(e2);
    }

    //tin[u] = discovery time of u
    //low[u] = lowest discovery time of a reachable node
    void bridgeDFS(int cur, int p, vector<bool> &vis, vector<int> &low, vector<int> &tin, int &timer) {
        vis[cur] = true; tin[cur] = low[cur] = timer++;
        for (auto &e : nodes[cur].edges) {
            if (e.v == p) { continue; }
            if (vis[e.v]) { low[cur] = min(low[cur], tin[e.v]); continue; }

            bridgeDFS(e.v, cur, vis, low, tin, timer);
            low[cur] = min(low[cur], low[e.v]);
            if (low[e.v] > tin[cur]) {  hasBridge = true; return; }
        }
    }

    void dfs(int u, int p, vector<bool>& vis){
        vis[u] = true;
        for(auto &e : nodes[u].edges){
            if (e.v == p){ continue; }
            if (vis[e.v]){
                if (ans[e.id].first == -1){
                    ans[e.id] = {e.u, e.v};
                }
            }
            else{
                dfs(e.v, u, vis);
                ans[e.id] = {e.u, e.v};
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

    vector<bool> vis(n, false);
    vector<int> low(n), tin(n); int timer;
    g.bridgeDFS(0, -1, vis, low, tin, timer);
    if (g.hasBridge){
        cout << "IMPOSSIBLE\n"; return 0;
    }
    for(int i = 0; i < n; i++) {
        if (!vis[i]){
            cout << "IMPOSSIBLE\n"; return 0;
        }
    }

    vis.assign(n, false);
    ans.resize(m, {-1,-1});
    g.dfs(0, -1, vis);

    for(auto &p : ans){ cout << p.first + 1 << " " << p.second + 1 << '\n'; }
}