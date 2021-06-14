#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }

		sort(nums.begin(), nums.end());
		cout << unique(nums.begin(), nums.end()) - nums.begin() << endl;
	}
}