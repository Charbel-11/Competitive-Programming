#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, k; cin >> n >> k;
		vector<int> h(n); for (auto& x : h) { cin >> x; }
		vector<int> start(n), end(n);
		start[0] = h[0]; end[0] = h[0] + k;
		start[n - 1] = h[n - 1]; end[n - 1] = h[n - 1] + k;

		bool OK = true;
		for (int i = 1; i < n - 1; i++) {
			int curMin = h[i], curMax = h[i] + k + k - 1;
			if (curMin >= end[i - 1] || curMax <= start[i - 1]) { OK = false; break; }
			curMin = max(curMin, start[i - 1] + 1 - k);
			curMax = min(curMax, end[i - 1] - 1 + k);
			start[i] = curMin; end[i] = curMax;
		}

		if (start[n - 1] >= end[n - 2] || end[n - 1] <= start[n - 2]) { OK = false; }

		cout << (OK ? "YES" : "NO") << '\n';
	}
}