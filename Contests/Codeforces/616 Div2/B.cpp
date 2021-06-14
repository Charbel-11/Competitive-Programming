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

		int cur = 0, i = 0, last = 0; bool up = true, OK = true;
		while (i < n) {
			if (cur < 0) { OK = false; break; }
			if (up) {
				if (nums[i] < cur) { 
					if (cur - 1 == nums[i] && last == nums[i]) {
						if (last == 0) { OK = false; break; }
						cur = nums[i] - 2;
					}
					else{ cur = nums[i] - 1; }
					up = false;
				}
				else { last = nums[i]; cur++; }
			}
			else {
				if (nums[i] < cur) { cur = nums[i] - 1; }
				else { cur--; }
			}

			i++;
		}

		cout << (OK ? "Yes" : "No") << endl;
	}
}