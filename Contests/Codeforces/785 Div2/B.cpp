#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

bool check(vector<vector<int>>& idx, int l, int r) {
	for (int i = 0; i < 26; i++) {
		if (idx[i].size() == 0) { continue; }

		int curIdx = lower_bound(idx[i].begin(), idx[i].end(), l) - idx[i].begin();
		if (curIdx == idx[i].size()) { return false; }

		curIdx = idx[i][curIdx];
		if (curIdx > r) { return false; }
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		string s; cin >> s;
		int n = s.size();

		set<char> C; for (auto& c : s) { C.insert(c); }
		if (C.size() == 1) { cout << "YES" << '\n'; continue; }

		bool OK = true;
		for (int i = 1; i < n; i++) {
			if (s[i] == s[i - 1]) {
				OK = false;
				break;
			}
		}

		if (!OK) { cout << "NO" << '\n'; continue; }

		vector<vector<int>> idx(26, vector<int>());
		for (int i = 0; i < n; i++) { idx[s[i] - 'a'].push_back(i); }

		for (int i = 0; i < 26; i++) {
			if (idx[i].size() < 2) { continue; }
			for (int j = 1; j < idx[i].size(); j++) {
				if (!check(idx, idx[i][j - 1], idx[i][j])) { OK = false; break; }
			}
		}

		if (!OK) { cout << "NO" << '\n'; }
		else { cout << "YES" << '\n'; }
	}
}