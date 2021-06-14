#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll pow2[402];
ll mod;
ll comb[402][402];

void fillComb() {
	int limit = 402;	//change if needed
	for (int i = 0; i < limit; i++) { comb[i][i] = 1; comb[i][0] = 1; }
	for (int i = 1; i < limit; i++)
		for (int j = 1; j < i; j++)
			comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n; cin >> mod;

	fillComb(); pow2[0] = 1;
	for (int i = 1; i <= n; i++) {
		pow2[i] = pow2[i - 1] * 2; pow2[i] %= mod;
	}

	vector<vector<ll>> dp(n + 1, vector<ll>(n+1, 0));
	for (int i = 1; i <= n; i++) {
		dp[i][i] = pow2[i - 1];
		for (int j = i - 1; j > 1; j--) {
			int sufRange = i - j;
			for (int k = 1; k <= j - 1; k++) {
				ll cur = pow2[sufRange - 1] * dp[j - 1][k]; cur %= mod;
				cur *= comb[sufRange + k][k]; cur %= mod;
				dp[i][sufRange + k] += cur; dp[i][sufRange + k] %= mod;
			}
		}
	}


	ll ans = 0;
	for (int i = 1; i <= n; i++) { ans += dp[n][i]; ans %= mod; }
	cout << ans << '\n';
}