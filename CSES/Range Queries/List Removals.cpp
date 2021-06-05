#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<int> base;

struct StVal {
	int v = 0; StVal() {}
	StVal(const int _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = v1 + v2; }
	operator int() const { return v; }	//Casts StVal to int
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
	StVal query(const int k) { return query(k, 1, 0, n - 1); }
	StVal query(const int k, const int si, const int lo, const int hi) {
		if (lo == hi) { return lo; }
		
		const int mid = (lo + hi) >> 1;
		int lC = si << 1, rC = si << 1 | 1;
		if (st[lC] >= k) { return query(k, lC, lo, mid); }
		return query(k - st[lC], rC, mid + 1, hi);
	}

	//Change a leaf and update its ancestors' values
	void update(const int i, int c) {
		int si = leaves[i];
		st[si] = StVal(c);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> val(n); for (auto &x : val) { cin >> x; }
	base.resize(n, 1); SegTree st(n);

	for (int i = 0; i < n; i++) {
		int p; cin >> p;
		int idx = st.query(p);
		st.update(idx, 0);
		cout << val[idx] << ' ';
	}
	cout << '\n';
}