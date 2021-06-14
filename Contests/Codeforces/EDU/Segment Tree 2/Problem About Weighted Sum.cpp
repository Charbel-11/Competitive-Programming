#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<ll> base;

ll sum(int i, int j) {
	ll s1 = (ll)j * (j + 1) / 2;
	ll s2 = (ll)(i - 1)*i / 2;
	return s1 - s2;
}

struct StVal {
	ll v = 0; StVal() {}
	StVal(const ll _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = v1 + v2; }
	operator ll() const { return v; }
};

struct StUpdate {
	ll v = 0; StUpdate() {}
	StUpdate(const ll v) : v(v) {}
	StUpdate(const StUpdate &u1, const StUpdate &u2) { v = u1 + u2; }	//Combine two lazy values
	operator ll() const { return v; }
	void apply(StVal &sv, const int lo, const int hi) {	
		sv.v += this->v * (hi - lo + 1);				
	}
};

struct StUpdate2 {
	ll v = 0; StUpdate2() {}
	StUpdate2(const ll v) : v(v) {}
	StUpdate2(const StUpdate2 &u1, const StUpdate2 &u2) { v = u1 + u2; }	//Combine two lazy values
	operator ll() const { return v; }
	void apply(StVal &sv, const int lo, const int hi) {
		sv.v += this->v * sum(lo + 1, hi + 1);
	}
};

template <class V, class U>
struct SegTree {
	int n;
	vector<V> st;
	vector<U> lazy;
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
			st[si] = V(base[lo]);			//Set the actual array here
			leaves[lo] = si;
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid); init(rC, mid + 1, hi);
		st[si] = V(st[lC], st[rC]);
	}

	void updateLazy(const int si, const int lo, const int hi) {
		lazy[si].apply(st[si], lo, hi);
		if (lo != hi) {
			lazy[si << 1] = U(lazy[si << 1], lazy[si]);
			lazy[si << 1 | 1] = U(lazy[si << 1 | 1], lazy[si]);
		}
		lazy[si] = U();
	}

	V query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : V(); }
	V query(const int l, const int r, const int si, const int lo, const int hi) {
		updateLazy(si, lo, hi);
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return V(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	void update(const int l, const int r, const U u) { if (l <= r) update(l, r, u, 1, 0, n - 1); }
	void update(const int l, const int r, const U &u, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) {
			lazy[si] = U(lazy[si], u);
			updateLazy(si, lo, hi);
		}
		else {
			updateLazy(si, lo, hi);
			if (hi < l || r < lo) return;
			const int mid = (lo + hi) >> 1;
			update(l, r, u, si << 1, lo, mid);
			update(l, r, u, si << 1 | 1, mid + 1, hi);
			st[si] = V(st[si << 1], st[si << 1 | 1]);
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	base.resize(n);
	for (auto &x : base) { cin >> x; }

	SegTree<StVal, StUpdate> stUsual(n);
	for (int i = 0; i < n; i++) { base[i] *= (i + 1); }
	SegTree<StVal, StUpdate2> stPoly(n);

	while (m--) {
		int type; cin >> type;
		if (type == 1) {
			int l, r; ll d; cin >> l >> r >> d; l--; r--;
			stUsual.update(l, r, d);
			stPoly.update(l, r, d);
		}
		else {
			int l, r; cin >> l >> r; l--; r--;
			ll ans = stPoly.query(l, r) - stUsual.query(l, r) * l;
			cout << ans << '\n';
		}
	}
}