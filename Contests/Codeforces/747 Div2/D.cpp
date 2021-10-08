#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;

struct edge {
	int u, v, col; edge() {}
	edge(int _u, int _v, int _c) :u(_u), v(_v), col(_c) {}
};
struct node { vector<edge> edges; };

struct graph {
	int n; vector<node> nodes;

	graph(int _n) :n(_n) { nodes.resize(n); }

	void addEdge(int u, int v, int c) {
		nodes[u].edges.push_back(edge(u, v, c));
		nodes[v].edges.push_back(edge(v, u, c));
	}

	int dfs(int start, bool restore, vector<int>& color) {
		vector<int> seen; seen.push_back(start);
		stack<int> S; S.push(start); color[start] = restore;
		int ans = restore; bool valid = true;

		while (!S.empty()) {
			int cur = S.top(); S.pop();
			for (auto& e : nodes[cur].edges) {
				if (color[e.v] == -1) {
					color[e.v] = color[cur] ^ e.col;
					if (color[e.v]) { ans++; }
					S.push(e.v); seen.push_back(e.v);
				}
				else if (color[e.v] != (color[cur] ^ e.col)) {
					valid = false;
				}
			}
		}

		if (restore) {
			for (auto& x : seen) { color[x] = -1; }
		}

		if (!valid) { return -1; }
		else { return ans; }
	}

	int findMaxImposters() {
		vector<int> color(n, -1);
		int ans = 0;

		for (int i = 0; i < n; i++) {
			if (color[i] != -1) { continue; }

			int c1 = dfs(i, true, color);
			int c2 = dfs(i, false, color);

			int best = max(c1, c2);
			if (best == -1) { return -1; }
			ans += best;
		}

		return ans;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;
		graph g(n);
		for (int i = 0; i < m; i++) {
			int u, v; cin >> u >> v; u--; v--;
			string type; cin >> type;
			int c = (type == "crewmate" ? 0 : 1);
			g.addEdge(u, v, c);
		}

		cout << g.findMaxImposters() << '\n';
	}
}