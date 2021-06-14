#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v){}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; vector<bool> visited;
	vector<int> height; int n;
	graph(int _n) : n(_n) { nodes.resize(n); height.resize(n, 0); visited.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v);
		nodes[u].edges.push_back(e1);
	}

	int dfs(int i) {
		if (visited[i]) { return height[i]; }
		
		int cur = 1;
		for (auto &e : nodes[i].edges) {
				cur = max(cur, 1 + dfs(e.v));
		}

		height[i] = cur; visited[i] = true;
		return cur;
	}
};

int main() {
	int n, k; cin >> n >> k;
	graph g(n);

	map<pair<int, int>, int> freq;
	for (int m = 0; m < k; m++) {
		vector<int> cur(n);
		for (auto &x : cur) { cin >> x; x--; }
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				freq[{cur[i], cur[j]}]++;
			}
		}
	}

	for (auto &p : freq) {
		if (p.second >= k) {
			g.add_edge(p.first.first, p.first.second);
		}
	}

	int res = 1;

	for (int i = 0; i < n; i++) {
		res = max(res, g.dfs(i));
	}

	cout << res << endl;
}