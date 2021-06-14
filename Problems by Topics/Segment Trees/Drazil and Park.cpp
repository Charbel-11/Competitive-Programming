//https://codeforces.com/contest/515/problem/E

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<ll> baseAdd, baseRem;

struct StVal {
	ll Radd = 0, Lrem = 0;
	int idxR, idxL;
	StVal() {}
	StVal(const ll a, const ll b, int idx) { Radd = a; Lrem = b; idxR = idxL = idx; }
	StVal(const StVal &v1, const StVal &v2) {
		if (v1.Radd > v2.Radd) { Radd = v1.Radd; idxR = v1.idxR; }
		else { Radd = v2.Radd; idxR = v2.idxR; }
		if (v1.Lrem > v2.Lrem) { Lrem = v1.Lrem; idxL = v1.idxL; }
		else { Lrem = v2.Lrem; idxL = v2.idxL; }
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
			st[si] = StVal(baseAdd[lo], baseRem[lo], lo);			//Set the actual array here
			leaves[lo] = si;
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid); init(rC, mid + 1, hi);
		st[si] = StVal(st[lC], st[rC]);
	}

	//l and r inclusive, 0-indexed
	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(-1e15, -1e15, -1); }
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

	int n, m; cin >> n >> m;
	vector<ll> d(n), h(n);
	for (auto &x : d) { cin >> x; }
	for (auto &x : h) { cin >> x; }

	baseAdd.resize(2 * n, 0); baseAdd[0] = h[0] * 2;
	for (int i = 1; i < 2 * n; i++) {
		baseAdd[i] = h[i%n] * 2 - h[(i - 1 + n) % n] * 2 + baseAdd[i - 1] + d[(i - 1 + n) % n];
	}
	baseRem.resize(2 * n, 0); baseRem[0] = h[0] * 2;
	for (int i = 1; i < 2 * n; i++) {
		baseRem[i] = h[i%n] * 2 - h[(i - 1 + n) % n] * 2 + baseRem[i - 1] - d[(i - 1 + n) % n];
	}

	SegTree st(2 * n);

	while (m--) {
		int a, b; cin >> a >> b; a--; b--;
		int l = b + 1, r = 0;
		if (a <= b) { r = n + a - 1; }
		else { r = a - 1; }

		StVal res = st.query(l, r);
		if (res.idxR > res.idxL) { cout << res.Radd + res.Lrem << '\n'; }
		else {
			StVal c1 = st.query(l, res.idxR - 1);
			ll ans = res.Radd + c1.Lrem;
			StVal c2 = st.query(res.idxL + 1, r);
			ans = max(ans, res.Lrem + c2.Radd);
			cout << ans << '\n';
		}
	}
}