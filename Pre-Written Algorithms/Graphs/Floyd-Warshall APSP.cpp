#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1ll << 60;

struct Edge {
	int u, v; ll w; Edge() {}
	Edge(int _u, int _v, ll _w = 0) :
		u(_u), v(_v), w(_w) {}
};

struct Node { vector<Edge> edges; };

struct Graph {
	vector<Node> nodes;
	vector<vector<ll>> D;
	vector<vector<int>> helper;
	int n;
	Graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, ll w = 0) {
		Edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void allPairsShortestPath() {
		int n = nodes.size();

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				helper[i][j] = -1;

		D.resize(n); 
		for (int i = 0; i < n; i++) { D[i].resize(n, INF); D[i][i] = 0; }

		for (auto &x : nodes)
			for (auto &y : x.edges)
				D[y.u][y.v] = min(D[y.u][y.v], y.w);

		for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (D[i][k] + D[k][j] < D[i][j]) {
                        D[i][j] = D[i][k] + D[k][j];
                        helper[i][j] = k;
                    }
                }
            }
        }
	}

	void printShortestPath(int s, int d) {
		if (s == d) { cout << s << " "; return; }
        printShortestPath(s, helper[s][d]);
        printShortestPath(helper[s][d], d);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

}