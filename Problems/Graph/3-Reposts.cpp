#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

struct edge {
	int u, v;
	edge(int _u, int _v) {
		u = _u; v = _v;
	}
};

struct node {
	vector<edge> edges;
	node() {}
};

struct graph{
	vector<node> nodes;
	vector<bool> visited;
	vector<int> heights;

	graph(int n) { nodes.resize(n); visited.resize(n, 0); heights.resize(n, 1); }

	void add_edge(int u, int v) {
		edge e(u,v);
		nodes[u].edges.push_back(e);
	}

	int dfs(int u) {
		visited[u] = true;
		int h = 1;
		for (auto &e : nodes[u].edges) {
			if (visited[e.v]) { 
				h = max(h, 1 + heights[e.v]); 
				continue; 
			}
			h = max(h, 1 + dfs(e.v));
		}
		return heights[u] = h;
	}
};

void lower(string &s) {
	for (auto &x : s) { 
		if (x < 'a') { x = x - 'A' + 'a'; }		//'A' is before 'a'
	}
}

int main() {
	int n; cin >> n;
	graph g(2 * n + 1);

	map<string, int> m; int cnt = 0;
	for (int i = 0; i < n; i++) {
		string a, b, c; cin >> a >> b >> c;
		lower(a); lower(c);
		
		if (m.count(a) == 0) { m[a] = cnt; cnt++; }
		if (m.count(c) == 0) { m[c] = cnt; cnt++; }

		g.add_edge(m[c], m[a]);
	}

	int res = 0;
	for (int i = 0; i < cnt; i++) {
		if (g.visited[i]) { continue; }

		g.dfs(i);
		res = max(res, g.heights[i]);
	}

	cout << res << endl;
}