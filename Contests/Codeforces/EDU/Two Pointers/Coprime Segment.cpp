#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll; 
vector<ll> base;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

struct StVal {
	ll v = 0; StVal() {}
	StVal(const ll _v) : v(_v) {}
	StVal(const StVal& v1, const StVal& v2) { v = gcd(v1.v, v2.v); }
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
			st[si] = StVal(base[lo]);			//Set the actual array here
			leaves[lo] = si;
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid); init(rC, mid + 1, hi);
		st[si] = StVal(st[lC], st[rC]);
	}

	int query(const int l) { return query(l, 0, 1, 0, n - 1).first; }
	pair<int, ll> query(const int l, ll curGcd, const int si, const int lo, const int hi) {
		if (hi < l) { return { -1, 0 }; }
		if (lo >= l) {
			ll newGcd = gcd(curGcd, st[si].v);
			if (newGcd != 1) { return { -1, newGcd }; }
			else if (lo == hi && newGcd == 1) { return { lo, newGcd }; }
		}

		const int mid = (lo + hi) >> 1;
		auto leftV = query(l, curGcd, si << 1, lo, mid);
		if (leftV.first != -1) { return leftV; }

		return query(l, leftV.second, si << 1 | 1, mid + 1, hi);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	base.resize(n); for (auto& x : base) { cin >> x; }
	SegTree st(n);

	int ans = n + 1;
	for (int l = 0; l < n; l++) {
		int r = st.query(l);
		if (r != -1) { ans = min(ans, r - l + 1); }
	}

	if (ans == n + 1) { cout << -1 << '\n'; }
	else { cout << ans << '\n'; }
}