#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int r;

int base[200001][2][2];

struct StVal {
	int m[2][2];
	StVal() {}
	StVal(const int _m[2][2]) {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				m[i][j] = _m[i][j];
	}
	StVal(const StVal &v1, const StVal &v2) {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++) {
				m[i][j] = 0;
				for (int k = 0; k < 2; k++) {
					m[i][j] += v1.m[i][k] * v2.m[k][j];
					m[i][j] %= r;
				}
			}
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
	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
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

	int n, m;
	cin >> r >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> base[i][0][0] >> base[i][0][1] >> base[i][1][0] >> base[i][1][1];
	}

	SegTree st(n);
	while (m--) {
		int l, r; cin >> l >> r; l--; r--;
		StVal v = st.query(l, r);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				cout << v.m[i][j] << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}
}