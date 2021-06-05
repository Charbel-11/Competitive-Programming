#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll; //In case ll is used, be sure to change everything (StVal/update function/vectors...)

string s;

struct DynamicHash {
	static const ll m1 = 8675309, m2 = 1e9 + 7;
	static const ll s1 = 257, s2 = 619;
	static const int SZ = 1e6;
	static ll s1Pow[SZ], s2Pow[SZ];
	static bool precomp;
	ll v1 = 0, v2 = 0; int l = 0;

	DynamicHash() {}
	DynamicHash(const DynamicHash& oh) : v1(oh.v1), v2(oh.v2), l(oh.l) {}
	DynamicHash(const string& s) {
		v1 = v2 = 0; l = 0;
		for (auto& c : s) { add(c); }
	}

	static void precompute() {
		if (precomp) { return; }
		precomp = true;
		s1Pow[0] = s2Pow[0] = 1;
		for (int i = 1; i < SZ; i++)
			s1Pow[i] = (s1Pow[i - 1] * s1) % m1;
		for (int i = 1; i < SZ; i++)
			s2Pow[i] = (s2Pow[i - 1] * s2) % m2;
	}

	void add(char c) {
		v1 = (v1 * s1 + c) % m1;
		v2 = (v2 * s2 + c) % m2;
		l++;
	}

	bool equal(const DynamicHash& oh) {
		if (v1 != oh.v1) { return false; }
		return v2 == oh.v2;
	}

	void append(const DynamicHash& oh) {
		precompute();
		v1 = (v1 * s1Pow[oh.l] + oh.v1) % m1;
		v2 = (v2 * s2Pow[oh.l] + oh.v2) % m2;
		l += oh.l;
	}
};

bool DynamicHash::precomp = false;
ll DynamicHash::s1Pow[SZ];
ll DynamicHash::s2Pow[SZ];


struct StVal {
	DynamicHash hash1, hash2;
	char v; StVal() {}
	StVal(const char _v) : v(_v) { hash1 = hash2 = DynamicHash(to_string(_v)); }
	StVal(const StVal& v1, const StVal& v2) { 
		hash1 = DynamicHash(v1.hash1); hash1.append(v2.hash1);
		hash2 = DynamicHash(v2.hash2); hash2.append(v1.hash2);
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
			st[si] = StVal(s[lo]);			//Set the actual array here
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
	void update(const int i, char c) {
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
	cin >> s; SegTree st(n);
	while (m--) {
		int t; cin >> t;
		if (t == 1) {
			int k; cin >> k; k--;
			char x; cin >> x;
			st.update(k, x);
		}
		else {
			int a, b; cin >> a >> b; a--; b--;
			StVal cur = st.query(a, b);
			if (cur.hash1.equal(cur.hash2)) { cout << "YES" << '\n'; }
			else { cout << "NO" << '\n'; }
		}
	}
}