#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	sort(nums.begin(), nums.end());

	int i = 0;
	int j = 1;			//2 counters to keep the complexity O(n); we know all the numbers between i and j have a diff of at most 5
	int res = 1;		//we should use this information
	int curRes = 1;
	while (i < n && j < n) {
		while (j<n && nums[j] - nums[i] <= 5) {				//Boundary checks
			j++;
		}
		curRes = j - i;
		if (curRes > res) {
			res = curRes;
		}
		i++;
	}

	cout << res << endl;
}