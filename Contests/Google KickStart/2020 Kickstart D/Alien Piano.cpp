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
		int n; cin >> n;
		vector<int> nums;
		for (int i = 0; i < n; i++) {
			int cur; cin >> cur;
			if (!nums.empty() && cur == nums.back()) { continue; }
			nums.push_back(cur);
		}
		n = (int)nums.size();

		vector<int> dec(n, 0), inc(n, 0);
		for (int i = n - 2; i >= 0; i--) {
			if (nums[i] > nums[i + 1]) { dec[i] = dec[i + 1] + 1; }
			else if (nums[i] < nums[i + 1]) { inc[i] = inc[i + 1] + 1; }
		}

		int ans = 0, state = (inc[0] ? 0 : 3);
		for (int i = 0; i < n; i++) {
			bool reset = false;
			if (inc[i] && state == 3) { ans++; state = 0; reset = 1; }
			if (dec[i] && state == 0) { ans++; state = 3; reset = 1; }

			if (inc[i] == 1) { state = 3; }
			else if (dec[i] == 1) { state = 0; }
			else if (!reset && inc[i]) { state++; }
			else if (!reset && dec[i]) { state--; }
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}