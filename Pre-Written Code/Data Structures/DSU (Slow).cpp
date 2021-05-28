#include <iostream>
#include <set>
#include <vector>
#include <numeric>
using namespace std;

//We store the elements of each component in children[compRoot]
//We use a set if ordering is needed, otherwise a vector is enough
struct DSU {
	vector<int> parent;
	vector<set<int>> children;

	DSU(int n) {
		parent.resize(n); children.resize(n);
		iota(parent.begin(), parent.end(), 0);
		for (int i = 0; i < n; i++) { children[i].insert(i); }
	}

	int find(int u) { return parent[u]; }
	int size(int u) { return children[parent[u]].size(); }

	bool merge(int u, int v) {
		u = parent[u]; v = parent[v]; if (u == v) { return false; }
		if (size(u) < size(v)) { swap(u, v); }
		set<int> &min = children[v], &max = children[u];
	
		for (auto &x : min) {
			parent[x] = u; max.insert(x);
			//Do something with x
		}
		min.clear(); return true;
	}
};