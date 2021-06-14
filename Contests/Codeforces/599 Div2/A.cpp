#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int k; cin >> k;

	while (k--) {
		int n; cin >> n;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }
		sort(nums.begin(), nums.end());

		int res = 1;
		for (int i = n - 2; i >= 0; i--) {
			if (nums[i] > res) {
				res++;
			}
		}

		cout << res << endl;
	}
}