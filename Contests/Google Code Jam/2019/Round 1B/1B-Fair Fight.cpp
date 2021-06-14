#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

struct StVal {
	int v = 0; StVal() {}
	StVal(const int _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = max(v1, v2); }
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

	//l and r inclusive, 0-indexed
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

int findTooGd(vector<int> &c, vector<int>& d, SegTree& C, SegTree& D, int K, int pivotIdx, bool direction) {	//1 right, 0 left
	int l = direction ? pivotIdx : 0, r = direction ? c.size() - 1 : pivotIdx;
	while (l < r) {
		int bound = (l + r) / 2;
		if (direction) { bound = (l + r + 1) / 2; }

		int mC, mD;
		if (direction) {
			mC = C.query(pivotIdx, bound);
			mD = D.query(pivotIdx, bound);
		}
		else {
			mC = C.query(bound, pivotIdx);
			mD = D.query(bound, pivotIdx);
		}

		if (mC == c[pivotIdx] && mC > mD + K) {
			if (direction) { l = bound; }
			else {
				if (C.query(bound, pivotIdx - 1) == mC) { l = bound + 1; }
				else { r = bound; }
			}
		}
		else {
			if (direction) { r = bound - 1; }
			else { l = bound + 1; }
		}
	}

	return l;
}

//Finding directly the correct range won't work, we could be at a small number in D, and there is a bigger one which satisfies the condition not yet seen
//So there isn't an increasing property here
//However, finding the range where maxC >= maxD - K satisfies the increasing property
int findGd(vector<int> &c, vector<int>& d, SegTree& C, SegTree& D, int K, int pivotIdx, bool direction) {	//1 right, 0 left
	int l = direction ? pivotIdx : 0, r = direction ? c.size() - 1 : pivotIdx;
	while (l < r) {
		int bound = (l + r) / 2;
		if (direction) { bound = (l + r + 1) / 2; }

		int mC, mD;
		if (direction) {
			mC = C.query(pivotIdx, bound);
			mD = D.query(pivotIdx, bound);
		}
		else {
			mC = C.query(bound, pivotIdx);
			mD = D.query(bound, pivotIdx);
		}
		
		if (mC == c[pivotIdx] && mC >= mD - K) {
			if (direction) { l = bound; }
			else { 
				if (C.query(bound, pivotIdx - 1) == mC) { l = bound + 1; }	//Consider the number only when he is the leftmost max
				else { r = bound; }
			}
		}
		else {
			if (direction) { r = bound - 1; }
			else { l = bound + 1; }
		}
	}

	return l;
}

int main() {
	int T; cin >> T;
	for (int qq = 1; qq <= T; qq++) {
		int N, K; cin >> N >> K;
		SegTree D(N), C(N);
		vector<int> d(N), c(N);

		for (int i = 0; i < N; i++) {
			cin >> c[i]; C.update(i, c[i]);
		}
		for (int i = 0; i < N; i++) {
			cin >> d[i]; D.update(i, d[i]);
		}

		ll ans = 0;
		for (int i = 0; i < N; i++) {
			int pivot = c[i];
			int l = findGd(c, d, C, D, K, i, 0);
			int r = findGd(c, d, C, D, K, i, 1);

			if (!(l == r && r == i && c[i] < d[i] - K)) {
				ans += (ll)(r - i + 1)*(ll)(i - l + 1);

				l = findTooGd(c, d, C, D, K, i, 0);
				r = findTooGd(c, d, C, D, K, i, 1);
				if (!(l == r && r == i && c[i] <= d[i] + K)) {
					ans -= (ll)(r - i + 1)*(ll)(i - l + 1);
				}
			}
		}

		cout << "Case #" << qq << ": " << ans << endl;
	}
}