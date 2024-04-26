#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
    vector<node> nodes;
    vector<int> dp;
    int n;

    tree(int _n) : n(_n) { nodes.resize(n); dp.resize(n, -1); }

    void add_edge(int u, int v) {
        edge e1(u, v), e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }

    void dfs(int u, int p){
        int sumChild = 0;
        for(auto &e : nodes[u].edges){
            if (e.v == p){ continue; }
            dfs(e.v, u);
            sumChild += dp[e.v];
        }

        if (sumChild == 0){ dp[u] = 1; }
        else { dp[u] = sumChild-1; }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    tree t(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        t.add_edge(u, v);
    }

    t.dfs(0, -1);

    cout << (t.dp[0] != 0 ? "Alice" : "Bob") << '\n';
}