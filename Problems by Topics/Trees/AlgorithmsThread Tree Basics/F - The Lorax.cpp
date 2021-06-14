#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct StVal {
	ll seeds = 0, pots = 0; StVal() {}
	StVal(const ll _s, const ll _p) : seeds(_s), pots(_p) {}
	StVal(const StVal &v1, const StVal &v2) { seeds = v1.seeds + v2.seeds; pots = v1.pots + v2.pots; }
};

struct SegTree {
	int n;
	vector<int> leaves;
	vector<StVal> st;

	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
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
	void update(const int i, ll s, ll p) {
		int si = leaves[i];
		st[si] = StVal(st[si], StVal(s, p));
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
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
	vector<int> depth;
	int n;

	tree(int _n) : n(_n) {
		nodes.resize(n); depth.resize(n, 0);
		start.clear(); finish.clear(); order.clear();
		start.resize(n, -1); finish.resize(n, -1);
	}

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void preorder(int u, int &t) {
		start[u] = t; t++; order.push_back(u);
		for (auto &x : nodes[u].edges) {
			if (start[x.v] == -1) { depth[x.v] = depth[u] + 1; preorder(x.v, t); }
		}
		finish[u] = t - 1;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int c; cin >> c;

	while (c--) {
		int n, q; cin >> n >> q;
		tree t(n);
		for (int i = 0; i < n - 1; i++) {
			int u, v; cin >> u >> v; u--; v--;
			t.add_edge(u, v);
		}

		int tS = 0; t.preorder(0, tS);
		SegTree st(n);

		while (q--) {
			int a, b; ll x; cin >> a >> b >> x;
			a--; b--;
			if (x){
				st.update(start[a], x, 0);
				st.update(start[b], 0, x);
			}
			else {
				if (t.depth[a] > t.depth[b]) { swap(a, b); }
				StVal ss = st.query(start[b], finish[b]);
				ll seeds1 = ss.seeds, pots1 = ss.pots;
				cout << abs(seeds1 - pots1) << '\n';
			}
		}
	}
}