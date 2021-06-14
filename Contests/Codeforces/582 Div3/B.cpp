#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int t; cin >> t;

	for (int z = 0; z < t; z++) {
		int n; cin >> n;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }

		int curMin = INT_MAX; int res = 0;
		for (int i = n - 1; i >= 0; i--) {
			if (nums[i] > curMin) { res++; }
			curMin = min(curMin, nums[i]);
		}

		cout << res << endl;
	}
}