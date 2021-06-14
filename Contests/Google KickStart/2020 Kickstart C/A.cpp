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
		int n, k; cin >> n >> k;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }

		int cur = k, ans = 0;
		for (int i = 0; i < n; i++) {
			if (nums[i] == cur) { cur--; }
			else if (nums[i] == k) { cur = k-1; }
			else { cur = k; }
			if (cur == 0) { ans++; cur = k; }
		}

		cout << "Case #" << qq << ": " << ans << endl;
	}
}