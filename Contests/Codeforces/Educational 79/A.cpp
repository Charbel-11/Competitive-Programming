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
		cin >> nums[0] >> nums[1] >> nums[2];

		sort(nums.begin(), nums.end());

		if (nums.back() - 1 > nums[0] + nums[1]) { cout << "No" << endl; }
		else { cout << "Yes" << endl; }
	}
}