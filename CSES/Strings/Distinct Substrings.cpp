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

//Counts the number of different substrings in s in O(n)
ll numOfDifSubstr(string& s, vector<int>& sufA, vector<int>& lcp) {
	ll res = 0; int n = s.size();
	for (int i = 1; i <= n; i++) {
		res += (n - sufA[i] - lcp[i]);
	}
	return res;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
	vector<int> sufA, lcp;
	suffArray(s, sufA, lcp);
	cout << numOfDifSubstr(s, sufA, lcp) << '\n';
}