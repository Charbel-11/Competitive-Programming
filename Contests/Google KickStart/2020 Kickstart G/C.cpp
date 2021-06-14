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
		ll W, N; cin >> W >> N;
		vector<ll> nums(W); for (auto& x : nums) { cin >> x; }

		sort(nums.begin(), nums.end());

		vector<ll> prefRoundCost(W, 0), sufRoudnCost(W, 0);
		prefRoundCost[0] = nums[0];
		for (int i = 1; i < W; i++) { prefRoundCost[i] = prefRoundCost[i - 1] + nums[i]; }
		sufRoudnCost[W - 1] = N - nums[W - 1] + 1;
		for (int i = W - 2; i >= 0; i--) { sufRoudnCost[i] = sufRoudnCost[i + 1] + N - nums[i] + 1; }

		vector<ll> prefDiff(W, 0), sufDiff(W, 0);
		for (int i = 1; i < W; i++) {
			prefDiff[i] = (nums[i] - nums[i - 1]) * i + prefDiff[i - 1];
		}
		for (int i = W - 2; i >= 0; i--) {
			sufDiff[i] = (nums[i + 1] - nums[i]) * (W - i - 1) + sufDiff[i + 1];
		}

		ll ans = 1e17;
		for (int j = 0; j < W; j++) {
			ll cur = 0;

			ll l = nums[j] - N / 2, r = nums[j] + N / 2;

			if (l <= nums[0]) { cur += prefDiff[j]; }
			else {
				ll idxL = lower_bound(nums.begin(), nums.end(), l) - nums.begin();
				cur += (prefDiff[j] - (prefDiff[idxL] + idxL * (nums[j] - nums[idxL])));
				cur += prefRoundCost[idxL - 1] + idxL * (N - nums[j]);
			}
			if (r >= nums[W - 1]) { cur += sufDiff[j]; }
			else {
				ll idxR = upper_bound(nums.begin(), nums.end(), r) - nums.begin() - 1ll;
				ll cnt = W - idxR - 1;
				cur += (sufDiff[j] - (sufDiff[idxR] + cnt * (nums[idxR] - nums[j])));
				cur += sufRoudnCost[idxR + 1] + cnt * (nums[j] - 1);
			}

			ans = min(ans, cur);
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}