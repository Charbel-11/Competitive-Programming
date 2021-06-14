#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int n, m; cin >> n >> m;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	set<int> mods;
	for (auto &x : nums) {
		if (mods.count(x%m)) { cout << 0 << endl; return 0; }
		mods.insert(x%m);
	}

	ll ans = 1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			ans *= abs(nums[i] - nums[j]);
			ans %= m;
		}
	}

	cout << ans << endl;
}