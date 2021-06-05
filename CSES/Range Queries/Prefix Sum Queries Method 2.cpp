#include <iostream>
#include <vector>
#include <climits>
using namespace std;
typedef long long ll;

vector<ll> base;

struct StVal {
	ll vS = 0, vM = -LLONG_MAX; StVal() {}
	StVal(const ll _v) : vS(_v), vM(_v) {}
	StVal(const StVal& v1, const StVal& v2) { vM = max(v1.vM, v2.vM); vS = v1.vS + v2.vS; }
};

struct StUpdate {
	ll v = 0; StUpdate() {}
	StUpdate(const ll v) : v(v) {}
	StUpdate(const StUpdate& u1, const StUpdate& u2) { v = u1 + u2; }
	operator ll() const { return v; }
	void apply(StVal& sv, const int lo, const int hi) {
		sv.vM += this->v;
		sv.vS += this->v * (hi - lo + 1);
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

	StVal query(const int l, const int r) { return (l <= r && l < n&& r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		updateLazy(si, lo, hi);
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	void update(const int l, const int r, const StUpdate u) { if (l <= r) update(l, r, u, 1, 0, n - 1); }
	void update(const int l, const int r, const StUpdate& u, const int si, const int lo, const int hi) {
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

	int n, q; cin >> n >> q;
	base.resize(n);
	for (auto& x : base) { cin >> x; }
	for (int i = 1; i < n; i++) { base[i] += base[i - 1]; }

	SegTree st(n);
	while (q--) {
		int t; cin >> t;
		if (t == 1) {
			int k; ll u; cin >> k >> u; k--;
			ll prevVal = st.query(k, k).vS - st.query(k - 1, k - 1).vS;
			st.update(k, n - 1, StUpdate(u - prevVal));
		}
		else {
			int l, r; cin >> l >> r; l--; r--;
			ll prefMax = st.query(l, r).vM;
			prefMax -= st.query(l - 1, l - 1).vS;
			cout << max(0ll, prefMax) << '\n';
		}
	}
}