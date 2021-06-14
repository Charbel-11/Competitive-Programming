#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int q; cin >> q;

	while (q--) {
		int n; cin >> n;
		vector<int> p(n); for (auto &x : p) { cin >> x; x--; }
		vector<int> cycleLen(n, 0);

		for (int i = 0; i < n; i++) {
			if (cycleLen[i] != 0) { continue; }

			int length = 1; int idx = i;
			while (p[idx] != i) {
				idx = p[idx]; length++;
			}
			idx = i; cycleLen[idx] = length;
			while (p[idx] != i) {
				cycleLen[p[idx]] = length;
				idx = p[idx];
			}
		}

		for (auto &x : cycleLen) { cout << x << " "; } cout << endl;
	}
}