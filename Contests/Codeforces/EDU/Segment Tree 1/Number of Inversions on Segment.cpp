#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<int> base;

struct StVal {
	vector<int> freq = vector<int>(41, 0);
	vector<int> freqP = vector<int>(41, 0);
	ll inv = 0; StVal() {}
	StVal(const int _v) {
		freq[_v] = 1;
		for (int i = _v; i <= 40; i++) { freqP[i] = 1; }
	}
	StVal(const StVal &v1, const StVal &v2) {
		inv = v1 + v2;

		for (int i = 2; i <= 40; i++) {
			ll a = v1.freq[i];
			if (a == 0) { continue; }
			ll b = v2.freqP[i - 1];
			inv += a * b;
		}

		for (int i = 1; i < 41; i++) {
			freq[i] = v1.freq[i] + v2.freq[i];
			freqP[i] = freq[i] + freqP[i - 1];
		}
	}
	operator ll() const { return inv; }	//Casts StVal to int
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
	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	void update(const int i, const int x) {
		int si = leaves[i];
		st[si] = StVal(x);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	base.resize(n);
	for (auto &x : base) { cin >> x; }
	SegTree st(n);

	while (q--) {
		int type; cin >> type;
		int x, y; cin >> x >> y;
		if (type == 1) {
			x--; y--;
			cout << st.query(x, y) << '\n';
		}
		else {
			x--;
			st.update(x, y);
			base[x] = y;
		}
	}
}