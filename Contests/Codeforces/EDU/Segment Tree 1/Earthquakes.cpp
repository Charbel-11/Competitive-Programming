#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 1e9 + 10;

struct StVal {
	int v = 0; StVal() {}
	StVal(const int _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = min(v1, v2); }
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
			st[si] = StVal(INF);			//Set the actual array here
			leaves[lo] = si;
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid); init(rC, mid + 1, hi);
		st[si] = StVal(st[lC], st[rC]);
	}

	//l and r inclusive, 0-indexed
	int query(const int l, const int r, const int p) { return (l <= r && l < n && r >= 0) ? query(l, r, p, 1, 0, n - 1) : 0; }
	int query(const int l, const int r, const int p, const int si, const int lo, const int hi) {
		if (st[si].v > p) { return 0; }
		if (lo > r || hi < l) { return 0; }
		if (lo == hi) { update(lo, INF); return 1; }

		const int mid = (lo + hi) >> 1;
		return query(l, r, p, si << 1, lo, mid) + query(l, r, p, si << 1 | 1, mid + 1, hi);
	}

	//Change a leaf and update its ancestors' values
	void update(const int i, int c) {
		int si = leaves[i];
		st[si] = StVal(c);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	SegTree st(n);

	while (m--) {
		int op; cin >> op;
		if (op == 1) {
			int i, h; cin >> i >> h;
			st.update(i, h);
		}
		else {
			int l, r, p; cin >> l >> r >> p; r--;
			cout << st.query(l, r, p) << '\n';
		}
	}
}