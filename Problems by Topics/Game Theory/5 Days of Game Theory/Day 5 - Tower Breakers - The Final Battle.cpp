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

	vector<ll> dp(256, 0);		// dp[x] = max height of tower that leads to at most x coins
	dp[0] = 1;
	for (int i = 1; i < 256; i++) {
		if (dp[i - 1] >= 1e18) { dp[i] = dp[i - 1]; continue; }
		for (int j = 1; j * j <= i; j++) {
			int coinCost = j * j;
			dp[i] += dp[i - coinCost];	// sum of the initial heights at indices j=1,2,...,root(i)
		}
	}

	int t; cin >> t;
	while (t--) {
		ll n; cin >> n;
		int ans = lower_bound(dp.begin(), dp.end(), n) - dp.begin();
		cout << ans << '\n';
	}
}