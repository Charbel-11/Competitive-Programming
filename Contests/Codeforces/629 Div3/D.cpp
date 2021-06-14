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
		vector<int> t(n);
		for (auto &x : t) { cin >> x; }
		int k = 1;
		vector<int> ans(n, -1); ans[0] = 1;
		for (int i = 1; i < n; i++) {
			if (t[i] == t[i - 1]) { ans[i] = ans[i - 1]; continue; }
			if (ans[i - 1] == 1) { ans[i] = 2; k = 2; }
			else { ans[i] = 1; }
		}
		if (t[n - 1] != t[0] && ans[n - 1] == ans[0]) {
			bool flip = false; int start = 0;
			for (int i = 1; i < n; i++) {
				if (t[i] == t[i - 1]) {
					if (ans[i] == 1) { ans[i] = 2; }
					else { ans[i] = 1; }
					flip = true; start = i; break;
				}
			}
			if (!flip) {
				ans[n - 1] = 3; k = 3;
			}
			else {
				for (int i = start + 1; i < n; i++) {
					if (t[i] == t[i - 1]) { ans[i] = ans[i - 1]; continue; }
					if (ans[i - 1] == 1) { ans[i] = 2; k = 2; }
					else { ans[i] = 1; }
				}
			}

		}

		cout << k << endl;
		for (auto &x : ans) { cout << x << " "; } cout << endl;
	}
}