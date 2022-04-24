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
	for (int qq = 1; qq <= t; qq++) {
		int N, P; cin >> N >> P;
		vector<vector<ll>> products(N, vector<ll>(P));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < P; j++) {
				cin >> products[i][j];
			}
			sort(products[i].begin(), products[i].end());
		}
		
		vector<vector<ll>> dp(N, vector<ll>(2, 1e17));
		ll firstMax = products[0].back();
		dp[0][0] = firstMax + (firstMax - products[0][0]);
		dp[0][1] = products[0].back();

		for (int i = 1; i < N; i++) {
			ll curMax = products[i].back(), curMin = products[i][0];
			ll start0 = products[i - 1][0], start1 = products[i - 1].back();

			ll c0 = dp[i - 1][0] + abs(start0 - curMax) + curMax - curMin;
			ll c1 = dp[i - 1][1] + abs(start1 - curMax) + curMax - curMin;
			dp[i][0] = min(c0, c1);

			c0 = dp[i - 1][0] + abs(start0 - curMin) + curMax - curMin;
			c1 = dp[i - 1][1] + abs(start1 - curMin) + curMax - curMin;
			dp[i][1] = min(c0, c1);
		}

		ll ans = *min_element(dp.back().begin(), dp.back().end());
		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
