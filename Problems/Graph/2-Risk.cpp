#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

struct edge {
	int u, v;
	int w;
	edge() {}
	edge(int _u, int _v, int _w = 1) :
		u(_u), v(_v), w(_w) {}
};

struct node {
	int id; vector<edge> edges;
	int distance; int parent;
};

bool operator < (const node& v1, const node& v2) {		//To make the initially max-heap a min-heap
	return v1.distance > v2.distance;
}

struct graph {
	vector<vector<int>> D;
	vector<node> nodes;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
	}

	void shortestPath(int s) {
		for (int i = 0; i < nodes.size(); i++) {
			nodes[i].parent = -1;
			nodes[i].distance = INT_MAX;
		}
		nodes[s].distance = 0;

		priority_queue<node> pq;
		pq.push(nodes[s]);

		while (!pq.empty()) {
			node u = pq.top(); pq.pop();

			for (auto e : u.edges) {
				if (nodes[e.v].distance > u.distance + e.w) {
					nodes[e.v].distance = u.distance + e.w;
					nodes[e.v].parent = e.u;

					pq.push(nodes[e.v]);
				}
			}
		}
	}

	void allPairsShortestPath() {
		int n = nodes.size();
		//Initializing all values at INT_MAX will cause an overflow for D[i][k] + D[k][j]
		int max = 50;	//Change max to be bigger than any possible output
		D.resize(n); for (int i = 0; i < n; i++) { D[i].resize(n, max); D[i][i] = 0; }

		for (auto u : nodes)
			for (auto e : u.edges)
				D[e.u][e.v] = min(D[e.u][e.v], e.w);

		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
	}
};

int main() {
	int setNum = 1;
	while (true) {
		graph g(20);

		bool ok = true;
		for (int i = 0; i < 19; i++) {
			int numOfE; cin >> numOfE;
			if (cin.fail()) { ok = false; break; }
			for (int j = 0; j < numOfE; j++) {
				int v; cin >> v; v--;
				g.add_edge(i, v);
				g.add_edge(v, i);
			}
		}
		if (!ok) { break; }

		int N; cin >> N;

		g.allPairsShortestPath();

		cout << "Test Set #" << setNum++ << endl;
		for (int i = 0; i < N; i++) {
			int s, d; cin >> s >> d;

			cout << s << " to " << d << ": " << g.D[s - 1][d - 1] << endl;
		}
		cout << endl;
	}
}