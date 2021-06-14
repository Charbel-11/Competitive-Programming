#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

typedef long long ll;
using namespace std;

int n;
vector<ll> nums;
int inf = 200;

struct edge {
	int u, v;
	edge(int _u,int _v) : u(_u), v(_v) {};
};

struct node {
	vector<edge> edges;
};

struct graph {
	vector<node> nodes; vector<int> distance; vector<int> parent;
	graph(int n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		nodes[u].edges.push_back(edge(u,v));
	}

	int findCycle(int s) {
		distance.resize(n, inf); parent.resize(n, -1);
		vector<bool> visited(n, false);  queue<int> Q;
		Q.push(s); visited[s] = 1; distance[s] = 0;

		int minCycleLength = inf;
		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto e : nodes[cur].edges) {
				if (visited[e.v] && e.v != parent[e.u]) { return distance[e.u] + distance[e.v] + 1; }
				if (!visited[e.v]) { Q.push(e.v); visited[e.v] = 1; parent[e.v] = e.u; distance[e.v] = distance[e.u] + 1; }
			}
		}

		return minCycleLength;
	}

	int findMinCycle() {
		int finalMin = inf;
		for (int i = 0; i < n; i++) {
			int cur = findCycle(i); 
			finalMin = min(finalMin, cur);
		}

		return finalMin == inf ? -1 : finalMin;
	}
};

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		ll temp; cin >> temp;
		if (temp) { nums.push_back(temp); }
	}
	n = (int)nums.size();

	if (n > 120) { cout << 3 << endl; return 0; }

	graph g(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) { continue; }
			if (nums[i] & nums[j]) { g.add_edge(i, j);}
		}
	}

	cout << g.findMinCycle() << endl;
}