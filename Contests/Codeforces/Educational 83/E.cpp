#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	for (int i = 1; i <= 1000; i++) {
		vector<int> cur;

		for (int j = 0; j < nums.size(); j++) {
			if (j < nums.size()-1 && nums[j] == nums[j + 1] && nums[j] == i) {
				cur.push_back(nums[j] + 1);
				j++;
			}
			else {
				cur.push_back(nums[j]);
			}
		}

		nums = cur;
	}

	cout << nums.size() << endl;
}