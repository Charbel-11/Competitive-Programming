#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <queue>
#include <climits>
#include <math.h>
#include <numeric>
#include <fstream>
using namespace std;
typedef long long ll;

struct DSU {
	vector<int> rank, parent;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}

	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		return true;
	}
};

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int added = 0; vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<vector<int>> anc;
	vector<node> nodes;
	vector<int> depth;

	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 1.0)));
		nodes.resize(n); depth.resize(n, 0);
		anc.resize(n + 1, vector<int>(lg2 + 1, -1));
	}

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	//Preprocessing takes O(nlogn) time; finds the depth at the same time
	void preprocess() {
		queue<int> q; q.push(root);
		vector<bool> visited(n, false);
		visited[root] = true;
		anc[root][0] = root;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto& e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				anc[e.v][0] = cur;
				depth[e.v] = depth[cur] + 1;
				q.push(e.v); visited[e.v] = true;
			}
		}
		for (int i = 1; i <= lg2; i++)
			for (int u = 0; u < n; u++)
				anc[u][i] = anc[anc[u][i - 1]][i - 1];
	}

	//Need to preprocess before using!
	//Returns the LCA of nodes u and v in O(logn)		
	int LCA(int u, int v) {
		if (depth[u] < depth[v]) { swap(u, v); }

		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) >= depth[v])
				u = anc[u][i];	//furthest parent found is 2^i
		}

		if (u == v) { return v; }

		for (int i = lg2; i >= 0; i--) {
			if (anc[u][i] != anc[v][i]) {
				u = anc[u][i];
				v = anc[v][i];
			}
		}

		return anc[u][0];
	}

	int dist(int u, int v) {
		int lca = LCA(u, v);
		return depth[u] + depth[v] - 2 * depth[lca];
	}

	//Finds kth parent of u
	int findKthParent(int u, int k) {
		int pI = 0;
		while (k) {
			if (k & 1) { u = anc[u][pI]; }
			pI++; k >>= 1;
		}
		return u;
	}

	//v is an ancestor of u
	int join(int u, int v, DSU& dsu) {
		int distU = depth[u] - depth[v];

		if (nodes[u].added < distU) {
			if (nodes[u].added == 0) { 
				dsu.merge(u, anc[u][0]); 
				
				if (distU > 1) { nodes[u].added = join(anc[u][0], v, dsu); }
				nodes[u].added++;
			}
			else {
				int nU = findKthParent(u, nodes[u].added);
				nodes[u].added += join(nU, v, dsu);
			}
		}

		return nodes[u].added;
	}
};


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; ifs >> n;
		tree tr(n);
		for (int i = 0; i < n - 1; i++) {
			int u, v; ifs >> u >> v; u--; v--;
			tr.add_edge(u, v);
		}
		
		tr.preprocess();

		vector<pair<int, int>> f(n);
		for (int i = 0; i < n; i++) {
			int curF; ifs >> curF;
			f[i] = { curF, i };
		}
		sort(f.begin(), f.end());

		DSU dsu(n);
		for (int i = 1; i < n; i++) {
			if (f[i].first == f[i - 1].first) { 
				int u = f[i].second, v = f[i - 1].second;
				int lca = tr.LCA(u, v);

				tr.join(u, lca, dsu); tr.join(v, lca, dsu);
			}
		}

		set<int> diffComp;
		for (int i = 0; i < n; i++) {
			diffComp.insert(dsu.find(i));
		}

		int ans = (int)diffComp.size() - 1;
		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}