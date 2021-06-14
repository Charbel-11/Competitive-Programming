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
	int ID;
	int u, v; ll paths;
	edge() {}
	edge(int _u, int _v, int id) :
		u(_u), v(_v), ID(id) {
		paths = 0;
	}

	bool operator<(edge& rhs) {
		return paths < rhs.paths;
	}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<edge> edges;
	vector<int> parent, size;
	stack<int> tempS;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v, edges.size()); edge e2(v, u, edges.size());
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
		edges.push_back(e1);
	}

	void fill() {
		parent.resize(n);
		queue<int> Q; Q.push(root);
		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			tempS.push(cur);					
			for (auto &e : nodes[cur].edges) {
				if (parent[cur] == e.v) { continue; }
				Q.push(e.v); parent[e.v] = cur;
			}
		}
	}

	//Call fill before
	void getSubtreeSize() {
		size.resize(n, 1);

		while (!tempS.empty()) {
			int cur = tempS.top(); tempS.pop();
			size[parent[cur]] += size[cur];
		}
	}

	void dfs(int u, int p) {
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			e.paths = (ll)size[e.v] * (ll)(n - size[e.v]);
			edges[e.ID].paths = e.paths;
			dfs(e.v, u);
		}
	}
};

int main() {
	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n-1; i++) {
		int u, v; cin >> u >> v; u--; v--;

		t.add_edge(u, v);
	}

	t.fill();
	t.getSubtreeSize();

	t.dfs(0, -1);

	sort(t.edges.begin(), t.edges.end());

	vector<int> ans(n-1);

	for (int i = 0; i < n - 1; i++) {
		ans[t.edges[i].ID] = i;
	}

	for (auto& x : ans) {
		cout << x << endl;
	}
}