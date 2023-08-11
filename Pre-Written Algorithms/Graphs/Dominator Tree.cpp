#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};
struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

};

struct graph {
	int n; vector<node> nodes[2];
	vector<int> idxToOrder, orderToIdx;
	vector<int> dsuParent, minToDsuParIdx;
	vector<int> sdom, dom, parent;			// work on pre-order index
	vector<vector<int>> bucket;

	graph(int _n) : n(_n) { 
		nodes[0].resize(n);
		idxToOrder.resize(n, -1); orderToIdx.resize(n, -1);
		parent.resize(n);  bucket.resize(n);
		
		minToDsuParIdx.resize(n); dsuParent.resize(n);
		iota(minToDsuParIdx.begin(), minToDsuParIdx.end(), 0);
		iota(dsuParent.begin(), dsuParent.end(), 0);

		sdom.resize(n); dom.resize(n);
		iota(sdom.begin(), sdom.end(), 0);
		iota(dom.begin(), dom.end(), 0);
	}

	void add_edge(int u, int v) {
		nodes[0][u].edges.push_back(edge(u, v));
	}

	// Builds the dominator tree T of a directed graph G in O((n+m)logn) (nodes in G and T have = index)
	// Note that every node not reachable from s in G will be isolated in T
	// u parent of v in T <-> u dominates v in G <-> every path in G from S to v must pass by u
	// dominators of v wrt S are the ancestors of v in T
	tree getDominatorTree(int S) {
		nodes[1].clear(); nodes[1].resize(n);
		int t = 0; dfs0(S, t);
		int initialN = n; n = t;

		buildDom(); tree T(initialN, S);
		for (int i = 1; i < n; i++) {
			T.add_edge(orderToIdx[i], orderToIdx[dom[i]]);
		}

		n = initialN;
		return T;
	}

private:
	void dfs0(int u, int &t){
		idxToOrder[u] = t; orderToIdx[t] = u; t++;
		for (auto& e : nodes[0][u].edges) {
			if (idxToOrder[e.v] == -1) {
				dfs0(e.v, t);
				parent[idxToOrder[e.v]] = idxToOrder[e.u];
			}
			nodes[1][e.v].edges.push_back(edge(e.v, e.u));		// here to avoid reverse edges to unreachable nodes
		}
	}

	// If x=0, returns idx of a node from u to prev(root) with min sdom 
	// Otherwise, return idx of prev(root) on the path from u to root
	int find(int u, int x = 0) {
		if (u == dsuParent[u]) { return x ? -1 : u; }
		int v = find(dsuParent[u], x + 1);
		if (v < 0) { return u; }

		if (sdom[minToDsuParIdx[dsuParent[u]]] < sdom[minToDsuParIdx[u]]) {
			minToDsuParIdx[u] = minToDsuParIdx[dsuParent[u]];
		}
		dsuParent[u] = v;
		return x ? v : minToDsuParIdx[u];
	}
	void merge(int u, int v) { dsuParent[v] = u; }

	void buildDom() {
		for (int i = n - 1; i >= 0; i--) {
			for (auto& e : nodes[1][orderToIdx[i]].edges) {
				sdom[i] = min(sdom[i], sdom[find(idxToOrder[e.v])]);
			}
			if (i > 0) { bucket[sdom[i]].push_back(i); }

			for(int w : bucket[i]){
				int v = find(w);
				if (sdom[v] == sdom[w]) { dom[w] = sdom[w]; }
				else { dom[w] = v; }
			}
			if (i > 0) { merge(parent[i], i); }
		}

		for (int i = 1; i < n; i++) {
			if (dom[i] != sdom[i]) { dom[i] = dom[dom[i]]; }
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

}