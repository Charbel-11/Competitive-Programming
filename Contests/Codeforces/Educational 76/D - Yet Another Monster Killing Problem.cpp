#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n; int maxMonst = 0;
		vector<int> monsters(n);
		for (auto &x : monsters) { cin >> x; maxMonst = max(x, maxMonst); }

		int m; cin >> m;
		vector<pair<int, int>> heroes(m);
		for (int i = 0; i < m; i++) {
			int p, s; cin >> p >> s;
			heroes[i] = { p, s };
		}

		sort(heroes.begin(), heroes.end());
		if (heroes.back().first < maxMonst) { cout << -1 << endl; continue; }

		vector<int> maxEnd(m);
		maxEnd[m - 1] = heroes[m - 1].second;
		for (int i = m - 2; i >= 0; i--) {
			maxEnd[i] = max(maxEnd[i + 1], heroes[i].second);
		}

		vector<int> h(m);
		for (int i = 0; i < m; i++) {
			h[i] = heroes[i].first;
		}

		int days = 1, streak = 1, curMax = monsters[0];
		int idx = lower_bound(h.begin(), h.end(), monsters[0]) - h.begin();
		for (int i = 1; i < n; i++) {
			streak++;

			curMax = max(curMax, monsters[i]);
			idx = lower_bound(h.begin(), h.end(), curMax) - h.begin();
			if (streak > maxEnd[idx]) {
				days++;
				streak = 1;
				curMax = monsters[i];
				idx = lower_bound(h.begin(), h.end(), curMax) - h.begin();
			}
		}

		cout << days << endl;
	}
}