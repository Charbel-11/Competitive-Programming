#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n;	cin >> n;

	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	sort(nums.begin(), nums.end());

	int res = 0;
	int curMax = 0;
	for (int i = 0; i < n; i++) {
		if (nums[i] - 1 > curMax) { curMax = nums[i] - 1; res++; continue; }
		if (nums[i] > curMax) { curMax = nums[i]; res++; continue; }
		if (nums[i] + 1 > curMax) { curMax = nums[i] + 1; res++; }
	}

	cout << res << endl;
}