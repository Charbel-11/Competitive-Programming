#include <bits/stdc++.h>
using namespace std;

struct DSU {
	int disjointSets;
	vector<int> rank, parent;
	stack<pair<int, int>> rankS, parentS;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
		disjointSets = n; rankS.push({ -1,-1 });
	}

	//O(logn)
	int find(int u) { while (u != parent[u]) { u = parent[u]; } return u; }
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rankS.push({ u, rank[u] });
		parentS.push({ v, parent[v] });
		rank[u] += rank[v];	parent[v] = u;
		disjointSets--;
		return true;
	}

	//Goes to the last time we called persist()
	void rollback() {
		while (rankS.top() != pair<int, int>{-1, -1}) {
			auto& p = rankS.top(); rankS.pop();
			rank[p.first] = p.second;
			p = parentS.top(); parentS.pop();
			parent[p.first] = p.second;
			disjointSets++;
		}
		rankS.pop(); 
		if (rankS.empty()) { rankS.push({ -1,-1 }); }
	}

	void persist() {
		rankS.push({ -1,-1 });
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	DSU dsu(n);
	while (m--) {
		string t; cin >> t;
		if (t[0] == 'u') {
			int u, v; cin >> u >> v; u--; v--;
			dsu.merge(u, v);
			cout << dsu.disjointSets << '\n';
		}
		else if (t[0] == 'p') {
			dsu.persist();
		}
		else {
			dsu.rollback();
			cout << dsu.disjointSets << '\n';
		}
	}
}