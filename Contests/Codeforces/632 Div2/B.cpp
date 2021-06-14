#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> a(n), b(n);
		for (auto &x : a) { cin >> x; }
		for (auto &x : b) { cin >> x; }

		if (a[0] != b[0]) { cout << "NO" << endl; continue; }
		bool OK = true;
		int neg = 0, pos = 0;
		for (int i = 1; i < n; i++) {
			if (a[i - 1] < 0) { neg++; }
			else if (a[i - 1] > 0) { pos++; }
			if (a[i] < b[i] && !pos) { OK = false; break; }
			if (a[i] > b[i] && !neg) { OK = false; break; }
		}

		cout << (OK ? "YES" : "NO") << endl;
	}
}