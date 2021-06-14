#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
	int T; cin >> T;
	while (T--) {
		int n; cin >> n;
		vector<int> nums(n);
		map<int, int> m;
		for (auto &x : nums) { cin >> x; m[x] = -1; }

		int res = n + 1;

		int i = 0, j = 0;
		while (j < n) {
			if (m[nums[j]] != -1 && m[nums[j]] >= i) {
				i = m[nums[j]];
				res = min(res, j - i + 1);
				i++;
			}
			m[nums[j]] = j; j++;
		}

		if (res == n + 1) { res = -1; }
		cout << res << endl;
	}
}