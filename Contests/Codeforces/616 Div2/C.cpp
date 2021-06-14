#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
int n, m, k;
vector<int> nums;

int minInRange(int l, int r) {
	int rem = m - k;
	int ans = INT_MAX;
	for (int i = l; i < l + rem; i++) {
		ans = min(ans, max(nums[i], nums[r-(l+rem-i) + 1]));
	}
	return ans;
}

int main() {
	int t; cin >> t;

	while (t--) {
		cin >> n >> m >> k;	//m-1 in front of me
		nums.clear(); nums.resize(n);
		for (auto &x : nums) { cin >> x; }

		k = min(k, m - 1);
		int best = 0;
		for (int leftTaken = 0; leftTaken <= k; leftTaken++) {
			best = max(best, minInRange(leftTaken, n - 1 - (k - leftTaken)));
		}

		cout << best << endl;
	}
}