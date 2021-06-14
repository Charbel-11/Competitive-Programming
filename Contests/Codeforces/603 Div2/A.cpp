#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		vector<int> nums(3);
		for (auto &x : nums) { cin >> x; }
		sort(nums.begin(), nums.end());
		int res = 0;

		if (nums[0] <= nums[2] - nums[1]) {
			cout << nums[0] + nums[1] << endl;
			continue;
		}

		res += nums[2] - nums[1];
		nums[0] -= (nums[2] - nums[1]);
		nums[1] -= (nums[0]+1)/2;
		res += nums[0] + nums[1];

		cout << res << endl;
		
	}
}