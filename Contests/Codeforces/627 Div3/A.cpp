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
		int maxNum = 0;
		for (auto &x : nums) { cin >> x; maxNum = max(maxNum, x); }

		bool OK = true;
		for (int i = 0; i < n; i++) {
			if (nums[i] % 2 != maxNum % 2) {
				OK = false; break;
			}
		}

		cout << (OK ? "YES" : "NO") << endl;
	}
}