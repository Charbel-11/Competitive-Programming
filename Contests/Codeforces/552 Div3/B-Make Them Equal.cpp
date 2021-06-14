#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> distNums;
//Having a vector nums of n sorted ints, create a vector of distinct ints in order
void makeDistinct(vector<int> nums, int n) {
	distNums.clear();
	if (n == 0) { return; }

	int i = 0;
	while (i < n - 1) {
		if (nums[i] != nums[i + 1]) {
			distNums.push_back(nums[i]);
			i++;
			continue;
		}

		distNums.push_back(nums[i]);
		while (i < n - 1 && nums[i] == nums[i + 1]) {
			i++;
		}
		i++;
	}
	if (n == 1 || (n > 1 && nums[n - 2] != nums[n - 1])) { distNums.push_back(nums[n - 1]); }
}

int main() {
	int n;
	cin >> n;

	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	sort(nums.begin(), nums.end());

	makeDistinct(nums, n);

	if (distNums.size() > 3) { cout << -1 << endl; return 0; }
	if (distNums.size() == 1) { cout << 0 << endl; return 0; }

	if (distNums.size() == 2) {
		int diff = distNums[1] - distNums[0];
		if (diff % 2 == 0) {
			cout << diff / 2 << endl;
		}
		else {
			cout << diff << endl;
		}
		return 0;
	}
	
	//size is 3
	if (distNums[1] - distNums[0] != distNums[2] - distNums[1]) {
		cout << -1 << endl; return 0;
	}
	
	cout << distNums[1] - distNums[0] << endl;
}