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
	int u, v; ll w;
	edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<node> nodes;
	vector<int> parent; vector<ll> dist;
	stack<int> tempS;	//remove if the subtree sizes aren't needed
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v, ll w = 1ll) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void fill() {
		parent.resize(n);
		dist.resize(n, INF); dist[root] = 0;			//remove if dist is not needed
		queue<int> Q; Q.push(root);
		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			tempS.push(cur);							//remove if subtree sizes are not needed
			for (auto &e : nodes[cur].edges) {
				if (parent[cur] == e.v) { continue; }
				Q.push(e.v); parent[e.v] = cur;
				dist[e.v] = e.w + dist[cur];			//remove if dist is not needed
			}
		}
	}

	//Call fill before
	//Returns size of subtree of each node counting the node itself
	vector<int> getSubtreeSize() {
		vector<int> res(n, 1);		
		while (!tempS.empty()) {
			int cur = tempS.top(); tempS.pop();
			if (cur == root) { continue; }
			res[parent[cur]] += res[cur];
		}
		return move(res);		
	}
};

int main() {
	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
}