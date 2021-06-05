#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll; //In case ll is used, be sure to change everything (StVal/update function/vectors...)

struct StVal {
	bool pref1, suf1;
	int prefLen, sufLen, maxLen, segLen;
	StVal() {}
	StVal(const bool _v) {
		if (_v) { pref1 = suf1 = 1; }
		else { pref1 = suf1 = 0; }
		prefLen = sufLen = maxLen = segLen = 1;
	}
	StVal(const StVal& v1, const StVal& v2) {
		segLen = v1.segLen + v2.segLen;
		pref1 = v1.pref1; suf1 = v2.suf1;
		maxLen = max(v1.maxLen, v2.maxLen);
		if (v1.suf1 == v2.pref1) { maxLen = max(maxLen, v1.sufLen + v2.prefLen); }

		if (v1.prefLen == v1.segLen && v1.pref1 == v2.pref1) { prefLen = v1.segLen + v2.prefLen; }
		else { prefLen = v1.prefLen; }
		if (v2.sufLen == v2.segLen && v2.suf1 == v1.suf1) { sufLen = v2.segLen + v1.sufLen; }
		else { sufLen = v2.sufLen; }
	}
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
			st[si] = StVal(0);			//Set the actual array here
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

	//Change a leaf and update its ancestors' values
	void update(const int i, bool c) {
		int si = leaves[i];
		st[si] = StVal(c);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	string s; cin >> s; int n = s.size();
	SegTree st(n);
	for (int i = 0; i < n; i++) { if (s[i] == '1') { st.update(i, 1); } }

	int m; cin >> m;
	while (m--) {
		int i; cin >> i; i--;
		if (s[i] == '0') {
			s[i] = '1';
			st.update(i, 1);
		}
		else{
			s[i] = '0';
			st.update(i, 0);
		}
		cout << st.query(0, n - 1).maxLen << ' ';
	}
	cout << '\n';
}