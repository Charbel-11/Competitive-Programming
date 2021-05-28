#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
struct edge {
	int u, v;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v){}
};

struct node { vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<node> nodes; vector<int> depth;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); depth.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	int minTime() {
		int ans = 0; 
		vector<bool> visited(n, 0); visited[0] = 1;
		for (auto &e : nodes[0].edges) {
			int cur = minTimeSubtree(e.v, visited);
			ans = max(ans, cur + 1);
		}
		return ans;
	}

	int minTimeSubtree(int u, vector<bool>& visited) {
		vector<int> p;
		queue<int> Q; Q.push(u);
		visited[u] = 1; depth[u] = 1;

		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			if (nodes[cur].edges.size() == 1) { p.push_back(depth[cur] - 1); continue; }
			for (auto &e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				Q.push(e.v); visited[e.v] = 1;
				depth[e.v] = depth[cur] + 1;
			}
		}

		sort(p.begin(), p.end());
		int ans = p[0];
		for (int i = 1; i < p.size(); i++) {
			ans = max(p[i], ans + 1);
		}
		return ans;
	}
};

int main() {
	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	cout << t.minTime() << endl;
}