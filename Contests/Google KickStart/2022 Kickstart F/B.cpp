#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> depthCnt;

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
    vector<node> nodes;
    int root, n;

    tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

    void add_edge(int u, int v) {
        edge e1(u, v), e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }

    void dfs(int u, int p, int d){
        depthCnt[d]++;
        for(auto& e : nodes[u].edges){
            if (e.v == p){ continue; }
            dfs(e.v, u, d+1);
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        int n, q; cin >> n >> q;

        depthCnt.clear(); depthCnt.resize(n, 0);
        tree t(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v; cin >> u >> v; u--; v--;
            t.add_edge(u, v);
        }

        t.dfs(0, -1, 0);

        int added = q;
        while(q--){ int tmp; cin >> tmp; }

        int ans = 0;
        for(int i = 0; i < n; i++){
            if (depthCnt[i] <= added){
                added -= depthCnt[i];
                ans += depthCnt[i];
            }
            else{ break; }
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}
