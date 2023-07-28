#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
    int u, v; ll w; edge() {}
    edge(int _u, int _v, ll _w) :
            u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
    vector<node> nodes; int n;
    graph(int _n) : n(_n) { nodes.resize(n); }

    void addEdge(int u, int v, ll w) {
        edge e1(u, v, w); nodes[u].edges.push_back(e1);
    }
};

bool dfs(int u, graph& g, map<int, ll>& pos){
    for(auto& e : g.nodes[u].edges) {
        if (pos.count(e.v)){
            if (pos[e.v] != pos[u] + e.w){
                return false;
            }
        }
        else {
            pos[e.v] = pos[u] + e.w;
            if (!dfs(e.v, g, pos)) { return 0; }
        }
    }
    return 1;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while(t--){
        int n, m; cin >> n >> m;
        graph g(n);
        for(int i = 0; i < m; i++){
            ll a, b, d; cin >> a >> b >> d; a--; b--;
            g.addEdge(b, a, d);
            g.addEdge(a, b, -d);
        }

        bool OK = true; map<int, ll> pos;
        for(int idx = 0; idx < n; idx++){
            if (pos.count(idx)){ continue; }
            pos[idx] = 0;
            OK = OK && dfs(idx, g, pos);
        }

        cout << (OK ? "YES" : "NO") << '\n';
    }
}