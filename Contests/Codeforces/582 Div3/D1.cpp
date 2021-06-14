#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

int main() {
	int n, k; cin >> n >> k;
	vector<int> nums(n);
	map<int, int> freq;
	int maxN = 0;
	for (auto &x : nums) { 
		cin >> x; 
		maxN = max(maxN, x);
		freq[x]++; 
		if (freq[x] >= k) { cout << 0 << endl; return 0; }
	}

	sort(nums.begin(), nums.end());

	int minRes = INT_MAX;
	for (int finalN = 0; finalN <= maxN; finalN++) {
		int equal = 0, i = 0;
		while (i < n && nums[i] < finalN) { i++; }
		while (i < n && nums[i] == finalN) { equal++; i++; }
		if (i >= n) { continue; }

		int res = 0;
		while (i < n) {
			int temp = nums[i]; int tempCost = 0; 
			while (temp > finalN) { temp /= 2; tempCost++; }
			if (temp == finalN) {
				res += tempCost;
				equal++;
				if (equal >= k) { 
					minRes = min(minRes, res);
					break;
				}
			}
			i++;
		}
	}

	cout << minRes << endl;
}