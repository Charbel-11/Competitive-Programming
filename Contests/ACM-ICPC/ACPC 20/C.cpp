#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 132120577;

//ll sum2[200005];

// a*x - b*y = return value = GCD(a,b). x,y >= 0
ll egcd(ll a, ll b, ll& x, ll& y) { // MINUS B*Y
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}

	ll d = egcd(b, a % b, y, x);
	y = a - x * (a / b) - y;
	x = b - x;
	return d;
}
// modular inverse; works for any mod p (coprime with a)
ll inverse(ll a, ll p = mod) {
	ll x, y;
	egcd(a % p + p, p, x, y);
	return x % p;
}

//1^2+2^2+...+n^2
ll sumSquares(ll n) {
	if (n <= 0) { return 0; }
	ll ans = (n * (n + 1)) % mod;
	ans *= (2 * n + 1); ans %= mod;
	ans *= inverse(6); ans %= mod;
	return ans;
}

void countingSort(vector<int>& p, vector<int>& c) {
	int n = p.size();
	vector<int> cnt(n, 0);
	for (auto& x : c) { cnt[x]++; }

	vector<int> newP(n);
	vector<int> pos(n); pos[0] = 0;
	for (int i = 1; i < n; i++) { pos[i] = pos[i - 1] + cnt[i - 1]; }
	for (auto x : p) {
		int i = c[x];
		newP[pos[i]] = x; pos[i]++;
	}
	p = newP;
}

//Builds the suffix array (lexicographical ordering of the suffixes defined by their start idx) of s in O(nlogn)
//sufA[i] gives the start index in s of the ith suffix
void suffArray(string s, vector<int>& sufA, vector<int>& lcp) {
	s.push_back('#');
	int n = s.size();
	vector<int> p(n), c(n);

	vector<pair<char, int>> a(n);
	for (int i = 0; i < n; i++) { a[i] = { s[i], i }; }
	sort(a.begin(), a.end());

	for (int i = 0; i < n; i++) { p[i] = a[i].second; }
	c[p[0]] = 0;
	for (int i = 1; i < n; i++) {
		if (a[i].first == a[i - 1].first) { c[p[i]] = c[p[i - 1]]; }
		else { c[p[i]] = c[p[i - 1]] + 1; }
	}

	int k = 0;
	while (c[p[n - 1]] != n - 1) {
		for (int i = 0; i < n; i++) { p[i] = (p[i] - (1 << k) + n) % n; }
		//p was shifted back but no need to change c
		//p is already sorted by the second half so radix sort only needs one additional counting sort
		countingSort(p, c);

		vector<int> newC(n); newC[p[0]] = 0;
		for (int i = 1; i < n; i++) {
			pair<int, int> prev = { c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n] };
			pair<int, int> now = { c[p[i]], c[(p[i] + (1 << k)) % n] };
			if (prev == now) { newC[p[i]] = newC[p[i - 1]]; }
			else { newC[p[i]] = newC[p[i - 1]] + 1; }
		}

		c = newC; k++;
	}
	sufA = p;

	//Finds the Longest Common Prefix of all contiguous suffixes in the suffix array in O(n)
	//lcp[pi] = lcp(s[p[i]..], s[p[i-1]..])
	lcp.clear(); lcp.resize(n); k = 0;
	for (int i = 0; i < n - 1; i++) {
		int pi = c[i];	//pos of suffix i in the suffix array
		int j = p[pi - 1];

		while (s[i + k] == s[j + k]) { k++; }
		lcp[pi] = k; k = max(k - 1, 0);
	}
	//LCP of any two suffixes i, j becomes min(lcp[pos[i]]...lcp[pos[j]]) = min(lcp[c[i]]...lcp[c[j]])

//	for (int i = 0; i < n; i++) { cout << lcp[i] << " " << sufA[i] << " " << s.substr(sufA[i], n - sufA[i]) << endl; }
}

struct StValMin {
	int v = 0, idx = 0; StValMin() {}
	StValMin(const int _v, const int _idx) : v(_v), idx(_idx) {}
	StValMin(const StValMin& v1, const StValMin& v2) {
		if (v1 <= v2) { v = v1; idx = v1.idx; }
		else { v = v2; idx = v2.idx; }
	}
	operator int() const { return v; }	//Casts StVal to int
};

struct StValC {
	int ones = 0, twos = 0; StValC() {}
	StValC(const int _v, const int _idx) {
		if (_v == 1) { ones = 1; twos = 0; }
		else if (_v == 2) { twos = 1; ones = 0; }
		else { ones = twos = 0; }
	}
	StValC(const StValC& v1, const StValC& v2) {
		ones = v1.ones + v2.ones;
		twos = v1.twos + v2.twos;
	}
};

vector<int> base;

template <typename T>
struct SegTree {
	int n;
	vector<int> leaves;
	vector<T> st;	//st[1] root; To go to a child, *2 (l) or *2+1 (r);	To go to a parent: /2

	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
	}

	//lo, hi indices of the actual array; si is the index of the segment tree array
	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = T(base[lo], lo);			//Set the actual array here
			leaves[lo] = si;
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid); init(rC, mid + 1, hi);
		st[si] = T(st[lC], st[rC]);
	}

	//l and r inclusive, 0-indexed
	T query(const int l, const int r) { return (l <= r && l < n&& r >= 0) ? query(l, r, 1, 0, n - 1) : T(); }
	T query(const int l, const int r, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return T(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}
};


ll ans = 0;
//O(nlogn)
//Initial call: l = 1, r = lcp.size()-1 (remember that l,r are indices in the lcp/suf array; NOT the string)
ll findKthSubstr(int l, int r, int rem, SegTree<StValC>& stC, SegTree<StValMin>& stM) {
	if (l >= r) { return 0; }
	StValC occ = stC.query(l, r);
	if (!occ.ones || !occ.twos) { return 0; }

	StValMin mi = stM.query(l + 1, r);
	int idx = mi.idx;
	ll height = mi.v - rem; rem = mi.v;

	ll contribution = findKthSubstr(l, idx - 1, rem, stC, stM) + findKthSubstr(idx, r, rem, stC, stM);
	ll curAns = sumSquares(contribution + height - 1) - sumSquares(contribution - 1);
	ans += curAns;
	ans %= mod; ans += mod; ans %= mod;

	return contribution + height;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	freopen("completions.in", "r", stdin);

	int t; cin >> t;
	while (t--) {
		ans = 0;
		int n1, n2; cin >> n1 >> n2;
		string s1, s2; cin >> s1 >> s2;
		string s = s1 + "_" + s2;

		vector<int> sufA, lcp;
		suffArray(s, sufA, lcp);

		int n = lcp.size(); n--;
		base.clear(); base.resize(n); base[0] = 0;
		for (int i = 1; i < n; i++) {
			if (sufA[i] < s1.size()) { base[i] = 1; }
			else if (sufA[i] > s1.size()) { base[i] = 2; }
		}
		SegTree<StValC> segTreeC(n);

		base = lcp;
		SegTree<StValMin> segTreeM(n);

		findKthSubstr(1, n - 1, 0, segTreeC, segTreeM);
		cout << ans << '\n';
	}
}