#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int n;
		cin >> n;

		vector<int> nums(n);
		for (int i = 0; i < n; i++) {
			cin >> nums[i];
		}

		sort(nums.begin(), nums.end());
		n -= 2;

		int base = nums[nums.size() - 2];
		base--;

		if (base > n) {
			cout << n << endl;
		}
		else {
			cout << base << endl;
		}
	}
}