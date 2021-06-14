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
		int n, x; cin >> n >> x;
		vector<int> nums(n);
		int ss = 0;
		for (auto &x : nums) { cin >> x; ss += x; }

		int res = -1;
		int curS = ss;
		if (curS%x) { res = n; }
		for (int i = 0; i < n - 1; i++) {
			curS -= nums[i];
			if (curS%x) { res = max(res, n - i - 1); break; }
		}
		curS = ss;
		for (int i = n - 1; i > 0; i--) {
			curS -= nums[i];
			if (curS%x) { res = max(res, i); break; }
		}
		cout << res << '\n';
	}
}