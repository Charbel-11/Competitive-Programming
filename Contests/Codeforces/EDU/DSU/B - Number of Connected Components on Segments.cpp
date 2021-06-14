#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <stack>
using namespace std;
typedef long long ll;

const int block = 224;			//Set it to sqrt(n)
vector<pair<int, int>> edges;

struct DSU {
	int disjointSets;
	vector<int> rank, parent;
	stack<pair<int, int>> rankS, parentS;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
		disjointSets = n; rankS.push({ -1,-1 });
	}

	int find(const int u) { return parent[u] == u ? u : find(parent[u]); }
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

struct query {
	int L, R, idx;
	query(int l, int r, int i) : L(l), R(r), idx(i) {}

	bool operator<(const query& q2) {
		int b1 = L / block, b2 = q2.L / block;
		if (b1 != b2) { return b1 < b2; }
		return R < q2.R;
	}
};

void add(int i, DSU &dsu) {
	dsu.merge(edges[i].first, edges[i].second);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	edges.resize(m);
	for (auto& x : edges) { cin >> x.first >> x.second; x.first--; x.second--; }

	int t; cin >> t;
	vector<query> queries;
	for (int i = 0; i < t; i++) {
		int l, r; cin >> l >> r; l--; r--;
		queries.push_back(query(l, r, i));
	}
	sort(queries.begin(), queries.end());

	vector<int> ans(t);
	DSU dsu(n);
	int L, R;
	int prevBlock = -1;
	for (auto& q : queries) {
		int curBlock = q.L / block;
		if (q.R < (curBlock+1) * block) {
			while (dsu.rankS.size() > 1) { dsu.rollback(); }
			L = R = q.L; R--;
			while (R < q.R) { add(++R, dsu); }
			ans[q.idx] = dsu.disjointSets;
			continue;
		}

		if (curBlock != prevBlock) {
			prevBlock = curBlock;
			while (dsu.rankS.size() > 1) { dsu.rollback(); }
			L = R = (curBlock + 1) * block; R--;
		}
		while (R < q.R) { add(++R, dsu); }
		dsu.persist();
		while (L > q.L) { add(--L, dsu); }
		ans[q.idx] = dsu.disjointSets;
		dsu.rollback(); L = (curBlock + 1) * block;
	}

	for (auto& x : ans) { cout << x << '\n'; }
}