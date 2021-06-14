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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n, c; cin >> n >> c;
		cout << "Case #" << qq << ": ";
		
		if (c < n - 1) { cout << "IMPOSSIBLE" << '\n'; continue; }
		c -= (n - 1);

		vector<int> ans(n);
		int l = 0, r = n - 1, cur = 1;
		bool dir = 0;
		while (l < r) {
			int curCost = r - l;
			if (c < curCost) {
				if (!dir) { ans[l++] = cur; }
				else { ans[r--] = cur; }
			}
			else {
				c -= curCost;
				if (!dir) { ans[r--] = cur; }
				else { ans[l++] = cur; }
				dir = !dir;
			}
			cur++;
		}
		ans[l] = cur;
		if (c) { cout << "IMPOSSIBLE" << '\n'; continue; }

		for (auto& x : ans) { cout << x << ' '; }
		cout << '\n';
	}
}