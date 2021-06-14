#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;

	int zeros = 0;
	vector<int> nums;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;

		t = t % k;
		if (t == 0) {
			zeros++;
		}
		else {
			nums.push_back(t);
		}
	}

	int res = (zeros % 2 == 0) ? zeros : zeros - 1;
	sort(nums.begin(), nums.end());

	if (nums.size() > 0) {
		int a = 0;
		int b = nums.size() - 1;
		int maxPoss = k - nums[a];

		while (a<b) {
			while (b>=0 && nums[b] > maxPoss) {
				b--;
			}
			if (a >= b) {			//important to avoid repetitions
				break;
			}
			if (b>=0 && nums[b] == maxPoss) {
				res += 2;
				a++;
				b--;
				maxPoss = k - nums[a];
			}
			else {
				a++;
				maxPoss = k - nums[a];
			}
		}
	}

	cout << res << endl;
}