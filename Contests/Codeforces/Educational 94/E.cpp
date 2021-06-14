#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> base;

struct StVal {
	int v = 0, idx = -1; StVal() {}
	StVal(const int _v, const int _idx) : v(_v), idx(_idx) {}
	StVal(const StVal &v1, const StVal &v2) { 
		if (v1.v < v2.v) { v = v1.v; idx = v1.idx; }
		else { v = v2.v; idx = v2.idx; }
	}
	operator int() const { return v; }
};

struct StUpdate {
	int v = 0; StUpdate() {}
	StUpdate(const int v) : v(v) {}
	StUpdate(const StUpdate &u1, const StUpdate &u2) { v = u1 + u2; }	//Combine two lazy values
	operator int() const { return v; }
	void apply(StVal &sv, const int lo, const int hi) {
		sv.v += v;
	}
}; 

struct SegTree {
	int n;
	vector<StVal> st;
	vector<StUpdate> lazy;
	vector<int> leaves;

	SegTree() {}
	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
		lazy.resize(st.size());
	}

	//lo, hi indices of the actual array; si is the index of the segment tree array
	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal(base[lo], lo);			//Set the actual array here
			leaves[lo] = si;
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid); init(rC, mid + 1, hi);
		st[si] = StVal(st[lC], st[rC]);
	}

	void updateLazy(const int si, const int lo, const int hi) {
		lazy[si].apply(st[si], lo, hi);
		if (lo != hi) {
			lazy[si << 1] = StUpdate(lazy[si << 1], lazy[si]);
			lazy[si << 1 | 1] = StUpdate(lazy[si << 1 | 1], lazy[si]);
		}
		lazy[si] = StUpdate();
	}

	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		updateLazy(si, lo, hi);
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	void update(const int l, const int r, const StUpdate u) { if (l <= r) update(l, r, u, 1, 0, n - 1); }
	void update(const int l, const int r, const StUpdate &u, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) {
			lazy[si] = StUpdate(lazy[si], u);
			updateLazy(si, lo, hi);
		}
		else {
			updateLazy(si, lo, hi);
			if (hi < l || r < lo) return;
			const int mid = (lo + hi) >> 1;
			update(l, r, u, si << 1, lo, mid);
			update(l, r, u, si << 1 | 1, mid + 1, hi);
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
		}
	}
};

SegTree st;

int findMin(int i, int j) {
	if (i > j) { return 0; }
	int ans = j - i + 1;

	StVal minQ = st.query(i, j);
	int curMin = minQ.v, curIdx = minQ.idx;
	if (curMin >= ans) { return ans; }
	st.update(i, j, -curMin);
	
	int left = findMin(i, curIdx - 1), right = findMin(curIdx + 1, j);
	ans = min(ans, curMin + left + right);
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	base.resize(n); for (auto &x : base) { cin >> x; }
	st = SegTree(n);
	
	cout << findMin(0, n - 1) << '\n';
}