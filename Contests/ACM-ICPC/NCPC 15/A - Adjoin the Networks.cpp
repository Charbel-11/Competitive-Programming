#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
#include <cmath>
#include <string>
using namespace std;
typedef long long ll;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> dist;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); dist.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.emplace_back(e1);
		edge e2(v, u); nodes[v].edges.emplace_back(e2);
	}

	void dfs(int u, int p, int &maxDist, int &idx, vector<bool> &vis) {
		vis[u] = 1;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dist[e.v] = dist[u] + 1;
			if (dist[e.v] > maxDist) { maxDist = dist[e.v]; idx = e.v; }
			dfs(e.v, u, maxDist, idx, vis);
		}
	}

	vector<int> findAllDiameters() {
		vector<bool> vis(n, 0);
		vector<int> ans;
		for (int i = 0; i < n; i++) {
			if (!vis[i]) { 			
				int diameter = 0, idx = i;
				dist[i] = 0; dfs(i, -1, diameter, idx, vis);
				dist[idx] = 0; dfs(idx, -1, diameter, idx, vis);
				ans.push_back(diameter);
			}
		}
		return move(ans);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, l; cin >> n >> l;
	tree finalT(n);
	for (int i = 0; i < l; i++) {
		int u, v; cin >> u >> v;
		finalT.add_edge(u, v);
	}

	vector<int> d = finalT.findAllDiameters();
	sort(d.rbegin(), d.rend());
	
	int ans = d[0];
	if (d.size() >= 2) { ans = max(ans, 1 + (d[0] + 1) / 2 + (d[1] + 1) / 2); }
	if (d.size() >= 3) { ans = max(ans, 2 + (d[1] + 1) / 2 + (d[2] + 1) / 2); }

	cout << ans << '\n';
}