#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node {
    int a, b; ll val = 0;
    vector<int> edges;
    node() {}
};

struct BipartiteGraph {
    vector<node> nodes; int n, m;
    vector<bool> Z, vis;
    vector<int> unMatched, match;

    BipartiteGraph(int _n, int _m) : n(_n), m(_m),
                                     nodes(_n + _m), Z(_n + _m, 0), match(_n + _m, -1), vis(_n + _m, 0) {}

    void addEdge(int u, int v) {
        nodes[u].edges.push_back(v);
        nodes[v].edges.push_back(u);
    }

    bool augment(int v) {
        if (v == -1) { return 1; }
        if (vis[v]) { return 0; }
        vis[v] = 1; for (auto &e : nodes[v].edges)
            if (augment(match[e])) {
                match[e] = v; match[v] = e;
                return 1;
            }
        return 0;
    }

    int maxMatching() {
        int w = 0;
        for (int x = 0; x < n; x++) {
            if (match[x] != -1) { continue; }
            for (auto &e : nodes[x].edges)
                if (match[e] == -1) {
                    match[e] = x; match[x] = e;
                    w++; break;
                }
        }
        for (int i = 0; i < n; i++) {
            if (match[i] != -1) { continue; }
            for (int j = 0; j < n; j++) { vis[j] = 0; }
            w += augment(i);
        }
        return w;
    }

    void printMaxMatching() {
        int K = maxMatching();
        if(K != n) { cout << "impossible\n"; return; }
        for (int i = 0; i < n; i++) {
            int a = nodes[i].a, b = nodes[i].b; ll val = nodes[match[i]].val;
            string operation = a + b == val ? " + " : a - b == val ? " - " : " * ";
            cout << nodes[i].a << operation << nodes[i].b << " = " << nodes[match[i]].val << '\n';
        }
    }
};

vector<pair<int, int>> v;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n; vector<ll> val;
    for(int i = 0; i < n; ++i){
        int a, b; cin >> a >> b;
        v.emplace_back(a, b);
        val.push_back(a + b);
        val.push_back(a - b);
        val.push_back(1ll * a * b);
    }

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    BipartiteGraph G(n, val.size());

    for(int i = 0; i < n; i++){
        G.nodes[i].a = v[i].first;
        G.nodes[i].b = v[i].second;
    }
    for(int i = n; i < n + val.size(); i++){
        G.nodes[i].val = val[i - n];
    }

    for(int i = 0; i < n; i++){
        int a = v[i].first, b = v[i].second;
        int add = lower_bound(val.begin(), val.end(), a + b) - val.begin();
        int sub = lower_bound(val.begin(), val.end(), a - b) - val.begin();
        int mul = lower_bound(val.begin(), val.end(), 1ll * a * b) - val.begin();
        G.addEdge(i, n + add);
        G.addEdge(i, n + sub);
        G.addEdge(i, n + mul);
    }
    G.printMaxMatching();
}