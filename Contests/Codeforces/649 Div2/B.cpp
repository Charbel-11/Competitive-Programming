#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }

		vector<int> ans;
		ans.push_back(nums[0]);
		bool inc = nums[1] > nums[0];
		int i = 1;
		while (i < n) {
			if (inc) {
				while (i < n && nums[i] > nums[i - 1]) { i++; }
				i--;
				ans.push_back(nums[i]);
			}
			else {
				while (i < n && nums[i] < nums[i - 1]) { i++; }
				i--;
				ans.push_back(nums[i]);
			}
			inc = !inc; i++;
		}

		cout << ans.size() << '\n';
		for (auto &x : ans) { cout << x << ' '; }
		cout << '\n';
	}
}