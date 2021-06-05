#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
vector<ll> base;

struct StVal {
	ll v = 0; StVal() {}
	StVal(const ll _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = v1 + v2; }
	operator ll() const { return v; }
};

struct StUpdate {
	bool set = 0; ll add = 0, val = 0; StUpdate() {}
	StUpdate(const ll v, const ll a, const bool b) {
		if (b) { set = 1; add = 0; val = v; }
		else { set = 0, add = a; val = 0; }
	}
	StUpdate(const StUpdate &u1, const StUpdate &u2) {
		if (u2.set) { set = 1; val = u2.val; add = 0; }
		else {
			if (u1.set) { set = 1; val = u1.val + u2.add; }
			else { set = 0; val = 0; add = u1.add + u2.add; }
		}
	}	//Combine two lazy values
	void apply(StVal &sv, const int lo, const int hi) {	//Changes the current answer (Stval not Stupdate) according to the lazy value
		if (set) { sv.v = val * (hi - lo + 1); }
		else { sv.v += add * (hi - lo + 1); }
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

	int n, q; cin >> n >> q;
	base.resize(n); for (auto &x : base) { cin >> x; }
	SegTree st(n);

	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int a, b; ll x; cin >> a >> b >> x; a--; b--;
			st.update(a, b, StUpdate(0, x, 0));
		}
		else if (op == 2) {
			int a, b; ll x; cin >> a >> b >> x; a--; b--;
			st.update(a, b, StUpdate(x, 0, 1));
		}
		else {
			int a, b; cin >> a >> b; a--; b--;
			cout << st.query(a, b) << '\n';
		}
	}
}