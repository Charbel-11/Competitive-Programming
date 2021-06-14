#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<int> nums(4);
	for (int i = 0; i < 4; i++) {
		cin >> nums[i];
	}

	sort(nums.begin(), nums.end());

	cout << nums[3] - nums[0] << " " << nums[3] - nums[1] << " " << nums[3] - nums[2] << endl;

}