#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int q;
	cin >> q;

	for (int z = 0; z < q; z++) {
		int n; cin >> n;
		vector<int> nums(4 * n);
		for (int i = 0; i < 4*n; i++) {
			cin >> nums[i];
		}

		sort(nums.begin(), nums.end());
		int area = nums[0] * nums[4*n - 1];
		
		bool OK = true;
		for (int i = 0; i < 4 * n; i+=2) {
			if (nums[i] != nums[i + 1] || nums[4 * n - i - 1] != nums[4 * n - i - 2] || nums[i] * nums[4*n-i-1] != area) {
				OK = false; break;
			}
		}
		if (OK) { cout << "YES" << endl; }
		else { cout << "NO" << endl; }
	}
}