#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <queue>
#include <climits>
using namespace std;

vector<int> res;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int mex = -1; vector<edge> edges; };

struct graph {
	vector<node> nodes;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	bool check(vector<pair<int, int>> &mexOfNode) {
		for (int i = 0; i < n; i++) {
			int cur = res[i];

			set<int> seen;
			for (auto &e : nodes[cur].edges) {
				if (nodes[e.v].mex != -1) {
					seen.insert(nodes[e.v].mex);
				}
			}

			int curMex = 1;
			while (seen.count(curMex)) { curMex++; }

			nodes[cur].mex = curMex;
		}

		for (int i = 0; i < n; i++) {
			if (mexOfNode[i].first != nodes[mexOfNode[i].second].mex) { return false; }
		}
		return true;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b; a--; b--;
		g.add_edge(a, b);
	}

	vector<pair<int, int>> mexOfNode(n);
	for (int i = 0; i < n; i++) {
		int curM; cin >> curM;
		mexOfNode[i] = { curM, i };
	}

	sort(mexOfNode.begin(), mexOfNode.end());
	for (int i = 0; i < n; i++) {
		res.push_back(mexOfNode[i].second);
	}

	bool b = g.check(mexOfNode);
	if (b) {
		for (auto &x : res) { cout << x + 1 << ' '; }
		cout << '\n';
	}
	else {
		cout << -1 << '\n';
	}
}