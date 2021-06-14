#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct StVal {
	ll v = 0; StVal() {}
	StVal(const ll _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = max(v1.v, v2.v); }
};

struct StUpdate {
	int v = 0; StUpdate() {}
	StUpdate(const int _v) : v(_v) {}
	StUpdate(const StUpdate &u1, const StUpdate &u2) { v = u1.v + u2.v; }
	void apply(StVal &sv, const int lo, const int hi) { sv.v += v; }
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
			st[si] = StVal();			//Set the actual array here
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

	int query(const int l, const int x) { return query(l, x, 1, 0, n - 1); }
	int query(const int l, const int x, const int si, const int lo, const int hi) {
		updateLazy(si, lo, hi);
		if (st[si].v < x || hi < l) { return -1; }
		if (lo == hi) { return lo; }

		const int mid = (lo + hi) >> 1;
		if (mid >= l) {
			int c1 = query(l, x, si << 1, lo, mid);
			if (c1 != -1) { return c1; }
		}
		return query(l, x, si << 1 | 1, mid + 1, hi);
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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	SegTree st(n);
	while (m--) {
		int type; cin >> type;
		if (type == 1) {
			int l, r, v; cin >> l >> r >> v;
			st.update(l, r - 1, StUpdate(v));
		}
		else {
			int x, l; cin >> x >> l;
			cout << st.query(l, x) << '\n';
		}
	}
}