//Handle point update (either node or edge) and path queries in O(log^2n)
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <string>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
vector<int> base;

struct StVal {
	int v = 0; StVal() {}
	StVal(const int _v) : v(_v) {}
	StVal(const StVal& v1, const StVal& v2) { v = max(v1, v2); }
	operator int() const { return v; }
};
struct SegTree {
	int n;
	vector<StVal> st;
	vector<int> leaves;

	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
	}

	//l, r indices of the actual array; si is the index of the segment tree array
	void init(const int si, const int l, const int r) {
		if (l == r) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal(base[l]);	//initialized with base
			leaves[l] = si;
			return;
		}

		int c1 = si << 1, c2 = (si << 1) | 1, mid = (l + r) >> 1;
		init(c1, l, mid); init(c2, mid + 1, r);
		st[si] = StVal(st[c1], st[c2]);
	}

	//l and r inclusive, 0-indexed
	StVal query(const int l, const int r) { return (l <= r && l < n&& r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	//Sets arr[i] = c
	void update(const int i, int c) {
		int si = leaves[i];
		st[si] = StVal(c);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
	}
};

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v) {}
};
struct node { int val = 0; vector<int> edges; };

struct tree {
	vector<vector<int>> anc;
	vector<edge> edges;
	vector<node> nodes;
	vector<int> depth, subtreeSize;
	vector<int> chainHead, chainIdx, posInBase;
	int root, n, lg2, chainNum, ptr;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 0.0)));
		nodes.resize(n);
		anc.resize(n + 1); for (auto& x : anc) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0); subtreeSize.resize(n, 1);
		chainNum = 0; ptr = 0; posInBase.resize(n);
		chainHead.resize(n, -1); chainIdx.resize(n);
	}

	void add_edge(int u, int v, int w = 0) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(edges.size()); edges.push_back(e1);
		nodes[v].edges.push_back(edges.size()); edges.push_back(e2);
	}

	void dfsPre(int u, int p) {
		for (auto& eIdx : nodes[u].edges) {
			auto& e = edges[eIdx];
			if (e.v == p) { continue; }
			dfsPre(e.v, u);
			subtreeSize[u] += subtreeSize[e.v];
		}
	}

	//Preprocessing takes O(nlogn) time; finds the depth at the same time
	void preprocess() {
		dfsPre(0, -1);
		queue<int> q; q.push(root);
		vector<bool> visited(n, false);
		visited[root] = true;
		anc[root][0] = root;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto& eIdx : nodes[cur].edges) {
				auto& e = edges[eIdx];
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

	void hld(int cur, int p) {
		if (chainHead[chainNum] == -1) { chainHead[chainNum] = cur; }
		chainIdx[cur] = chainNum;

		posInBase[cur] = ptr;	//sets the idx of the node in the segment tree array
		base[ptr++] = nodes[cur].val;		//sets the actual array

		int idx = -1, maxS = -1;
		for (auto& eIdx : nodes[cur].edges) {
			auto& e = edges[eIdx];
			if (e.v == p) { continue; }
			if (subtreeSize[e.v] > maxS) {
				maxS = subtreeSize[e.v];
				idx = e.v;
			}
		}

		if (idx >= 0) { hld(idx, cur); }

		for (auto& eIdx : nodes[cur].edges) {
			auto& e = edges[eIdx];
			if (e.v == p || e.v == idx) { continue; }
			chainNum++; hld(e.v, cur);
		}
	}

	//v should be an ancestor of u
	int query_up(int u, int v, SegTree& st) {
		int uchain, vchain = chainIdx[v];
		StVal ans(0);

		while (true) {
			uchain = chainIdx[u];
			if (uchain == vchain) {
				StVal qq = st.query(posInBase[v], posInBase[u]).v;
				ans = StVal(ans, qq);
				break;
			}

			int headU = chainHead[uchain];
			StVal qq = st.query(posInBase[headU], posInBase[u]);
			ans = StVal(ans, qq);
			u = anc[headU][0];	//Move to the parent of the head, i.e. to a new chain
		}

		return ans;
	}

	void updateVal(int u, int newVal, SegTree& st) {
		st.update(posInBase[u], newVal);
	}

	//O(log^2n)
	void query(int u, int v, SegTree& st) {
		int lca = LCA(u, v);
		StVal ans = query_up(u, lca, st);
		StVal temp = query_up(v, lca, st);
		ans = StVal(ans, temp);
		cout << ans.v << ' ';
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	tree t(n);
	for (int i = 0; i < n; i++) { cin >> t.nodes[i].val; }
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	base.clear(); base.resize(n);
	t.preprocess();
	t.hld(0, -1);
	SegTree segT(t.ptr);

	while (q--) {
		int type, a, b; cin >> type >> a >> b;
		if (type == 1) {
			a--;
			t.updateVal(a, b, segT);
		}
		else {
			a--; b--;
			t.query(a, b, segT);
		}
	}
}