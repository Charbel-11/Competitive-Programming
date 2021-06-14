#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<int> strength;

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

struct StVal {
	int GCD = 1, gcdCount = 0; StVal() {}
	StVal(const int _v) : GCD(_v), gcdCount(1) {}
	StVal(const StVal &v1, const StVal &v2) { 
		GCD = gcd(v1.GCD, v2.GCD);
		gcdCount = 0;
		if (GCD == v1.GCD) { gcdCount += v1.gcdCount; }
		if (GCD == v2.GCD) { gcdCount += v2.gcdCount; }
	}
	operator int() const { return gcdCount; }
};

struct SegTree {
	int n;
	vector<int> leaves;
	vector<StVal> st;

	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
	}

	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal(strength[lo]);			//Set the actual array here
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

	int n; cin >> n;
	strength.resize(n);
	for (auto &x : strength) { cin >> x; }

	SegTree sT(n);

	int t; cin >> t;
	while (t--) {
		int l, r; cin >> l >> r; l--; r--;
		cout << (r - l + 1) - sT.query(l, r) << '\n';
	}
}