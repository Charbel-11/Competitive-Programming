#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
    vector<node> nodes;
    vector<int> values;
    vector<bool> covered;
    int root, n;

    tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); values.resize(n, 0); covered.resize(n, 0); }

    void add_edge(int u, int v) {
        edge e1(u, v), e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }

    void propValues(int u, int p, int valLeft){
        valLeft = max(valLeft, values[u]);
        if (valLeft > 0){ covered[u] = true; }
        for(auto &e : nodes[u].edges){
            if (e.v == p){ continue; }
            propValues(e.v, u, valLeft - 1);
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m; cin >> n >> m;
    tree t(n);
    for (int i = 1; i < n; i++) {
        int v; cin >> v; v--;
        t.add_edge(i, v);
    }

    for(int i = 0; i < m; i++){
        int x, y; cin >> x >> y; x--; y++;
        t.values[x] = max(t.values[x], y);
    }
    t.propValues(0, -1, 0);

    int ans = 0;
    for(auto b : t.covered){ ans += b; }
    cout << ans << '\n';
}