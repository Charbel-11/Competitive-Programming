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
typedef long long ll;
vector<int> base;

struct StVal {
	int v = 0; StVal() {}
	StVal(const int _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = max(v1, v2); }
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
	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
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
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}
};
struct node { vector<int> edges; };

struct tree {
	vector<vector<int>> anc;
	vector<edge> edges;
	vector<node> nodes;
	vector<int> depth, subtreeSize;
	vector<int> chainHead, chainIdx, posInBase;
	vector<int> chainSize, chainPos;		//optional
	int root, n, lg2, chainNum, ptr;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 0.0)));
		nodes.resize(n);
		anc.resize(n + 1); for (auto &x : anc) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0); subtreeSize.resize(n, 1);
		chainNum = 0; ptr = 0; posInBase.resize(n);
		chainHead.resize(n, -1); chainIdx.resize(n); 
		chainPos.resize(n); chainSize.resize(n); 
	}

	void add_edge(int u, int v, int w) {
		edge e1(u, v, w); edge e2(v, u, w);		
		nodes[u].edges.push_back(edges.size()); edges.push_back(e1);
		nodes[v].edges.push_back(edges.size()); edges.push_back(e2);
	}

	void dfsPre(int u, int p) {
		for (auto &eIdx : nodes[u].edges) {
			auto &e = edges[eIdx];
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
			for (auto &eIdx : nodes[cur].edges) {
				auto &e = edges[eIdx];
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

	void hld(int cur, int p, int cost) {
		if (chainHead[chainNum] == -1) { chainHead[chainNum] = cur; }
		chainIdx[cur] = chainNum;
		chainPos[cur] = chainSize[chainNum];
		chainSize[chainNum]++;

		posInBase[cur] = ptr;	//sets the idx of the node in the segment tree array
		base[ptr++] = cost;		//sets the actual array

		int idx = -1, maxS = -1, nCost = -1;
		for (auto &eIdx : nodes[cur].edges) {
			auto &e = edges[eIdx];
			if (e.v == p) { continue; }
			if (subtreeSize[e.v] > maxS) {
				maxS = subtreeSize[e.v]; 
				idx = e.v; nCost = e.w;
			}
		}

		if (idx >= 0) { hld(idx, cur, nCost); }

		for (auto &eIdx : nodes[cur].edges) {
			auto &e = edges[eIdx];
			if (e.v == p || e.v == idx) { continue; }
			chainNum++; hld(e.v, cur, e.w);
		}
	}

	//v should be an ancestor of u
	StVal query_up(int u, int v, SegTree& st) {
		int uchain, vchain = chainIdx[v];
		StVal ans(-1);

		while (true) {
			uchain = chainIdx[u];
			if (uchain == vchain) {
				//In this particular problem, the values were on the edges, hence the break here and the +1 below
				if (u == v) { break; }		
				StVal qq = st.query(posInBase[v] + 1, posInBase[u]).v;	//+1 to avoid the edge above the lca
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

	//For node values
	void updateVal(int u, int newVal, SegTree& st) {
		st.update(posInBase[u], newVal);
	}

	//For edge values, we update the node which has that edge as parent
	void updateEdgeVal(int eN, int newVal, SegTree& st) {
		int u1 = edges[eN * 2].u, v1 = edges[eN * 2].v;
		int lower = (depth[u1] > depth[v1] ? u1 : v1);
		st.update(posInBase[lower], newVal);
	}

	//O(log^2n)
	//For node queries, might count the LCA twice
	void query(int u, int v, SegTree& st) {
		int lca = LCA(u, v);
		StVal ans = query_up(u, lca, st); 
		StVal temp = query_up(v, lca, st);
		ans = StVal(ans, temp);
		cout << ans.v << '\n';
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		tree t(n);
		for (int i = 0; i < n - 1; i++) {
			int u, v, w; cin >> u >> v >> w; u--; v--;
			t.add_edge(u, v, w);
		}

		base.clear(); base.resize(n);

		t.preprocess();
		t.hld(0, -1, -1);		//Min possible cost assumed = -1
		SegTree segT(t.ptr);


	}
}