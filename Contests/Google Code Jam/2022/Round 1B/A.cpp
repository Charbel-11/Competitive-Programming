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
	for (int qq = 1; qq <= t; qq++) {
		int n; cin >> n;
		vector<int> D(n); for (auto& x : D) { cin >> x; }

		int l = 0, r = n - 1, curMax = 0, ans = 0;
		while (l <= r) {
			if (D[l] <= D[r]) {
				if (D[l] >= curMax) { ans++; }
				curMax = max(curMax, D[l]);
				l++;
			}
			else {
				if (D[r] >= curMax) { ans++; }
				curMax = max(curMax, D[r]);
				r--;
			}
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
