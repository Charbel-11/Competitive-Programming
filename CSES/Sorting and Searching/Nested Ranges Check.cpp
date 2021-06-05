#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<int> base;

struct StVal {
	int ma = -1, mi = 1e9 + 2; StVal() {}
	StVal(const int _v) : ma(_v), mi(_v) {}
	StVal(const StVal& v1, const StVal& v2) { ma = max(v1.ma, v2.ma); mi = min(v1.mi, v2.mi); }
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
	StVal query(const int l, const int r) { return (l <= r && l < n&& r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}
};

struct range {
	int l, r, id;
	range(int _l, int _r, int _id) :l(_l), r(_r), id(_id) {}

	bool operator<(range& rhs) {
		if (l == rhs.l) { return r > rhs.r; }
		return l < rhs.l;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n; base.resize(n);
	vector<range> ranges;
	for (int i = 0; i < n; i++) {
		int l, r; cin >> l >> r;
		ranges.push_back(range(l, r, i));
	}
	sort(ranges.begin(), ranges.end());
	for (int i = 0; i < n; i++) { base[i] = ranges[i].r; }
	
	SegTree st(n);
	vector<int> ans1(n, 0), ans2(n, 0);
	for (int i = 0; i < n; i++) {
		int minR = st.query(i +  1, n - 1).mi;
		int maxR = st.query(0, i - 1).ma;

		if (minR <= ranges[i].r) { ans1[ranges[i].id] = 1; }
		if (maxR >= ranges[i].r) { ans2[ranges[i].id] = 1; }
	}

	for (auto& x : ans1) { cout << x << ' '; } cout << '\n';
	for (auto& x : ans2) { cout << x << ' '; }cout << '\n';
}