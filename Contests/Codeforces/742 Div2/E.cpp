#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<int> base;

struct StVal {
	int length = 0, pref = 0, suf = 0;
	ll ans = 0; StVal() {}
	StVal(const int _v) : length(1), pref(_v), suf(_v) {}
	StVal(const StVal& v1, const StVal& v2) { 
		length = v1.length + v2.length;
		ans = v1.ans + v2.ans;

		int left = v1.suf, right = v2.pref;
		if (v1.length != v1.suf) { left++; }
		ans += (ll)left * right;

		pref = v1.pref;
		if (v1.pref == v1.length) { pref += v2.pref; }

		suf = v2.suf;
		if (v2.suf == v2.length) { suf += v1.suf; }
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
			st[si] = StVal(base[lo]);			
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

	int n, q; cin >> n >> q;
	vector<int> a(n); for (auto& x : a) { cin >> x; }

	base.resize(n); base[0] = 0;
	for (int i = 1; i < n; i++) {
		if (a[i] >= a[i - 1]) { base[i] = 1; }
	}
	
	SegTree st(n);
	while (q--) {
		int t; cin >> t;
		if (t == 1) {
			int x, y; cin >> x >> y; x--;
			
			a[x] = y;
			if (x > 0 && a[x] >= a[x - 1]) { base[x] = 1; }
			else { base[x] = 0; }
			st.update(x, base[x]);

			if (x < n - 1) {
				if (a[x + 1] >= a[x]) { base[x + 1] = 1; }
				else { base[x + 1] = 0; }
				st.update(x + 1, base[x + 1]);
			}
		}
		else {
			int l, r; cin >> l >> r; l--; r--;
			cout << st.query(l, r).ans + (r - l + 1) << '\n';
		}
	}
}