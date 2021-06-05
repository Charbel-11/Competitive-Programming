#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll MIN = -1e9 - 4;
vector<ll> base;

struct StVal {
	ll maxPref = MIN, maxSuf = MIN, maxAns = 0, sum = 0; StVal() {}
	StVal(const ll _v) { maxPref = maxSuf = sum = _v; maxAns = max(0ll, _v); }
	StVal(const StVal &v1, const StVal &v2) {
		sum = v1.sum + v2.sum;
		maxPref = max(v1.maxPref, v1.sum + max(0ll, v2.maxPref));
		maxSuf = max(v2.maxSuf, v2.sum + max(0ll, v1.maxSuf));
		maxAns = max(v1.maxAns, v2.maxAns);
		maxAns = max(maxAns, v1.maxSuf + v2.maxPref);
	}
	operator ll() const { return maxAns; }	//Casts StVal to int
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
			st[si] = StVal(base[lo]);			//Set the actual array here
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

	int n, m; cin >> n >> m;
	base.resize(n); for (auto &x : base) { cin >> x; }

	SegTree st(n);
	for (int i = 0; i < m; i++) {
		int k, x; cin >> k >> x; k--;
		st.update(k, x);
		cout << st.query(0, n - 1) << '\n';
	}
}