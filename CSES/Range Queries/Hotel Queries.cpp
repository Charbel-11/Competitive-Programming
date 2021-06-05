#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

vector<int> hotel;

struct StVal {
	int v = 0; StVal() {}
	StVal(const int _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = max(v1, v2); }
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
			st[si] = StVal(hotel[lo]);			//Set the actual array here
			leaves[lo] = si;
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid); init(rC, mid + 1, hi);
		st[si] = StVal(st[lC], st[rC]);
	}

	//l and r inclusive, 0-indexed
	StVal query(const int l, const int r, const int k) { return (l <= r && l < n && r >= 0) ? query(l, r, k, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int k, const int si, const int lo, const int hi) {
		if (l > hi || r < lo) { return -1; }
		if (st[si] < k) { return -1; }
		if (lo == hi) { return lo; }
			
		const int mid = (lo + hi) >> 1;
		auto try1 = query(l, r, k, si << 1, lo, mid);
		if (try1 != -1) { return try1; }
		return query(l, r, k, si << 1 | 1, mid + 1, hi);
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

	int n, m; cin >> n >> m;
	hotel.resize(n); for (auto &x : hotel) { cin >> x; }
	vector<int> group(m); for (auto &x : group) { cin >> x; }


	SegTree st(n);
	for (int i = 0; i < m; i++) {
		int idx = st.query(0, n - 1, group[i]);
		if (idx!=-1){
			hotel[idx] -= group[i];
			st.update(idx, hotel[idx]);
		}
		cout << idx + 1 << ' ';
	}
	cout << '\n';
}