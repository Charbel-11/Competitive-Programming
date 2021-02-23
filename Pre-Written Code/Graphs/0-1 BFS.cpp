#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>

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
		edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
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


//GRID DIRECT IMPLEMENTATION
const int INF = 1 << 30; 
const int MAXN = 2002;			//SET MAXN
int n, m;
int dist[MAXN][MAXN];
bool visited[MAXN][MAXN];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

bool check(int i, int j) {
	if (i < 0 || j < 0 || i >= n || j >= m) { return false; }
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			dist[i][j] = INF;

	deque<pair<int, int>> dq;
	dist[0][0] = 0; dq.push_back({ 0,0 });

	while (!dq.empty()) {
		pair<int, int> cur = dq.front(); dq.pop_front();
		while (visited[cur.first][cur.second] && !dq.empty()) { cur = dq.front(); dq.pop_front(); }
		if (visited[cur.first][cur.second]) { break; } visited[cur.first][cur.second] = 1;

		int i = cur.first, j = cur.second;

		for (int k = 0; k < 4; k++) {
			int ni = i + dx[k], nj = j + dy[k];
			if (!check(ni, nj)) { continue; }

			int w = //CHANGE ACCORDING TO THE PROBLEM
			if (visited[ni][nj] || dist[ni][nj] < dist[i][j] + w) { continue; }
			dist[ni][nj] = dist[i][j] + w;
			if (w) { dq.push_back({ ni,nj }); }
			else { dq.push_front({ ni,nj }); }
		}
	}
}