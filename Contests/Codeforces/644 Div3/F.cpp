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

int n, m, spareIdx;
string cur;
vector<string> s;

bool check(int i) {
	if (i >= n) { return true; }

	int diff = 0;
	for (int k = 0; k < m; k++) {
		if (k == spareIdx) { continue; }
		if (s[i][k] != cur[k]) { diff++; }
	}

	if (diff >= 2) { return false; }
	if (diff == 0) { return check(i + 1); }
	if (spareIdx != -1) { cur[spareIdx] = s[i][spareIdx]; spareIdx = -1; }
	return check(i + 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		cin >> n >> m;
		s.clear();
		for (int i = 0; i < n; i++) {
			string ss; cin >> ss;
			s.push_back(ss);
		}

		bool found = false;
		for (int i = -1; i < m; i++) {
			spareIdx = i; cur = s[0];
			bool b = check(1);
			if (b) { cout << cur << endl; found = true; break; }
		}
		if (!found) { cout << -1 << endl; }
	}
}