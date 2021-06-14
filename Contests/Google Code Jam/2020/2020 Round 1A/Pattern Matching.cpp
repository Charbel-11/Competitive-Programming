#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		int n; cin >> n;
		vector<string> vs;
		for (int i = 0; i < n; i++) {
			string s; cin >> s;
			vs.push_back(s);
		}

		vector<pair<int, int>> starIdx(n);
		for (int i = 0; i < n; i++) { starIdx[i] = { -1,-1 }; }

		bool OK = true;
		string start = "", end = ""; int cnt = 0;
		for (auto &s : vs) {
			int j = 0;
			for (int i = 0; i < s.size(); i++) {
				if (s[i] == '*') { starIdx[cnt++].first = i; break; }

				if (j == start.size()) { start.push_back(s[i]); }
				else if (start[j] != s[i]) { OK = false; break; }
				j++;
			}
		}

		cnt = 0;
		for (auto &s : vs) {
			int j = 0;
			for (int i = s.size() - 1; i >= 0; i--) {
				if (s[i] == '*') { starIdx[cnt++].second = i; break; }

				if (j == end.size()) { end.push_back(s[i]); }
				else if (end[j] != s[i]) { OK = false; break; }
				j++;
			}
		}

		reverse(end.begin(), end.end());

		string mid = "";
		for (int i = 0; i < n; i++) {
			if (starIdx[i].first == -1 || starIdx[i].second == -1) { continue; }
			for (int j = starIdx[i].first + 1; j < starIdx[i].second; j++) {
				if (vs[i][j] != '*') { mid.push_back(vs[i][j]); }
			}
		}

		cout << "Case #" << q << ": ";
		if (!OK) { cout << "*" << endl; }
		else { cout << start << mid << end << endl; }
	}
}