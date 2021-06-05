#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<ll> base;
struct StVal {
	ll v = 0; StVal() {}
	StVal(const ll _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = v1 + v2; }
	operator ll() const { return v; }	//Casts StVal to int
};

struct SegTree {
	int n;
	vector<int> leaves;
	vector<StVal> st;	//st[1] root, st[2] root's left child, st[3] root's right child...
	//To go to a child, *2 (l) or *2+1 (r)	To go to a parent: /2

	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
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

	//l and r inclusive, 0-indexed
	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	//Change a leaf and update its ancestors' values
	void update(const int i, int c) {
		int si = leaves[i];
		st[si] = StVal(c);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
	}
};


struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int val; vector<edge> edges; };

vector<int> start, finish, order;
struct tree {
	vector<node> nodes;
	int n;

	tree(int _n) : n(_n) { nodes.resize(n); start.resize(n, -1); finish.resize(n, -1); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void preorder(int u, int &t) {
		start[u] = t; t++; order.push_back(u);
		for (auto &x : nodes[u].edges) {
			if (start[x.v] == -1) { preorder(x.v, t); }
		}
		finish[u] = t - 1;
	}
};


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q; 
	base.resize(n); tree t(n);
	for (int i = 0; i < n; i++) { int cur; cin >> cur; t.nodes[i].val = cur; }
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	int timeStamp = 0; t.preorder(0, timeStamp);

	for (int i = 0; i < n; i++) { base[i] = t.nodes[order[i]].val; }
	SegTree st(n);
	
	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int s; ll x; cin >> s >> x; s--;
			t.nodes[s].val = x; st.update(start[s], x);
		}
		else {
			int u; cin >> u; u--;
			cout << st.query(start[u], finish[u]) << '\n';
		}
	}
}