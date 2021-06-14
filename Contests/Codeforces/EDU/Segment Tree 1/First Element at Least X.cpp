#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

vector<int> base;

struct StVal {
	int v = 0; StVal() {}
	StVal(const int _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = max(v1, v2); }
	operator int() const { return v; }	//Casts StVal to int
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

	int BigEqX(const int x) { return BigEqX(x, 1, 0, n - 1); }
	int BigEqX(const int x, const int si, const int lo, const int hi) {
		if (st[si].v < x) { return -1; }
		if (lo == hi) { return lo; }

		const int mid = (lo + hi) >> 1;
		if (st[si << 1].v >= x) { return BigEqX(x, si << 1, lo, mid); }
		return BigEqX(x, si << 1 | 1, mid + 1, hi);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	base.resize(n); for (auto &x : base) { cin >> x; }

	SegTree st(n);
	for (int i = 0; i < m; i++) {
		int op; cin >> op;
		if (op == 1) {
			int i, v; cin >> i >> v;
			st.update(i, v);
		}
		else {
			int x; cin >> x;
			cout << st.BigEqX(x) << '\n';
		}
	}
}