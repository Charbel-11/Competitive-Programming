#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;

vector<int> dest, monsters;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	vector<int> parent, dist, distM;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); parent.resize(n, -1); dist.resize(n, 1e7); distM.resize(n, 1e7); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	void bfs1(int u) {
		queue<int> Q; vector<bool> visited(n, 0);
		dist[u] = 0; visited[u] = 1; Q.push(u);

		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto &e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				dist[e.v] = dist[cur] + 1;
				visited[e.v] = 1; Q.push(e.v);
				parent[e.v] = cur;
			}
		}
	}

	void bfs2() {
		queue<int> Q; vector<bool> visited(n, 0);
		for (auto x : monsters) { Q.push(x); visited[x] = 1; distM[x] = 0; }

		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto &e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				distM[e.v] = distM[cur] + 1;
				visited[e.v] = 1; Q.push(e.v);
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<string> grid(n);
	for (auto &s : grid) { cin >> s; }
	graph g(n*m);

	int st;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int cur = i * m + j;
			if (grid[i][j] == '#') { continue; }

			if (i < n - 1 && grid[i + 1][j] != '#') { g.add_edge(cur, (i + 1)*m + j); }
			if (j < m - 1 && grid[i][j + 1] != '#') { g.add_edge(cur, i*m + j + 1); }
			if ((i == n - 1 || j == m - 1 || i == 0 || j == 0) && grid[i][j] != 'M') { dest.push_back(cur); }
			if (grid[i][j] == 'A') { st = cur; }
			if (grid[i][j] == 'M') { monsters.push_back(cur); }
		}
	}

	g.bfs1(st); g.bfs2();

	int d = -1;
	for(auto &m : dest){
		if (g.dist[m] < g.distM[m]) { d = m; break; }
	}

	if (d == -1) { cout << "NO\n"; }
	else {
		cout << "YES\n";
		int cur = d;
		string ans = "";
		while (cur != st) {
			int i = cur / m, j = cur % m;
			int prev = g.parent[cur];
			int pi = prev / m, pj = prev % m;
			if (pi == i - 1) { ans.push_back('D'); }
			else if (pi == i + 1) { ans.push_back('U'); }
			else if (pj == j - 1) { ans.push_back('R'); }
			else { ans.push_back('L'); }
			cur = prev;
		}
		reverse(ans.begin(), ans.end());

		cout << ans.size() << '\n' << ans << '\n';
	}
}