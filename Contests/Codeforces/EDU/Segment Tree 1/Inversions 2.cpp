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

	//Change a leaf and update its ancestors' values
	void update(const int i, int c) {
		int si = leaves[i];
		st[si] = StVal(c);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
	}

	int kth(const int k) { return kth(k, 1, 0, n - 1); }
	int kth(const int k, const int si, const int lo, const int hi) {
		if (lo == hi) { return lo; }

		const int mid = (lo + hi) >> 1;
		if (st[si << 1].v >= k) { return kth(k, si << 1, lo, mid); }
		return kth(k - st[si << 1].v, si << 1 | 1, mid + 1, hi);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	base.resize(n + 1, 1); base[0] = 0;
	vector<int> nums(n); for (auto &x : nums) { cin >> x; }

	SegTree st(n + 1);
	
	vector<int> ans(n);
	for (int i = n - 1; i >= 0; i--) {
		ans[i] = st.kth(n - nums[i]);
		n--; st.update(ans[i], 0);
	}

	for (auto &x : ans) { cout << x << ' '; }
	cout << '\n';
}