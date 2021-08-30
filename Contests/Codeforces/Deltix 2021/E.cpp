#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<ll> base;

struct StVal {
	ll maxPref = 0, minPref = 0, sum = 0;
	StVal() {}
	StVal(const ll _v) { sum = _v; maxPref = _v; minPref = _v; }
	StVal(const StVal& v1, const StVal& v2) {
		sum = v1.sum + v2.sum;
		maxPref = max(v1.maxPref, v1.sum + max(0ll, v2.maxPref));
		minPref = min(v1.minPref, v1.sum + min(0ll, v2.minPref));
	}
};

struct SegTree {
	int n;
	vector<int> leaves;
	vector<StVal> st;	//st[1] root; To go to a child, *2 (l) or *2+1 (r);	To go to a parent: /2

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
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	vector<ll> a(n); for (auto& x : a) { cin >> x; }
	vector<ll> b(n); for (auto& x : b) { cin >> x; }

	base.resize(n);
	for (int i = 0; i < n; i++) {
		base[i] = b[i] - a[i];
	}

	for (int i = 1; i < n; i++) {
		a[i] += a[i - 1];
		b[i] += b[i - 1];
	}

	SegTree st(n);
	while (q--) {
		int l, r; cin >> l >> r; l--; r--;

		ll sum1 = a[r] - (l ? a[l - 1] : 0);
		ll sum2 = b[r] - (l ? b[l - 1] : 0);
		if (sum1 != sum2) { cout << -1 << '\n'; }
		else {
			StVal curV = st.query(l, r);
			if (curV.minPref < 0) { cout << -1 << '\n'; }
			else { cout << curV.maxPref << '\n'; }
		}
	}
}