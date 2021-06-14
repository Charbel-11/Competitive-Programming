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
		vector<int> nums(n); for (auto& x : nums) { cin >> x; }

		int ans = 0;
		for (int i = 0; i < n - 1; i++) {
			int idx = i;
			for (int j = i + 1; j < n; j++) {
				if (nums[j] < nums[idx]) { idx = j; }
			}
			ans += idx - i + 1;
			reverse(nums.begin() + i, nums.begin() + idx + 1);
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}