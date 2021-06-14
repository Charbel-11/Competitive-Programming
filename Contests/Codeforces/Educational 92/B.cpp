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

	while (t--) {
		int n, k, z; cin >> n >> k >> z;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }

		vector<int> pref(n, 0); pref[0] = nums[0];
		int ans = 0;
		multiset<int> ms;
		for (int i = 1; i <= k; i++) {
			ms.insert(nums[i] + nums[i-1]);
			pref[i] = pref[i-1] + nums[i];
		}
		ans = pref[k];

		for (int i = 1; i <= z; i++) {
			int idx = k - i * 2, cur = 0;
			if (idx < 0) { break; }
			cur = pref[idx];
			ms.erase(ms.find(nums[idx + 2] + nums[idx + 1]));
			if (!ms.empty()) { cur += i * (*ms.rbegin()); }
			ms.erase(ms.find(nums[idx] + nums[idx + 1]));

			ans = max(ans, cur);
		}

		cout << ans << '\n';
	}
}