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
		vector<int> nums(n); for (auto &x : nums) { cin >> x; }

		int r = n - 2;
		while (r >= 0 && nums[r] >= nums[r + 1]) { r--; }
		r--;
		while (r >= 0 && nums[r] <= nums[r + 1]) { r--; }
		r++;

		cout << max(r, 0) << '\n';
	}
}