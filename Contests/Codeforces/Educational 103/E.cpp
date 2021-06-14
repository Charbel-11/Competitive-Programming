#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int k;


struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int id; vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
	}

	bool cycle_dfs(int u, vector<int>& color, vector<int>& parent) {
		color[u] = 1;
		for (auto& e : nodes[u].edges) {
			int v = e.v;
			if (color[v] == 0) {
				parent[v] = u;
				if (cycle_dfs(v, color, parent)) { return true; }
			}
			else if (color[v] == 1) { parent[v] = u; return true; }	//One node in the cycle would be u or v
		}
		color[u] = 2; return false;
	}
	bool find_cycle() {
		vector<int> color(n, 0), parent(n, -1);
		for (int v = 0; v < n; v++)
			if (cycle_dfs(v, color, parent)) { return true; }
		return false;
	}

	void dfs(int u, vector<int>& visited, vector<int>& ans) {
		visited[u] = true;
		for (auto& e : nodes[u].edges) {
			int v = e.v;
			if (!visited[v]) { dfs(v, visited, ans); }
		}
		ans.push_back(u);
	}
	vector<int> topological_sort() {
		vector<int> visited(n, false), ans;
		for (int i = 0; i < n; ++i)
			if (!visited[i]) { dfs(i, visited, ans); }
		reverse(ans.begin(), ans.end());
		return move(ans);
	}
};

int pToInt(string& s) {
	int ans = 0;
	for (int i = 0; i < k; i++) {
		ans *= 27;
		if (s[i] == '_') { ans += 26; }
		else { ans += s[i] - 'a'; }
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m >> k;
	vector<int> patterns(6e5);
	graph g(6e5);
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		int id = pToInt(s);
		g.nodes[id].id = i;
		patterns[id] = i;
	}
	
	bool OK = true;
	vector<pair<int, vector<int>>> str;
	for (int i = 0; i < m; i++) {
		string s; cin >> s;
		int mt; cin >> mt; mt--;
		str.push_back({ mt, vector<int>() });
		int source = -1;
		for (int j = 0; j < (1 << k); j++) {
			string curP = s;
			for (int kk = 0; kk < k; kk++) {
				if (j & (1 << kk)) { curP[kk] = '_'; }
			}
			int corrP = pToInt(curP);
			str.back().second.push_back(corrP);
			if (patterns[corrP] == mt) { source = corrP; }
		}
		
		if (source == -1) { OK = false; continue; }
		for (auto& x : str.back().second) {
			if (x == source) { continue; }
			g.add_edge(source, x);
		}
	}

	if (!OK || g.find_cycle()) { cout << "NO" << '\n'; return 0; }
	vector<int> res = g.topological_sort();
	cout << "YES" << '\n';
	for (auto& x : res) {
		if (patterns[x] != -1) { cout << g.nodes[x].id + 1 << ' '; }
	}
	cout<<'\n';
}