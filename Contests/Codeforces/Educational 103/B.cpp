#include <iostream>
#include <string>
#include <map>
#include <set>
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
		int n, k; cin >> n >> k;
		vector<ll> nums(n); for (auto& x : nums) { cin >> x; }

		ll ans = 0, curP = nums[0];
		for (int i = 1; i < n; i++) {
			ll cur = nums[i] * 100;
			ll up = curP * k;

			if (up < cur) {
				ll add = (cur - up + k - 1) / k;
				ans += add;
				curP += nums[i] + add;
			}
			else { curP += nums[i]; }
		}
		cout << ans << '\n';
	}
}