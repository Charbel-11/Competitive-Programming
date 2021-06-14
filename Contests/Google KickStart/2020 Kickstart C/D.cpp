#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<ll> A;

struct StVal {
	ll v = 0; StVal() {}
	StVal(const ll _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = v1 + v2; }
	operator ll() const { return v; }
};

struct SegTree {
	int n;
	vector<int> leaves;
	vector<StVal> st;	//st[1] root, st[2] root's left child, st[3] root's right child...
	//To go to a child, *2 (l) or *2+1 (r)	To go to a parent: /2

	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
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

	//l and r inclusive, 0-indexed
	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
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

	int t; cin >> t;

	for (int qq = 1; qq <= t; qq++) {
		int n, q; cin >> n >> q;
		A.clear(); A.resize(n);
		for (auto &x : A) { cin >> x; }
		SegTree c(n), s(n);

		for (int i = 0; i < n; i++) {
			if (i % 2 == 0) { c.update(i, (i + 1)*A[i]);s.update(i, A[i]); }
			else { c.update(i, -(i + 1)*A[i]); s.update(i, -A[i]); }
			
		}

		ll ans = 0;

		while (q--) {
			char qq; cin >> qq;
			if (qq == 'U') {
				int x, v; cin >> x >> v; x--;
				A[x] = v;
				if (x % 2 == 0) { c.update(x, (x + 1)*A[x]); s.update(x, A[x]);}
				else { c.update(x, -(x + 1)*A[x]); s.update(x, -A[x]); }
			}
			else {
				ll l, r; cin >> l >> r; l--; r--;
				if (l % 2 == 0) {
					ans += c.query(l, r) - l * s.query(l, r);
				}
				else {
					ans += (-c.query(l, r) + l * s.query(l, r));
				}
			}
		}

		cout << "Case #" << qq << ": " << ans << endl;
	}
}