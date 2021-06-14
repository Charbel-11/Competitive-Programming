#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
vector<int> v;

struct StVal {
	int mi = 0, idx = 0; StVal() {}
	StVal(const int _v, const int _idx) : mi(_v), idx(_idx) { }
	StVal(const StVal& v1, const StVal& v2) { 
		if (v1.mi < v2.mi) {
			mi = v1.mi; idx = v1.idx;
		}
		else if (v1.mi > v2.mi) {
			mi = v2.mi; idx = v2.idx;
		}
		else {
			mi = v1.mi; idx = max(v2.idx, v1.idx);
		}
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

	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal(v[lo], lo);			//Set the actual array here
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

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	if (p == 0) return 1;
	ll w = powe((x * x) % mod, p / 2);
	if (p & 1) w = (w * x) % mod;
	return w;
}
// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

const int SZ = (int)2e5 + 1;
ll fact[SZ];
void fillFact() {
	fact[0] = 1;
	for (int i = 1; i < SZ; i++) {
		fact[i] = fact[i - 1] * i;
		fact[i] %= mod;
	}
}

ll choose(ll n, ll k) {
	if (k > n) { return 0; }
	ll num = fact[n], denom = fact[k];
	denom *= fact[n - k]; denom %= mod;

	ll multInv = modinv(denom);
	num *= multInv; num %= mod;
	return num;
}

ll countWays(int l, int r, SegTree& st) {
	if (l >= r) { return 1; }
	int mIdx = st.query(l, r).idx;

	ll ans = countWays(l, mIdx - 1, st) * countWays(mIdx + 1, r, st); ans %= mod;
	ans *= choose(r - l, mIdx - l); ans %= mod;
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	fillFact();
	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; cin >> n;
		v.clear(); v.resize(n); for (auto& xx : v) { cin >> xx; }

		bool OK = v[0] == 1;
		for (int i = 1; i < n; i++) {
			if (v[i] == 0 || v[i] - v[i - 1] > 1) { OK = false; break; }
		}
		if (!OK) {
			cout << "Case #" << qq << ": " << 0 << '\n';
			continue;
		}

		SegTree st(n);

		cout << "Case #" << qq << ": " << countWays(0, n-1, st) << '\n';
	}
}
