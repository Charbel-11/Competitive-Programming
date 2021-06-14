#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

vector<pair<int, int>> students, tutors;

struct edge {
	int u, v; bool matched = 0; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { bool matched = 0; vector<edge> edges; };

struct bipartiteGraph {
	vector<node> nodes; int n, m;
	vector<int> match;
	vector<bool> vis;

	//Vertices on the left should have indices 0..n-1
	//Vertices on the right should have indices n..n+m-1
	bipartiteGraph(int _n, int _m) : n(_n), m(_m) {
		nodes.resize(n + m);
		match.resize(n + m, -1); vis.resize(n + m, 0);
	}
	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	bool augment(int v) {
		if (vis[v]) { return 0; }
		vis[v] = 1;
		for (auto &e : nodes[v].edges) {
			if (match[e.v] == -1 || augment(match[e.v])) {
				match[e.v] = v; match[v] = e.v;
				return 1;
			}
		}
		return 0;
	}

	int matching() {	//With greedy initialization
		int w = 0;
		for (int x = 0; x < n; x++) {
			if (match[x] != -1) { continue; }
			for (auto &e : nodes[x].edges) {
				if (match[e.v] == -1) {
					match[e.v] = x; match[x] = e.v;
					w++;  break;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if (match[i] != -1) { continue; }
			for (int j = 0; j < n; j++) { vis[j] = 0; }
			w += augment(i);
		}
		return w;
	}
};

int distance(pair<int, int> &p1, pair<int, int> &p2) {
	return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

bool check(int n, int k) {
	bipartiteGraph g(n, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (distance(students[i], tutors[j]) <= k) {
				g.add_edge(i, j + n);
			}
		}
	}

	return g.matching() == n;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	students.resize(n); tutors.resize(n);
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		students[i] = { x,y };
	}
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		tutors[i] = { x,y };
	}

	int l = 0, r = (int)4e8 + 5;
	while (l < r) {
		int mid = (l + r) / 2;
		bool b = check(n, mid);
		if (b) { r = mid; }
		else { l = mid + 1; }
	}

	cout << l << endl;
}