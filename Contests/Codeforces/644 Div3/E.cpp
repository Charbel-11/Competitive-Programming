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

void check(vector<string> &s, int i, int j) {
	if (j < 0 || i < 0 || i >= s.size() || j >= s.size()) { return; }
	if (s[i][j] == '2') { return; }
	if (s[i][j] != '0') { 
		s[i][j] = '2'; 
		check(s, i, j - 1);
		check(s, i - 1, j);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<string> s(n);
		for (auto &x : s) { cin >> x; }
		for (int i = 0; i < n; i++) {
			if (s[i][n - 1] == '1') { check(s, i, n - 1); }
		}

		for (int j = 0; j < n; j++) {
			if (s[n - 1][j] == '1') { check(s, n - 1, j); }
		}

		bool OK = true;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (s[i][j] == '1') { OK = false; }
			}
		}
		cout << (OK ? "YES" : "NO") << endl;
	}
}