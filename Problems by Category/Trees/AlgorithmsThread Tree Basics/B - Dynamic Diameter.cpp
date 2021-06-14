#include <iostream>
#include <vector>
#include <set>
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

	void dfs(int u, int p, vector<int> &dist) {
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dist[e.v] = dist[u] + 1;
			dfs(e.v, u, dist);
		}
	}

	void findDiameter(int &diameter, set<int> &s) {
		diameter = 0; int d1 = root, d2 = root;
		vector<int> dist1(n, -1), dist2(n, -1);

		dist1[root] = 0; dfs(root, -1, dist1);
		for (int i = 0; i < n; i++) {
			if (dist1[i] > diameter) { diameter = dist1[i]; d1 = i; }
		}
		s.insert(d1);

		dist2[d1] = 0; dfs(d1, -1, dist2);
		for (int i = 0; i < n; i++) {
			if (dist2[i] > diameter) {
				diameter = dist2[i]; d2 = i;
				s.clear(); s.insert(d1); s.insert(i);
			}
			else if (dist2[i] == diameter) { s.insert(i); }
		}

		vector<int> dist(n, -1);
		dist[d2] = 0; dfs(d2, -1, dist);
		for (int i = 0; i < n; i++) {
			if (dist[i] == diameter) { s.insert(i); }
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	int diameter; set<int> nodes;
	t.findDiameter(diameter, nodes);

	for (int i = 0; i < n; i++) {
		if (nodes.count(i)) { cout << diameter + 1 << '\n'; }
		else { cout << diameter << '\n'; }
	}
}