#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct StVal {
	ll b = 0, diff = 0; StVal() {}
	StVal(const ll _b, const ll _d) : b(_b), diff(_d) {}
	StVal(const StVal &v1, const StVal &v2) { b = v1.b + v2.b; diff = v1.diff + v2.diff; }
};

struct StUpdate {
	bool c1 = false, c2 = false, black = false, diff = false; 
	StUpdate() {}
	StUpdate(const bool _b, const bool _c1, const bool _d, const bool _c2) : black(_b), c1(_c1), diff(_d), c2(_c2) {}
	StUpdate(const StUpdate &u1, const StUpdate &u2) {
		if (u2.c1) { c1 = 1; black = u2.black; }
		else { c1 = u1.c1; black = u1.black; }

		if (u2.c2) { c2 = 1; diff = u2.diff; }
		else { c2 = u1.c2; diff = u1.diff; }
	}
	void apply(StVal &sv, const int lo, const int hi) {
		if (c1) {
			if (black) { sv.b = hi - lo + 1; }
			else { sv.b = 0; }
		}
		
		if (c2) { sv.diff = diff; }
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

	int n; cin >> n;
	SegTree st(1000003);
	while (n--) {
		char type; cin >> type;
		int x, len; cin >> x >> len; x += 500001;
		int l = x, r = x + len - 1;
		bool b = type == 'B';

		st.update(l, r, StUpdate(b, true, false, false));
		st.update(l + 1, r, StUpdate(false, false, false, true));

		bool isB = st.query(l - 1, l - 1).b;
		st.update(l, l, StUpdate(false, false, !b && isB, true));
		isB = st.query(r + 1, r + 1).b;
		st.update(r + 1, r + 1, StUpdate(false, false, b && !isB, true));

		StVal ans = st.query(0, 1000002);
		cout << ans.diff << " " << ans.b << '\n';
	}
}