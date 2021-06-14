#include <map>
#include <set>
#include <iostream>
#include <string>
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
void suffArray(string s, vector<int>& sufA) {
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
}

int n, k;
string ans, s;

bool findAns(int i, int l, int r, string& cur, vector<int>& sufA) {
	if (i == k && l <= r) { return false; }
	else if (l > r) { ans = cur; return true; }

	int curL = l, curR = r;
	if (s[sufA[r] + i] == '0') { curL = curR + 1; }
	while (curL < curR) {
		int mid = (curL + curR) / 2;
		int idx = sufA[mid];
		if (s[idx+i] == '1') { curR = mid; }
		else { curL = mid + 1; }
	}

	cur.push_back('0');
	bool c2 = findAns(i + 1, curL, r, cur, sufA);
	cur.pop_back();
	if (c2) { return true; }

	cur.push_back('1');
	bool c1 = findAns(i + 1, l, curL - 1, cur, sufA);
	cur.pop_back();
	return c1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		cin >> n >> k >> s;
		vector<int> sufA;
		suffArray(s, sufA);
		vector<int> sufA2;
		for (int i = 0; i < sufA.size(); i++) {
			if (sufA[i] + k - 1 >= n) { continue; }
			sufA2.push_back(sufA[i]);
		}

		string c = "";
		bool OK = findAns(0, 0, sufA2.size()-1, c , sufA2);
		if (OK) {
			cout << "YES\n";
			while (ans.size() < k) { ans.push_back('0'); }
			cout << ans << '\n';
		}
		else { cout << "NO\n"; }
	}
}