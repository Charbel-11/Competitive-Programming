#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans = 0;

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct Tree {
    vector<node> nodes; vector<ll> curP;
    vector<bool> dead; vector<int> sz;
    int n, k1, k2;

    Tree(int _n, int _k1, int _k2) : n(_n), k1(_k1), k2(_k2) {
        nodes.resize(n); sz.resize(n, 1);
        dead.resize(n, false); curP.resize(k2 + 2, 0);
    }

    void add_edge(int u, int v) {
        edge e1(u, v); edge e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
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

        curP[0] = 1; ll curCnt = 0;
        for (auto& e : nodes[c].edges) {
            if (dead[e.v]) { continue; }
            addNeeded(e.v, c, 1, curCnt);
            dfs(e.v, c, 1, curCnt);
        }
        for(int i = 0; i <= k2 && curP[i]; i++){
            curP[i] = 0;
        }

        for (auto& e : nodes[c].edges) {
            if (!dead[e.v]) { CDRec(e.v); }
        }
    }

    void dfs(int u, int p, int level, ll& curCnt) {
        if (level > k2){ return; }
        curP[level]++;
        if (level >= k1 && level <= k2){ curCnt++; }
        for (auto& e : nodes[u].edges) {
            if (e.v == p || dead[e.v]) { continue; }
            dfs(e.v, u, level + 1, curCnt);
        }
    }
    void addNeeded(int u, int p, int level, ll& curCnt) {
        if (level > k2) { return; }
        int lo = max(0, k1 - level), hi = k2 - level;
        ll diff = -curP[hi + 1];
        if (k1 >= level){ diff += curP[lo]; };
        curCnt += diff; ans += curCnt;
        for (auto& e : nodes[u].edges) {
            if (e.v == p || dead[e.v]) { continue; }
            addNeeded(e.v, u, level + 1, curCnt);
        }
        curCnt -= diff;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, k1, k2; cin >> n >> k1 >> k2;
    Tree t(n, k1, k2);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        t.add_edge(u, v);
    }
    t.centroidDecomposition();
    cout << ans << '\n';
}