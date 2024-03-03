#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;

    vector<ll> fact(n + 1, 1);
    for(ll i = 2; i <= n; i++){
        fact[i] = i * fact[i-1];
        fact[i] %= mod;
    }

    //dp[i][j] = ans for arrays of len i s.t. their last j elements are distinct (but j+1 aren't)
    vector<vector<ll>> dpSum(n+1, vector<ll>(k+1, 0));
    vector<vector<ll>> dp(n+1, vector<ll>(k+1, 0));
    vector<vector<ll>> dpSum2(n+1, vector<ll>(k+1, 0));
    vector<vector<ll>> numWays(n+1, vector<ll>(k+1, 0));
    numWays[0][0] = 1;
    for(int j = 0; j <= k; j++){ dpSum2[0][j] = 1;}
    for(int i = 1; i <= n; i++) {
        for (int j = 1; j < k; j++) {
            numWays[i][j] = (dpSum2[i-1].back() - dpSum2[i-1][j-1] + mod) % mod;
            numWays[i][j] += ((k-j+1)*numWays[i-1][j-1]) % mod; numWays[i][j] %= mod;

            dpSum2[i][j] = dpSum2[i][j-1] + numWays[i][j];
            dpSum2[i][j] %= mod;
        }

        if (i >= k) { numWays[i][k] = (dpSum2[i-k].back() * fact[k]) % mod; }
        dpSum2[i][k] = dpSum2[i][k-1] + numWays[i][k];
        dpSum2[i][k] %= mod;
    }

    for(int i = k; i <= n; i++){
        for(int j = 1; j < k; j++) {
            dp[i][j] = (dpSum[i-1].back() - dpSum[i-1][j-1] + mod) % mod;
            dp[i][j] += ((k-j+1)*dp[i-1][j-1]) % mod; dp[i][j] %= mod;

            dpSum[i][j] = dpSum[i][j-1] + dp[i][j];
            dpSum[i][j] %= mod;
        }

        dp[i][k] = ((dpSum[i-k].back() + dpSum2[i-k].back()) * fact[k]) % mod;
        dpSum[i][k] = dpSum[i][k-1] + dp[i][k];
        dpSum[i][k] %= mod;
    }

    cout << dpSum[n].back() << '\n';
}