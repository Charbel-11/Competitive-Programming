#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	vector<vector<int>> divisors((int)2e5 + 2);
	for (int i = 1; i < (int)2e5 + 2; i++)
		for (int j = i; j < (int)2e5 + 2; j += i)
			divisors[j].push_back(i);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> p(n), c(n);
		for (auto &x : p) { cin >> x; x--; }
		for (auto &x : c) { cin >> x; }

		int ans = n;
		for (int i = 0; i < n; i++) {
			if (p[i] == -1) { continue; }

			vector<int> curCycle; int j = i;
			while (true) {
				if (p[j] == -1) { break; }
				curCycle.push_back(c[j]);
				int next = p[j]; p[j] = -1;
				j = next;
			}

			for (int k : divisors[(int)curCycle.size()]) {
				for (int i = 0; i < k; i++) {
					bool OK = true;
					for (int j = i; j < (int)curCycle.size(); j += k) {
						if (curCycle[j] != curCycle[i]) { OK = false; break; }
					}
					if (OK) {
						ans = min(ans, k);
					}
				}
			}
		}

		cout << ans << endl;
	}
}