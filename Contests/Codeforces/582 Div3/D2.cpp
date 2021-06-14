#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>

using namespace std;
int n, k;

int main() {
	cin >> n >> k;
	vector<int> nums(n);
	map<int, pair<int, int>> res;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];

		res[nums[i]].first++; res[nums[i]].second = 0;
	}

	sort(nums.begin(), nums.end());

	for (auto x : nums) {
		int cost = 1;
		while (x != 0) {
			x /= 2;
			if (res[x].first < k) {
				res[x].first++;
				res[x].second += cost;
				cost++;
			}
		}
	}

	int finalR = INT_MAX;
	for (auto &x : res) {
		if (x.second.first >= k) {
			finalR = min(finalR, x.second.second);
		}
	}

	cout << finalR << endl;
}