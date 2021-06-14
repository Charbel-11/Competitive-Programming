#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll; //In case ll is used, be sure to change everything (StVal/update function/vectors...)

vector<int> base;

struct StVal {
	int v = 1, maxV = 0; ll vS = 0; StVal() {}
	StVal(const int _v) : v(_v), vS(_v), maxV(_v) {}
	StVal(const StVal& v1, const StVal& v2) { 
		v = v1.v & v2.v; 
		vS = v1.vS + v2.vS; 
		maxV = max(v1.maxV, v2.maxV);
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
	void query1(const int l, const int r) { query1(l, r, 1, 0, n - 1); }
	void query1(const int l, const int r, const int si, const int lo, const int hi) {
		if (lo == hi) { st[si].v = st[si].vS = st[si].maxV = (st[si].v | (st[si].v - 1)); return; }
		if (l <= lo && hi <= r && (st[si].v & 1)) return;

		const int mid = (lo + hi) >> 1;
		if (r <= mid) query1(l, r, si << 1, lo, mid);
		else if (mid < l) query1(l, r, si << 1 | 1, mid + 1, hi);
		else {
			query1(l, r, si << 1, lo, mid); 
			query1(l, r, si << 1 | 1, mid + 1, hi);
		}

		st[si] = StVal(st[si << 1], st[(si << 1) | 1]);
	}

	void query2(const int l, const int r) { query2(l, r, 1, 0, n - 1); }
	void query2(const int l, const int r, const int si, const int lo, const int hi) {
		if (lo == hi) { st[si].v = st[si].vS = st[si].maxV = (st[si].v ^ (st[si].v - 1)); return; }
		if (l <= lo && hi <= r && st[si].maxV == 1) return;

		const int mid = (lo + hi) >> 1;
		if (r <= mid) query2(l, r, si << 1, lo, mid);
		else if (mid < l) query2(l, r, si << 1 | 1, mid + 1, hi);
		else {
			query2(l, r, si << 1, lo, mid);
			query2(l, r, si << 1 | 1, mid + 1, hi);
		}

		st[si] = StVal(st[si << 1], st[(si << 1) | 1]);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	freopen("orxor.in", "r", stdin);

	int n, q; cin >> n >> q;
	base.resize(n); for (auto& x : base) { cin >> x; }

	SegTree segT(n);
	while (q--) {
		int t, l, r; cin >> t >> l >> r; l--; r--;

		if (t == 1) { segT.query1(l, r); }
		else { segT.query2(l, r); }

		cout << segT.st[1].vS << '\n';
	}
}