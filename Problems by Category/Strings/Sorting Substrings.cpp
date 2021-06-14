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

string s;
vector<int> posInSufA, sufA, lcp;

struct StVal {
	int v = 0; StVal() {}
	StVal(const int _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = min(v1, v2); }
	operator int() const { return v; }	//Casts StVal to int
};

struct SegTree {
	int n;
	vector<int> leaves;
	vector<StVal> st;

	SegTree() {}
	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
	}

	//lo, hi indices of the actual array; si is the index of the segment tree array
	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal(lcp[lo]);			//Set the actual array here
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

SegTree st;
void countingSort(vector<int> &p, vector<int> &c) {
	int n = p.size();
	vector<int> cnt(n, 0);
	for (auto &x : c) { cnt[x]++; }

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
void suffArray(string s) {
	s.push_back(' ');
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
	while (c[p[n-1]] != n-1) {
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
	sufA = p; posInSufA = c;

	//Finds the Longest Common Prefix of all contiguous suffixes in the suffix array in O(n)
	//lcp[pi] = lcp(s[p[i]..], s[p[i-1]..]
	lcp.clear(); lcp.resize(n); k = 0;
	for (int i = 0; i < n - 1; i++) {
		int pi = c[i];	//pos of suffix i in the suffix array
		int j = p[pi - 1];

		while (s[i + k] == s[j + k]) { k++; }
		lcp[pi] = k; k = max(k - 1, 0);
	}
	//LCP of any two suffixes i, j becomes min(lcp[pos[i]]...lcp[pos[j]]) = min(lcp[c[i]]...lcp[c[j]])
}

bool comp(pair<int, int> &p1, pair<int, int> &p2) {
	if (p1.first == p2.first) { return p1.second < p2.second; }

	int l1 = posInSufA[p1.first], l2 = posInSufA[p2.first];
	int len1 = p1.second - p1.first + 1, len2 = p2.second - p2.first + 1;
	if (l1 > l2) { swap(l1, l2); }
	int common = st.query(l1 + 1, l2);
	
	if (common >= min(len1, len2)) { 
		if (len1 == len2) { return p1 < p2; }
		return len1 < len2;
	}
	return s[p1.first + common] < s[p2.first + common];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> s; suffArray(s); st = SegTree(s.size() + 1);
//	for (int i = 0; i <= s.size(); i++) { cout << lcp[i] << " " << sufA[i] << " " << s.substr(sufA[i], s.size() + 1 - sufA[i]) << endl; }
	int m; cin >> m;
	vector<pair<int, int>> p(m);
	for (auto &x : p) { cin >> x.first >> x.second; x.first--; x.second--; }
	sort(p.begin(), p.end(), comp);

	for (auto &x : p) { cout << x.first + 1 << ' ' << x.second + 1 << '\n'; }
}