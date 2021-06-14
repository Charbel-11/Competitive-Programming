#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }

		set<int> remaining;
		for (int i = 1; i <= 2 * n; i++) {
			remaining.insert(i);
		}

		bool OK = true;
		vector<int> res(2*n);
		for (int i = 0; i < 2 * n; i += 2) {
			res[i] = nums[i/2];
			if (!remaining.count(nums[i/2])) { OK = false; break; }
			remaining.erase(nums[i/2]);
		}

		if (!OK) { cout << -1 << endl; continue; }

		for (int i = 1; i < 2 * n; i += 2) {
			auto it = remaining.upper_bound(res[i - 1]);
			if (it == remaining.end()) { OK = false; break; }
			res[i] = *it;
			remaining.erase(it);
		}

		if (!OK) { cout << -1 << endl; continue; }

		for (auto &x : res) { cout << x << " "; }cout << endl;
	}
}