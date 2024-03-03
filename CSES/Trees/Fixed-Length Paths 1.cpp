#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans = 0;

struct edge {
    int v; edge() {}
    edge(int _v) : v(_v) {}
};

struct node { vector<edge> edges; };

struct Tree {
    vector<node> nodes;
    vector<int> sz, curP;
    vector<bool> dead;
    int n, k;

    Tree(int _n, int _k = 0) : n(_n), k(_k) {
        nodes.resize(n); sz.resize(n, 1);
        curP.resize(k + 1, 0); dead.resize(n, false);
    }

    void add_edge(int u, int v) {
        nodes[u].edges.emplace_back(v);
        nodes[v].edges.emplace_back(u);
    }

    void centroidDecomposition() { CDRec(0); }

    void getSize(int u, int p) {
        sz[u] = 1;
        for (auto& e : nodes[u].edges) {
            if (e.v == p || dead[e.v]) { continue; }
            getSize(e.v, u); sz[u] += sz[e.v];
        }
    }
    int getCentroid(int u, int p, int subtreeN) {
        for (auto e : nodes[u].edges) {
            if (e.v == p || dead[e.v]) { continue; }
            if (sz[e.v] > subtreeN / 2) { return getCentroid(e.v, u, subtreeN); }
        }
        return u;
    }

    void CDRec(int start) {
        getSize(start, -1);
        int c = getCentroid(start, -1, sz[start]);
        dead[c] = true;

        curP[0] = 1;
        for (auto& e : nodes[c].edges) {
            if (dead[e.v]) { continue; }
            addNeeded(e.v, c, 1);
            dfs(e.v, c, 1);
        }
        for(int i = 0; i <= k && curP[i]; i++){
            curP[i] = 0;
        }

        for (auto& e : nodes[c].edges) {
            if (!dead[e.v]) { CDRec(e.v); }
        }
    }

    void dfs(int u, int p, int level) {
        if (level > k){ return; }
        curP[level]++;
        for (auto& e : nodes[u].edges) {
            if (e.v == p || dead[e.v]) { continue; }
            dfs(e.v, u, level + 1);
        }
    }
    void addNeeded(int u, int p, int level) {
        if (level > k) { return; }
        ans += curP[k - level];
        for (auto& e : nodes[u].edges) {
            if (e.v == p || dead[e.v]) { continue; }
            addNeeded(e.v, u, level + 1);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, k; cin >> n >> k; Tree t(n, k);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        t.add_edge(u, v);
    }
    t.centroidDecomposition();
    cout << ans << '\n';
}
