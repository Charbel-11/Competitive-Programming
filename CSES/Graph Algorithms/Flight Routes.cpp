#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;

const ll INF = 1ll << 60;
int k;

struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, ll w) {
		edge e1(u, v, w);
		nodes[u].edges.push_back(e1);
	}

	//Finds the k smallest distances from s to n-1
	void dijkstra_sp(int s) {
		vector<int> visited(n, 0);
		priority_queue <pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
		pq.push({ 0, s });

		while(true){
			int cur = pq.top().second; ll dist = pq.top().first; pq.pop();
			if (visited[cur] >= k) { continue; }
			visited[cur]++;

			if (cur == n - 1) {
				cout << dist << " ";
				if (visited[cur] == k) { break; }
			}

			for (auto &e : nodes[cur].edges) { pq.push({ dist + e.w, e.v }); }	//I keep track of all possible distances where the node is visited < k times (excluding this time)
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m >> k;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; ll c; cin >> u >> v >> c; u--; v--;
		g.add_edge(u, v, c);
	}

	g.dijkstra_sp(0);
}