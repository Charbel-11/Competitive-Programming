#include <iostream>
#include <set>
#include <vector>
#include <numeric>
using namespace std;

//We store the elements of each component
//We use a set if ordering is needed, otherwise a vector is enough
struct DSU {
	vector<int> parent, exp, add;
	vector<set<int>> children;

	DSU(int n) {
		parent.resize(n); children.resize(n);
		exp.resize(n, 0); add.resize(n, 0);
		iota(parent.begin(), parent.end(), 0);
		for (int i = 0; i < n; i++) { children[i].insert(i); }
	}

	int find(int u) { return parent[u]; }
	int size(int u) { return children[parent[u]].size(); }

	bool merge(int u, int v) {
		u = parent[u]; v = parent[v]; if (u == v) { return false; }
		if (size(u) < size(v)) { swap(u, v); }
		set<int>& min = children[v], & max = children[u];

		for (auto& x : min) {
			parent[x] = u; max.insert(x);
			exp[x] += add[v] - add[u];
		}
		add[v] = 0;	min.clear(); 
		return true;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	DSU dsu(n);
	while (m--) {
		string t; cin >> t;
		if (t[0] == 'a') {
			int x, v; cin >> x >> v; x--;
			x = dsu.find(x);
			dsu.add[x] += v;
		}
		else if (t[0] == 'j') {
			int u, v; cin >> u >> v; u--; v--;
			dsu.merge(u, v);
		}
		else {
			int x; cin >> x; x--;
			cout << dsu.exp[x] + dsu.add[dsu.find(x)] << '\n';
		}
	}
}