#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

struct StVal {
	int v = 0; StVal() {}
	StVal(const int _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = v1 & v2; }
	operator int() const { return v; }
};

struct SegTree {
	int n;
	vector<StVal> st;
	vector<int> leaves;

	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
	}

	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) st.resize(si + 1);
			st[si] = StVal();
			leaves[lo] = si;
		}
		else {
			const int mid = (lo + hi) >> 1;
			init(si << 1, lo, mid);
			init(si << 1 | 1, mid + 1, hi);
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
		}
	}

	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	void update(const int i, int c) { 
		int si = leaves[i];
		st[si] = StVal(c);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
	}
};

int main() {
	int n, m; cin >> n >> m;
	vector<pair<pair<int, int>, int>> in(m);
	for (int i = 0; i < m; i++) {
		int l, r, q; cin >> l >> r >> q; l--;
		in[i] = { {l, r}, q };
	}

	vector<vector<int>> nums(n+1);
	for (auto &x : nums) { x.resize(31); }
	vector<int> finalNums(n, 0);

	for (int b = 0; b < 31; b++) {
		for (int i = 0; i < m; i++) {
			if ((in[i].second >> b) & 1) {
				nums[in[i].first.first][b]++;
				nums[in[i].first.second][b]--;
			}
		}

		for (int i = 0; i < n; i++) {
			if (i) { nums[i][b] += nums[i - 1][b]; }
			if (nums[i][b]) {
				finalNums[i] |= (1 << b);
			}
		}
	}

	SegTree sT(n);
	for (int i = 0; i < n; i++) {
		sT.update(i, finalNums[i]);
	}

	for (int i = 0; i < m; i++) {
		StVal r = sT.query(in[i].first.first, in[i].first.second-1);
		if (r.v != in[i].second) {
			cout << "NO" << endl; return 0;
		}
	}

	cout << "YES" << endl;
	for (int i = 0; i < n; i++) {
		cout << finalNums[i] << " ";
	}
}