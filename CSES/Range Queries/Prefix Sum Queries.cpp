#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<ll> base;

struct StVal {
	ll v = 0, maxPref = 0; StVal() {}
	StVal(const ll _v) : v(_v) { maxPref = max(0ll, _v); }
	StVal(const StVal& v1, const StVal& v2) { 
		v = v1.v + v2.v;
		maxPref = max({ v1.maxPref, v1.v + v2.maxPref });
	}
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
	StVal query(const int l, const int r) { return (l <= r && l < n&& r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	//Change a leaf and update its ancestors' values
	void update(const int i, ll c) {
		int si = leaves[i];
		st[si] = StVal(c);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	base.resize(n);
	for (auto& x : base) { cin >> x; }

	SegTree st(n);
	while (q--) {
		int t; cin >> t;
		if (t == 1) {
			int k; ll u; cin >> k >> u; k--;
			st.update(k, u);
		}
		else {
			int l, r; cin >> l >> r; l--; r--;
			cout << st.query(l, r).maxPref << '\n';
		}
	}
}