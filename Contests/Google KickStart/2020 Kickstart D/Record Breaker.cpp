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

	for (int qq = 1; qq <= t; qq++) {
		int n; cin >> n;
		vector<int> nums(n + 1, -1);
		for (int i = 0; i < n; i++) { cin >> nums[i]; }

		int curMax = -1, res = 0;
		for (int i = 0; i < n; i++) {
			if (nums[i] > curMax && nums[i] > nums[i + 1]) { res++; }
			curMax = max(curMax, nums[i]);
		}

		cout << "Case #" << qq << ": " << res << '\n';
	}
}