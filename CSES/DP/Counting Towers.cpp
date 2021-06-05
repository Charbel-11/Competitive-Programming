#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll dp[(int)1e6 + 2][2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	dp[1][0] = dp[1][1] = 1;
	for (int i = 2; i <= 1e6; i++) {
		dp[i][0] = dp[i][1] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
		dp[i][0] += 3 * dp[i - 1][0]; dp[i][0] %= mod;
		dp[i][1] += dp[i - 1][1]; dp[i][1] %= mod;
	}

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		ll ans = dp[n][0] + dp[n][1]; ans %= mod;
		cout << ans << '\n';
	}
}
