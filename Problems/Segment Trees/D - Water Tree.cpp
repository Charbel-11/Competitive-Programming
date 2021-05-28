//https://codeforces.com/contest/343/problem/D
#include <iostream>
#include <vector>
using namespace std;

struct StVal {
	bool hasZ = 1; StVal() {}
	StVal(const StVal &v1, const StVal &v2) { hasZ = v1.hasZ | v2.hasZ; }
};

struct StUpdate {
	bool b = 0, f = 0; StUpdate() {}
	StUpdate(const bool _f, const bool _b = 0) : f(_f), b(_b) {}
	StUpdate(const StUpdate &u1, const StUpdate &u2) {
		if (u2.b) { f = u2.f; b = 1; }
		else { f = u1.f; b = u1.b; }
	}
	void apply(StVal &sv, const int lo, const int hi) { 
		if (b) { sv.hasZ = !f; }
	}
};

struct SegTree {
	int n;
	vector<StVal> st;
	vector<StUpdate> lazy;
	vector<int> leaves;

	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
		lazy.resize(st.size());
	}

	//lo, hi indices of the actual array; si is the index of the segment tree array
	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal();			//Set the actual array here
			leaves[lo] = si;
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

struct node { int id; vector<edge> edges; };

vector<int> start, finish, order;
struct tree {
	vector<node> nodes;
	vector<int> parent;
	int n;

	tree(int _n) : n(_n) { nodes.resize(n); start.resize(n, -1); finish.resize(n, -1); parent.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void preorder(int u, int &t) {
		start[u] = t; t++; order.push_back(u);
		for (auto &x : nodes[u].edges) {
			if (start[x.v] == -1) { parent[x.v] = u; preorder(x.v, t); }
		}
		finish[u] = t - 1;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	int tS = 0; t.preorder(0, tS);
	SegTree st(n);

	int q; cin >> q;
	while (q--) {
		int c, v; cin >> c >> v; v--;
		if (c == 1) { 
			StVal temp = st.query(start[v], finish[v]);
			//If the subtree contained a 0, we must make sure to put a 0 for the ancestors
			if (temp.hasZ && v) { st.update(start[t.parent[v]], start[t.parent[v]], StUpdate(0, 1)); }
			st.update(start[v], finish[v], StUpdate(1, 1));
		}
		else if (c == 2) { st.update(start[v], start[v], StUpdate(0, 1)); }
		else { 
			StVal temp = st.query(start[v], finish[v]);
			cout << !temp.hasZ << '\n';
		}
	}
}