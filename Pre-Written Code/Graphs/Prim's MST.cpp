#include <bits/stdc++.h>
using namespace std;

struct edge {
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, int w) {
		edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	int primMST(int s, vector<int> &parent) {
		vector<bool> visited(n, false);
        vector<int> dist(n, INT_MAX);
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
		dist[s] = 0ll; pq.push({ 0, s }); int res = 0;

		for (int i = 0; i < n; i++) {
			int cur = pq.top().second; pq.pop();
			while (visited[cur]) { cur = pq.top().second; pq.pop(); }
			visited[cur] = true; res += dist[cur];
			for (auto &e : nodes[cur].edges){
				if (dist[e.v] > e.w) {
					dist[e.v] = e.w; parent[e.v] = e.u;
                    pq.push({ dist[e.v], e.v });
				}
            }
		}

		return res;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

}