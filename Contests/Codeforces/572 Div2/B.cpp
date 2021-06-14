#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;
	
	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	sort(nums.begin(), nums.end());

	int temp = nums[n - 1];
	nums[n - 1] = nums[n - 2];
	nums[n - 2] = temp;

	if (nums[n - 2] >= nums[n - 1] + nums[n - 3]) {
		cout << "NO" << endl;
	}
	else {
		cout << "YES" << endl;
		for (int i = 0; i < n; i++) {
			cout << nums[i] << " ";
		}
		cout << endl;
	}
}