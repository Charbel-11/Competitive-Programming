#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
typedef long long ll;

struct StVal {
	double v = 0.0; StVal() {}
	StVal(const double _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = v1.v + v2.v; }
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
	void update(const int i, double v) {
		int si = leaves[i];
		st[si] = StVal(v);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
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

	tree(int _n) : n(_n) { nodes.resize(n);	start.resize(n, -1); finish.resize(n, -1); }

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

	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	int tS = 0; t.preorder(0, tS);
	SegTree st(n);

	double eps = 1e-7;
	int q; cin >> q;
	while (q--) {
		int t, x, y; cin >> t >> x >> y;
		if (t == 1) {
			x--;
			double lg10 = log10(y);
			st.update(start[x], lg10);
		}
		else {
			x--; y--;
			double s1 = st.query(start[x], finish[x]).v;
			double s2 = st.query(start[y], finish[y]).v;

			if (s1 - s2 >= 9 - eps) { cout << 1000000000 << '\n'; }
			else { cout << setprecision(7) << fixed << pow(10, s1 - s2) << '\n'; }
		}
	}
}