#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll dp[3002][6014];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; ll mod; cin >> n >> mod;
	dp[0][0] = 1; dp[1][0] = -1;

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= 2 * i; j++) {
			if (i > 0) { dp[i][j] += dp[i - 1][j]; dp[i][j] %= mod; }

			int l = 1;
			for (int k = 2; k <= 5; k++) {
				if (i + l > n || j + k > 2 * n) { break; }
				dp[i + l][j + k] += dp[i][j] * (i == 0 ? 26 : 25);
				dp[i + l][j + k] %= mod;

				if (i + l * 10 <= n) {
					dp[i + l * 10][j + k] -= dp[i][j] * (i == 0 ? 26 : 25);
					dp[i + l * 10][j + k] %= mod;
					if (dp[i + l * 10][j + k] < 0) { dp[i + l * 10][j + k] += mod; }
				}

				l *= 10;
			}
		}
	}

	ll ans = 0;
	for (int j = 1; j < n; j++) {
		ans += dp[n][j];
		ans %= mod;
	}
	cout << ans << '\n';
}