#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9+7;

struct DSU {
    vector<int> rank, parent;

    DSU(int n) {
        rank.resize(n, 1); parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(const int u) {	return parent[u] == u ? u : (parent[u] = find(parent[u])); }
    int size(int u) { return rank[find(u)]; }

    bool merge(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) { return false; }
        if (rank[u] < rank[v]) { swap(u, v); }
        rank[u] += rank[v];	parent[v] = u;
        return true;
    }
};

ll power(ll x, ll p) {
    ll res = 1; x %= mod;
    for (; p; p >>= 1, x = (x * x) % mod) {
        if (p & 1) { res = (res * x) % mod; }
    }
    return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
    DSU dsu(n); int cc = n;
    for(int i = 0; i < m; i++){
        int u,v; cin >> u >> v; u--; v--;
        if (dsu.merge(u,v)){ cc--; }
    }

    cout << power(2, m-n+cc) << '\n';
}