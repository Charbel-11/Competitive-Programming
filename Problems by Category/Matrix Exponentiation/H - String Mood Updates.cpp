#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

string s;

struct StVal {
	ll a00 = 0, a01 = 0, a10 = 0, a11 = 0; StVal() {}
	StVal(const char c) { 
		if (c == 'H') { a00 = a10 = 1; a11 = a01 = 0; }
		else if (c == 'S' || c == 'D') { a00 = a10 = 0; a11 = a01 = 1; }
		else if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') { a00 = a11 = 0; a01 = a10 = 1; }
		else if (c == '?') { a00 = 19; a01 = 7; a10 = 6; a11 = 20; }
		else { a00 = a11 = 1; a01 = a10 = 0; }
	}
	StVal(const StVal &v1, const StVal &v2) {
		a00 = v1.a00*v2.a00 + v1.a01*v2.a10; a00 %= mod;
		a01 = v1.a00*v2.a01 + v1.a01*v2.a11; a01 %= mod;
		a10 = v1.a10*v2.a00 + v1.a11*v2.a10; a10 %= mod;
		a11 = v1.a10*v2.a01 + v1.a11*v2.a11; a11 %= mod;
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
			st[si] = StVal(s[lo]);			//Set the actual array here
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
	void update(const int i, char c) {
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
	cin >> s;
	SegTree st(n);
	for (int i = 0; i < n; i++) { }
	cout << st.query(0, n - 1).a00 << '\n';

	while (q--) {
		int idx; cin >> idx; idx--;
		char c; cin >> c;
		st.update(idx, c);
		cout << st.query(0, n - 1).a00 << '\n';
	}
}
