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

struct StVal {
	int v = 0, idx = 0; StVal() {}
	StVal(const int _v, const int _idx) : idx(_idx), v(_v) {}
	StVal(const StVal& v1, const StVal& v2) {
		if (v1 < v2) { v = v1; idx = v1.idx; }
		else { v = v2; idx = v2.idx; }
	}
	operator int() const { return v; }	//Casts StVal to int
};

struct SegTree {
	int n;
	vector<int> leaves;
	vector<StVal> st;

	SegTree(const vector<int>& lcp) {
		n = lcp.size();
		leaves.resize(n);
		init(1, 0, n - 1, lcp);
	}

	//lo, hi indices of the actual array; si is the index of the segment tree array
	void init(const int si, const int lo, const int hi, const vector<int>& lcp) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal(lcp[lo], lo);			//Set the actual array here
			leaves[lo] = si;
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid, lcp); init(rC, mid + 1, hi, lcp);
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
}

ll maxRefrain = 0;
int startIdx = 0, len = 0;

//Returns {startPos, len} of the kth substring
void findMaxRefrain(int l, int r, vector<int>& sufA, SegTree& st) {
	if (l >= r) { return; }

	StVal mi = st.query(l + 1, r);
	int idx = mi.idx;
	ll range = r - l + 1, height = mi.v;
	ll curR = range * height;
	if (curR > maxRefrain) { maxRefrain = curR; startIdx = sufA[l]; len = height; }

	findMaxRefrain(l, idx - 1, sufA, st);
	findMaxRefrain(idx, r, sufA, st);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	string s = ""; 
	for (int i = 0; i < n; i++) {
		int cur; cin >> cur; cur--;
		s.push_back('0' + cur);
	}

	vector<int> sufA, lcp; suffArray(s, sufA, lcp);
	SegTree st(lcp);
	maxRefrain = n; startIdx = 0; len = n;

	findMaxRefrain(1, lcp.size() - 1, sufA, st);

	cout << maxRefrain << '\n';
	cout << len << '\n';
	for (int i = startIdx; i < startIdx + len; i++) {
		cout << (s[i] - '0' + 1) << ' ';
	}
	cout << '\n';
}