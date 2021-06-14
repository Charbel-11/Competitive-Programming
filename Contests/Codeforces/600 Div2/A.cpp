#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> a(n); vector<int> b(n);
		for (auto &x : a) { cin >> x; }
		for (auto &y : b) { cin >> y; }

		bool OK = true;
		for (int i = 0; i < n; i++) {
			b[i] -= a[i];
			if (b[i] < 0) {
				cout << "NO" << endl;
				OK = false;  break;
			}
		}

		if (!OK) { continue; }

		int i = 0;
		while (i < n && b[i] == 0) {
			i++;
		}
		if (i < n) {
			int val = b[i];
			while (i < n && b[i] != 0) {
				if (b[i] != val) { OK = false; }
				i++;
			}
			while (i < n) {
				if (b[i] != 0) { OK = false; }
				i++;
			}
		}
		if (OK)		cout << "YES" << endl;
		else { cout << "NO" << endl; }
	}
}