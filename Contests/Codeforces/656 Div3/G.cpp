#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <set>
#include <climits>
using namespace std;

vector<int> ans;

struct edge {
	int u, v; bool b; edge() {}
	edge(int _u, int _v, bool _b) :
		u(_u), v(_v), b(_b) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	vector<int> color;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); color.resize(n, -1); }

	void add_edge(int u, int v, bool b) {
		edge e1(u, v, b); nodes[u].edges.push_back(e1);
		edge e2(v, u, b); nodes[v].edges.push_back(e2);
	}

	pair<vector<int>, vector<int>> graphColoring(int u) {
		stack<int> S; S.push(u);
		color[u] = 0;

		vector<int> c0, c1; c0.push_back(u);

		while (!S.empty()) {
			int cur = S.top(); S.pop();
			for (auto &e : nodes[cur].edges) {
				if (color[e.v] != -1) {
					if (e.b && color[e.u] == color[e.v]) { return { vector<int>(), vector<int>() }; }
					if (!e.b && color[e.u] != color[e.v]) { return { vector<int>(), vector<int>() }; }
					continue;
				}
				if (e.b) { color[e.v] = 1 ^ color[e.u]; }
				else { color[e.v] = color[e.u]; }
				if (color[e.v]) { c1.push_back(e.v); }
				else { c0.push_back(e.v); }
				S.push(e.v);
			}
		}

		return { move(c0), move(c1) };
	}
	bool graphColoring() {
		for (int i = 0; i < n; i++) {
			if (color[i] == -1) { 
				auto p = graphColoring(i); 
				if (p.first.size() == p.second.size() && p.first.empty()) { return 0; }
				
				if (p.first.size() < p.second.size()) {
					for (auto x : p.first) { ans.push_back(x); }
				}
				else {
					for (auto &x : p.second) { ans.push_back(x); }
				}
			}
		}
		return 1;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n; ans.clear();
		vector<int> a1(n), a2(n), freq(n, 0);
		vector<pair<int, int>> pos1(n, { -1, -1 }), pos2(n, { -1, -1 });
		for (int i = 0; i < n; i++) {
			cin >> a1[i]; a1[i]--; freq[a1[i]]++; 
			if (pos1[a1[i]].first == -1) { pos1[a1[i]] = { 0, i }; }
			else { pos2[a1[i]] = { 0, i }; }
		}
		for (int i = 0; i < n; i++) {
			cin >> a2[i]; a2[i]--; freq[a2[i]]++; 
			if (pos1[a2[i]].first == -1) { pos1[a2[i]] = { 1, i }; }
			else { pos2[a2[i]] = { 1, i }; }
		}
		
		bool OK = true;
		for (int i = 0; i < n; i++) { 
			if (freq[i] != 2) { OK = false; break; }
		}
		if (!OK) { cout << -1 << '\n'; continue; }

		graph g(n);
		for (int i = 0; i < n; i++) {
			int c1 = pos1[i].second, c2 = pos2[i].second;
			if (pos1[i].first == pos2[i].first) { g.add_edge(c1, c2, 1); }
			else { g.add_edge(c1, c2, 0); }
		}

		bool b = g.graphColoring();
		if (!b) { cout << -1 << '\n'; }
		else {
			cout << ans.size() << '\n';
			for (auto &x : ans) { cout << x + 1 << ' '; }
			cout << '\n';
		}
	}
}