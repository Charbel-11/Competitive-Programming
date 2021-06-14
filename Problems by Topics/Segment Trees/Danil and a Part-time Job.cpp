//https://codeforces.com/contest/877/problem/E

#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

vector<int> base;

struct StVal {
	int v = 0; StVal() {}
	StVal(const int _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = v1 + v2; }
	operator int() const { return v; }
};

struct StUpdate {
	int v = 0; StUpdate() {}
	StUpdate(const int v) : v(v) {}
	StUpdate(const StUpdate &u1, const StUpdate &u2) { v = u1 ^ u2; }	//Combine two lazy values
	operator int() const { return v; }
	void apply(StVal &sv, const int lo, const int hi) {	
		if (v) sv.v = (hi - lo + 1) - sv.v;
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
			st[si] = StVal(base[lo]);			//Set the actual array here
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

	void flip(const int l, const int r) { if (l <= r) update(l, r, StUpdate(1), 1, 0, n - 1); }
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

struct node { vector<edge> edges; };

vector<int> start, finish, order;
struct tree {
	vector<node> nodes;
	int n;

	tree(int _n): n(_n) { nodes.resize(n); start.resize(n, -1); finish.resize(n, -1); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void preorder(int u, int &t) {
		start[u] = t++; order.push_back(u);
		for (auto &e : nodes[u].edges) {
			if (start[e.v] == -1) { preorder(e.v, t); }
		}
		finish[u] = t - 1;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n); base.resize(n);
	for (int i = 0; i < n - 1; i++) {
		int p; cin >> p; p--;
		t.add_edge(i + 1, p);
	}

	int tS = 0; t.preorder(0, tS);

	for (int i = 0; i < n; i++) {
		int on; cin >> on;
		base[start[i]] = on;
	}

	SegTree st(n);
	int q; cin >> q;
	while (q--) {
		string op; cin >> op;
		if (op[0] == 'g') {
			int v; cin >> v; v--;
			cout << st.query(start[v], finish[v]) << '\n';
		}
		else {
			int v; cin >> v; v--;
			st.flip(start[v], finish[v]);
		}
	}
}