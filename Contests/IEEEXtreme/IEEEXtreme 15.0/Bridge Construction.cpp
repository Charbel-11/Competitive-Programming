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

	void dfs(int u, int p, vector<int>& dist) {
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dist[e.v] = dist[u] + 1;
			dfs(e.v, u, dist);
		}
	}

	//returns {endpoint, dist}
	pair<int, int> bfs(int u, vector<bool>& visited, vector<int>& parent) {
		queue<pair<int, int>> Q; visited[u] = true;
		int dist = 0; Q.push({ u, 0 });
		while (!Q.empty()) {
			u = Q.front().first; dist = Q.front().second; Q.pop();
			for (auto& e : nodes[u].edges) {
				if (visited[e.v]) { continue; }
				visited[e.v] = true; Q.push({ e.v, dist + 1 });
				parent[e.v] = u;
			}
		}
		return { u, dist };
	}

	void findDiameter(int u, vector<bool>& vis1, vector<bool>& vis2, vector<int>& parent,
		int& diameter, int& d1, int& d2) {
		d1 = bfs(u, vis1, parent).first;
		auto p = bfs(d1, vis2, parent);
		d2 = p.first; diameter = p.second;
	}
	
	int findCenter(int u, int diameter, vector<int>& parent) {
		diameter >>= 1;
		while (diameter--) { u = parent[u]; }
		return u;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int tt; cin >> tt;
	while (tt--) {
		int n1; cin >> n1; tree t1(n1);
		for (int i = 0; i < n1 - 1; i++) {
			int u, v; cin >> u >> v; u--; v--;
			t1.add_edge(u, v);
		}

		int n2; cin >> n2; tree t2(n2);
		for (int i = 0; i < n2 - 1; i++) {
			int u, v; cin >> u >> v; u--; v--;
			t2.add_edge(u, v);
		}

		vector<bool> vis11(n1, false), vis12(n1, false);
		vector<bool> vis21(n2, false), vis22(n2, false);
		vector<int> parent1(n1), parent2(n2);
		int d1 = 0, d2 = 0; int e11, e12, e21, e22;
		t1.findDiameter(0, vis11, vis12, parent1, d1, e11, e12);
		t2.findDiameter(0, vis21, vis22, parent2, d2, e21, e22);
		int c1 = t1.findCenter(e12, d1, parent1);
		int c2 = t2.findCenter(e22, d2, parent2);

		int maxDist = max({ d1, d2, (d1 + 1) / 2 + (d2 + 1) / 2 + 1 });
		cout << maxDist << '\n';
		cout << c1 + 1 << " " << c2 + 1 << '\n';
	}
}