#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<int> a(n); for(auto &x : a){ cin >> x; x--; }
        vector<int> b(n); for(auto &x : b){ cin >> x; x--; }

        ll ans = 1; DSU dsu(n);
        vector<bool> used(n, false);
        for(int i = 0; i < n; i++){
            if (dsu.find(a[i]) == dsu.find(b[i])){ continue; }
            dsu.merge(a[i], b[i]); used[i] = true;
        }

        map<int, int> m;
        for(int i = 0; i < n; i++){
            if (used[i]){ continue; }
            int root = dsu.find(a[i]);
            m[root]++;
            if (m[root] > 1){ ans = 0; break; }

            if (a[i] == b[i]){ ans *= n; ans %= mod; }
            else{ ans *= 2; ans %= mod; }
        }

        cout << ans << '\n';
	}
}