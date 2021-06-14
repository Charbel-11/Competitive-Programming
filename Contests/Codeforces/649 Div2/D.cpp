//Could have considered first k nodes only

#include <iostream>
#include <vector>
#include <map>
using namespace std;

int k;
vector<int> set1, set2, cc;
int cycleNode;
struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<int> parent;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, int w = 0) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	bool cycle_dfs(int u, vector<int> &color) {
		color[u] = 1;
		for (auto x : nodes[u].edges) {
			int v = x.v;
			if (v == parent[u]) { continue; }
			if (color[v] == 0) {
				parent[v] = u;
				if (cycle_dfs(v, color)) { return true; }
			}
			else if (color[v] == 1) { parent[v] = u; cycleNode = u; return true; }
		}
		color[u] = 2; return false;
	}
	bool find_cycle() {
		vector<int> color(n, 0); parent.resize(n, -1);
		for (int v = 0; v < n; v++)
			if (cycle_dfs(v, color)) { return true; }
		return false;
	}

	void dfs(int u, int p, int dist) {
		if (dist % 2) { set1.push_back(u); }
		else { set2.push_back(u); }
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u, dist + 1);
		}
	}

	void separate() {
		set1.clear(); set2.clear(); cc.clear();
		int cur = cycleNode; 
		cc.push_back(cur); set1.push_back(cur);
		cur = parent[cur];
		bool alt = 1;
		while (cur != cycleNode) {
			if (alt) { set2.push_back(cur); }
			else { set1.push_back(cur); }
			cc.push_back(cur);
			alt = !alt;
			cur = parent[cur];
		}

		if (cc.size() <= k) {
			cout << 2 << '\n' << cc.size() << '\n';
			for (auto &x : cc) { cout << x + 1 << ' '; }
			cout << '\n';
			return;
		}

		checkIndep();
	}

	void checkIndep() {
		map<int, int> s2;
		for (int i = 0; i < set2.size(); i++) {
			s2.insert({ set2[i], i });
		}

		for (int i = 0; i < set2.size(); i++) {
			int u = set2[i];
			for (auto &e : nodes[u].edges) {
				if (s2.count(e.v)) {
					int j = s2[e.v];
					int dist1 = j - i;
					int dist2 = n - dist1;
					if (dist1 < dist2) { parent[e.v] = u; cycleNode = u; }
					else { parent[u] = e.v; cycleNode = e.v; }
					
					separate(); return;
				}
			}
		}

		cout << 1 << '\n'; 
		for (int i = 0; i < (k + 1) / 2; i++) {
			cout << set2[i] + 1 << ' ';
		}
		cout << '\n';
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m >> k;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	bool cycle = g.find_cycle();
	if (!cycle) { 
		cout << 1 << '\n';
		g.dfs(0, -1, 0); 
		if (set1.size() >= (k + 1) / 2) {
			for (int i = 0; i < (k + 1) / 2; i++) { cout << set1[i] + 1 << ' '; }
		}
		else {
			for (int i = 0; i < (k + 1) / 2; i++) { cout << set2[i] + 1 << ' '; }
		}
		cout << '\n';
		return 0;
	}

	g.separate();
}