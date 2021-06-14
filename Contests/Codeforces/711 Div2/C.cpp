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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, K; cin >> n >> K;

		vector<vector<ll>> dp(n + 1, vector<ll>(K + 1, 0));

		for (int i = 0; i <= n; i++) { dp[i][1] = 1; }
		for (int k = 0; k <= K; k++) { dp[0][k] = 1; }

		for (int k = 2; k <= K; k++) {
			for (int i = 1; i <= n; i++) {
				dp[i][k] = dp[n - i][k - 1] + dp[i - 1][k];
				dp[i][k] %= mod;
			}
		}

		cout << dp[n][K] << '\n';
	}
}
