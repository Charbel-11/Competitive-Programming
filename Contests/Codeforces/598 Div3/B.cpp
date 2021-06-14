#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

set<pair<int, int>> used;

void opNum(vector<int> &nums, int i, int &limit) {
	int curMin = nums[i];
	int curMinIndex = i;
	for (int a = i+1; a < nums.size(); a++) {
		if (curMin > nums[a]) {
			curMin = nums[a];
			curMinIndex = a;
		}
	}
	int k = curMinIndex, op = 0;
	while (k > 0 && k > i && limit > 0 && used.count({ k, k - 1 }) == 0) {
		swap(nums[k], nums[k - 1]);
		used.insert({ k, k - 1 });
		k--; limit--;
	}
}

int main() {
	int q; cin >> q;

	while (q--) {
		used.clear();
		int n; cin >> n;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }

		int limit = n - 1, i = 0;
		while (limit && i < n) {
			opNum(nums, i, limit);
			i++;
		}

		for (auto &x : nums) { cout << x << " "; } cout << endl;
	}
}