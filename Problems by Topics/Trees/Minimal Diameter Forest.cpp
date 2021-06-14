//https://codeforces.com/contest/1092/problem/E
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
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
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}
	
	//Finds all diameters and centers (if 2 centers exist it takes any 1) of each tree in a forest
	vector<pair<int, int>> findDiametersAndCenters() {
		vector<pair<int, int>> ans;
		vector<bool> vis1(n, 0), vis2(n, 0);
		vector<int> parent(n, 0);
		for (int i = 0; i < n; i++) {
			if (vis1[i]) { continue; }
			int diameter, d1, d2;
			findDiameter(i, vis1, vis2, parent, diameter, d1, d2);
			int c = findCenter(d2, diameter, parent);
			ans.push_back({ diameter, c });
		}
		return move(ans);
	}
	
	//returns {endpoint, dist}
	pair<int, int> bfs(int u, vector<bool> &visited, vector<int> &parent) {
		queue<pair<int, int>> Q; visited[u] = true;	
		int dist = 0; Q.push({ u, 0 });
		while (!Q.empty()) {
			u = Q.front().first; dist = Q.front().second; Q.pop();
			for (auto &e : nodes[u].edges) {
				if (visited[e.v]) { continue; }
				visited[e.v] = true; Q.push({ e.v, dist + 1 });
				parent[e.v] = u;
			}
		}
		return { u, dist };
	}

	void findDiameter(int u, vector<bool> &vis1, vector<bool>& vis2, vector<int> &parent,
		int &diameter, int &d1, int &d2) {
		d1 = bfs(u, vis1, parent).first;
		auto p = bfs(d1, vis2, parent);
		d2 = p.first; diameter = p.second;
	}
	//Can be modified to return both centers if diameter is even
	//u should be the endpoint of the diameter which is not the root
	int findCenter(int u, int diameter, vector<int> &parent) {
		diameter >>= 1;
		while (diameter--) { u = parent[u]; }
		return u;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	tree t(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	vector<pair<int, int>> DnC = t.findDiametersAndCenters();
	sort(DnC.rbegin(), DnC.rend());
	int res = DnC[0].first;
	if (DnC.size() >= 2) { res = max(res, (DnC[0].first + 1) / 2 + (DnC[1].first + 1) / 2 + 1); }
	if (DnC.size() >= 3) { res = max(res, (DnC[1].first + 1) / 2 + (DnC[2].first + 1) / 2 + 2); }

	cout << res << '\n';
	for (int i = 1; i < DnC.size(); i++) {
		cout << DnC[i].second + 1 << ' ' << DnC[0].second + 1 << '\n';
	}
}