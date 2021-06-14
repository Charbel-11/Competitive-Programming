//https://www.spoj.com/problems/GSS7/
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
vector<ll> base;

struct StVal {
	ll maxPref = 0, maxSuf = 0, maxAns = 0, sum = 0; StVal() {}
	StVal(const ll _v) { maxPref = maxSuf = maxAns = max(0ll, _v); sum = _v; }
	StVal(const StVal &v1, const StVal &v2) {
		sum = v1.sum + v2.sum;
		maxPref = max(v1.maxPref, v1.sum + max(0ll, v2.maxPref));
		maxSuf = max(v2.maxSuf, v2.sum + max(0ll, v1.maxSuf));
		maxAns = max(v1.maxAns, v2.maxAns);
		maxAns = max(maxAns, v1.maxSuf + v2.maxPref);
	}
	operator ll() const { return maxAns; }
};

struct StUpdate {
	ll v = 0; bool b = 0; StUpdate() {}
	StUpdate(const ll v) : v(v) {}
	StUpdate(const StUpdate &u1, const StUpdate &u2) { 
		if (u2.b) { v = u2.v; b = 1; }
		else { v = u1.v; b = u1.b; }
	}	
	operator ll() const { return v; }
	void apply(StVal &sv, const int lo, const int hi) {	//Changes the current answer (Stval not Stupdate) according to the lazy value
		if (b) {
			sv.sum = (ll)(hi - lo + 1)*v;
			sv.maxPref = sv.maxSuf = sv.maxAns = max(sv.sum, 0ll);
		}
	}
};

struct SegTree {
	int n;
	vector<StVal> st;
	vector<StUpdate> lazy;

	SegTree(const int n) : n(n) {
		init(1, 0, n - 1);
		lazy.resize(st.size());
	}

	//lo, hi indices of the actual array; si is the index of the segment tree array
	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal(base[lo]);			//Set the actual array here
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid); init(rC, mid + 1, hi);
		st[si] = StVal(st[lC], st[rC]);
	}

	void updateLazy(const int si, const int lo, const int hi) {
		lazy[si].apply(st[si], lo, hi);
		if (lo != hi) {
			lazy[si << 1] = StUpdate(lazy[si << 1], lazy[si]);
			lazy[si << 1 | 1] = StUpdate(lazy[si << 1 | 1], lazy[si]);
		}
		lazy[si] = StUpdate();
	}

	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		updateLazy(si, lo, hi);
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	void update(const int l, const int r, const StUpdate u) { if (l <= r) update(l, r, u, 1, 0, n - 1); }
	void update(const int l, const int r, const StUpdate &u, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) {
			lazy[si] = StUpdate(lazy[si], u);
			updateLazy(si, lo, hi);
		}
		else {
			updateLazy(si, lo, hi);
			if (hi < l || r < lo) return;
			const int mid = (lo + hi) >> 1;
			update(l, r, u, si << 1, lo, mid);
			update(l, r, u, si << 1 | 1, mid + 1, hi);
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
		}
	}
};

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};
struct node { ll val; vector<int> edges; };

struct tree {
	vector<vector<int>> anc;
	vector<edge> edges;
	vector<node> nodes;
	vector<int> depth, subtreeSize;
	vector<int> chainHead, chainIdx, chainSize, chainPos, posInBase;
	int root, n, lg2, chainNum, ptr;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 0.0)));
		nodes.resize(n);
		anc.resize(n + 1); for (auto &x : anc) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0); subtreeSize.resize(n, 1);
		chainNum = 0; ptr = 0; posInBase.resize(n);
		chainHead.resize(n, -1); chainIdx.resize(n); chainPos.resize(n); chainSize.resize(n);
	}

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
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

	void hld(int cur, int p) {
		if (chainHead[chainNum] == -1) { chainHead[chainNum] = cur; }
		chainIdx[cur] = chainNum;
		chainPos[cur] = chainSize[chainNum];
		chainSize[chainNum]++;

		posInBase[cur] = ptr;	//sets the idx of the node in the segment tree array
		base[ptr++] = nodes[cur].val;		//sets the inital array

		int idx = -1, maxS = -1;
		for (auto &eIdx : nodes[cur].edges) {
			auto &e = edges[eIdx];
			if (e.v == p) { continue; }
			if (subtreeSize[e.v] > maxS) {
				maxS = subtreeSize[e.v];
				idx = e.v;
			}
		}

		if (idx >= 0) { hld(idx, cur); }

		for (auto &eIdx : nodes[cur].edges) {
			auto &e = edges[eIdx];
			if (e.v == p || e.v == idx) { continue; }
			chainNum++; hld(e.v, cur);
		}
	}

	//v should be an ancestor of u
	StVal query_up(int u, int v, bool withV, SegTree& st) {
		int uchain, vchain = chainIdx[v];
		StVal ans;

		while (true) {
			uchain = chainIdx[u];
			if (uchain == vchain) {
				StVal qq = st.query(posInBase[v] + (withV ^ 1), posInBase[u]);
				ans = StVal(qq, ans);
				break;
			}

			int headU = chainHead[uchain];
			StVal qq = st.query(posInBase[headU], posInBase[u]);
			ans = StVal(qq, ans);
			u = anc[headU][0];	//Move to the parent of the head, i.e. to a new chain
		}

		return ans;
	}

	void update_up(int u, int v, ll val, SegTree &st) {
		int uchain, vchain = chainIdx[v];
		StUpdate upd(val); upd.b = 1;
		while (true) {
			uchain = chainIdx[u];
			if (uchain == vchain) {
				st.update(posInBase[v], posInBase[u], upd);
				break;
			}
			int headU = chainHead[uchain];
			st.update(posInBase[headU], posInBase[u], upd);
			u = anc[headU][0];	//Move to the parent of the head, i.e. to a new chain
		}
	}

	//O(log^2n)
	StVal query(int u, int v, SegTree& st) {
		int lca = LCA(u, v);
		StVal t1 = query_up(u, lca, 1, st);
		StVal t2 = query_up(v, lca, 0, st);
		swap(t1.maxPref, t1.maxSuf);
		return StVal(t1, t2);
	}

	void update(int u, int v, ll val, SegTree &st) {
		int lca = LCA(u, v);
		update_up(u, lca, val, st); update_up(v, lca, val, st);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n; i++) { cin >> t.nodes[i].val; }
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	int Q; cin >> Q;

	base.clear(); base.resize(n);

	t.dfsPre(0, -1);
	t.preprocess();
	t.hld(0, -1);
	SegTree segT(t.ptr);

	while (Q--) {
		char op; cin >> op;
		if (op == '2') {
			int u, v; ll val; cin >> u >> v >> val; u--; v--;
			t.update(u, v, val, segT);
		}
		else {
			int u, v; cin >> u >> v; u--; v--;
			cout << t.query(u, v, segT) << '\n';
		}
	}
}