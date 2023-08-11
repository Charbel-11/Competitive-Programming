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

struct query {
	int type, t1, t2, u, v;
	query(int tp, int t1, int t2, int u, int v) : type(tp), t1(t1), t2(t2), u(u), v(v) {}
};

struct DynamicGraph {
	DSU dsu;
	int n, t = 0;
	vector<int> ans;
	vector<query> queries;
	map<pair<int, int>, int> start;
	DynamicGraph(int n) : n(n), ans(n, -1), dsu(n) {}

	void link(int u, int v) {
		if (u > v) { swap(u, v); }
		if (start.count({ u, v }) == 0) {
			start[{u, v}] = t++;
		}
	}

	void cut(int u, int v) {
		if (u > v) { swap(u, v); }
		queries.push_back(query(1, start[{u, v}], t++, u, v));
		start.erase({ u, v });
	}

	void getNumOfComponents() {
		queries.push_back(query(2, t, t, -1, -1));
		t++;
	}

	void areConnected(int u, int v) {
		queries.push_back(query(3, t, t, u, v));
		t++;
	}

	void fillAnswers() {
		ans = vector<int>(t, -1);
		for (auto& it : start) {
			queries.push_back(query(1, it.second, t, it.first.first, it.first.second));
		}
		fillAnswersRec(0, t, queries);
	}

	void fillAnswersRec(int t1, int t2, vector<query>& queriesInRange) {
		if (t1 == t2) {
			dsu.persist();
			for (auto& query : queriesInRange) {
				if (query.type == 1 && query.t1 <= t1 && t2 <= query.t2) {
					dsu.merge(query.u, query.v);
				}
			}
			for (auto& query : queriesInRange) {
				if (query.t1 == t1 && query.t2 == t2) {
					if (query.type == 2) {
						ans[query.t1] = dsu.disjointSets;
					}
					else if (query.type == 3) {
						ans[query.t1] = (dsu.find(query.u) == dsu.find(query.v));
					}
				}
			}
			dsu.rollback();
			return;
		}

		dsu.persist();
		vector<query> nextQueries;
		for (auto& query : queriesInRange) {
			if (query.type == 1 && query.t1 <= t1 && t2 <= query.t2) {
				dsu.merge(query.u, query.v);
			}
			else if ((query.type == 1 && !(query.t1 > t2 || query.t2 < t1)) || (query.type != 1 && query.t1 >= t1 && query.t2 <= t2)) {
				nextQueries.push_back(query);
			}
		}
		int mid = (t1 + t2) / 2;
		fillAnswersRec(t1, mid, nextQueries);
		fillAnswersRec(mid + 1, t2, nextQueries);
		dsu.rollback();
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	DynamicGraph g(n);
	for (int i = 0; i < m; i++) {
		char c; cin >> c;
		if (c == '+') {
			int u, v; cin >> u >> v; u--, v--;
			g.link(u, v);
		}
		else if (c == '-') {
			int u, v; cin >> u >> v; u--, v--;
			g.cut(u, v);
		}
		else {
			g.getNumOfComponents();
		}
	}

	g.fillAnswers();
	for (auto& x : g.ans) {
		if (x >= 0) { cout << x << '\n'; }
	}
}