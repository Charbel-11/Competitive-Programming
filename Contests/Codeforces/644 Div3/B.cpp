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
		sort(nums.begin(), nums.end());
		int res = INT_MAX;
		for (int i = 1; i < n; i++) {
			res = min(res, nums[i] - nums[i - 1]);
		}
		cout << res << endl;
	}
}