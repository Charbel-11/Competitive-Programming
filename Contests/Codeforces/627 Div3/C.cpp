#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool check(int d, string& s) {
	int range = d;
	for (int i = 1; i <= s.size(); i++) {
		if (range < i) { return false; }
		if (s[i-1] == 'R') {
			range = max(range, i + d);
		}
	}
	return range > s.size();
}

int main() {
	int t; cin >> t;

	while (t--) {
		string s; cin >> s;

		int l = 1, r = s.size()+1;
		while (l < r) {
			int mid = (l + r) / 2;
			bool b = check(mid, s);
			if (b) {
				r = mid;
			}
			else {
				l = mid + 1;
			}
		}

		cout << l << endl;
	}
}