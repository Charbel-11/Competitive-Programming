#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct StVal {
	ll maxPref = 0, maxSuff = 0, sum = 0, ans = 0;
	StVal() {}
	StVal(const ll _v) { sum = _v; maxPref = maxSuff = ans = max(_v, 0ll); }
	StVal(const StVal &v1, const StVal &v2) {
		sum = v1.sum + v2.sum;
		ans = max(v1.ans, v2.ans);
		ans = max(ans, v1.maxSuff + v2.maxPref);
		maxSuff = max(v2.maxSuff, v1.maxSuff + v2.sum);
		maxPref = max(v1.maxPref, v1.sum + v2.maxPref);
	}
};

struct StUpdate {
	ll v = 0; bool c = false; StUpdate() {}
	StUpdate(const ll v, const bool _b) : v(v), c(_b) {}
	StUpdate(const StUpdate &u1, const StUpdate &u2) {
		if (u2.c) { c = true; v = u2.v; }
		else { c = u1.c; v = u1.v; }
	}
	void apply(StVal &sv, const int lo, const int hi) {
		if (c) {
			if (v > 0) { sv.maxPref = sv.maxSuff = sv.sum = sv.ans = v * (hi - lo + 1); }
			else { sv.maxPref = sv.maxSuff = sv.ans = 0; sv.sum = v * (hi - lo + 1); }
		}
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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	SegTree st(n);
	while (m--) {
		int l, r; ll v; cin >> l >> r >> v;
		st.update(l, r - 1, StUpdate(v, true));
		cout << st.query(0, n - 1).ans << '\n';
	}
}