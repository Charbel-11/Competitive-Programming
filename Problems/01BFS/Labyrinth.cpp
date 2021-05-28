//https://codeforces.com/contest/1063/problem/B

#include <iostream>
#include <vector>
#include <deque>
#include <string>

using namespace std;
typedef long long ll;
const int INF = 1 << 30;
int r, c;

struct edge {
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	int n;

	graph(int _n) :n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, int w) {
		nodes[u].edges.push_back(edge(u,v,w));
	}

	//Assumes all weights are either 0 or x for a fixed x >= 0
	//Returns the shortest distance from s to all nodes
	vector<int> bfs01(int s) {
		vector<bool> visited(n, 0); vector<int> dist(n, INF); deque<int> dq;
		dist[s] = 0; dq.push_back(s);

		while (!dq.empty()) {
			int cur = dq.front(); dq.pop_front();
			while (visited[cur] && !dq.empty()) { cur = dq.front(); dq.pop_front(); }
			if (visited[cur]) { break; } visited[cur] = 1;

			for (auto &e : nodes[cur].edges) {
				if (visited[e.v] || dist[e.v] < dist[cur] + e.w) { continue; }
				dist[e.v] = dist[cur] + e.w;
				if (e.w) { dq.push_back(e.v); }
				else { dq.push_front(e.v); }
			}
		}

		return move(dist);
	}
};

int dx[] = { 1,0 };
int dy[] = { 0,1 };
int n, m;

bool check(int i, int j) {
	if (i < 0 || j < 0 || i >= n || j >= m) { return false; }
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	int rS, cS; cin >> rS >> cS; rS--; cS--;
	int maxLeft, maxRight; cin >> maxLeft >> maxRight;

	vector<string> grid(n);
	for (auto &x : grid) { cin >> x; }

	graph g(n*m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == '*') { continue; }
			for (int k = 0; k < 2; k++) {
				int ni = i + dx[k], nj = j + dy[k];
				if (!check(ni, nj) || grid[ni][nj] == '*') { continue; }
				g.add_edge(i*m + j, ni*m + nj, 0);
				g.add_edge(ni*m + nj, i*m + j, k);
			}
		}
	}

	int res = 0;
	vector<int> dist = g.bfs01(rS*m + cS);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int idx = i * m + j;
			int leftNeeded = dist[idx];
			int rightNeeded = abs(cS - (j + leftNeeded));
			if (leftNeeded <= maxLeft && rightNeeded <= maxRight) { res++; }
		}
	}

	cout << res << '\n';
}