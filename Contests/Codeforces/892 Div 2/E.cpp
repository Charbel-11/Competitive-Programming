#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, k; cin >> n >> k;
        vector<ll> a(n), b(n);
        for(auto &x : a){ cin >> x; }
        for(auto &x: b){ cin >> x; }

        vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, 0));
        vector<ll> max1(n+1, -1e16), max2(n+1, -1e16), max3(n+1, -1e16), max4(n+1, -1e16);
	    for(int i = 1; i <= n; i++){
            for(int j = 1; j <= min(i, k); j++){
                dp[i][j] = max(dp[i][j], dp[i-1][j]);

                int diag = i-j;
                max1[diag] = max(max1[diag], dp[i-1][j-1] - a[i-1] - b[i-1]);
                max2[diag] = max(max2[diag], dp[i-1][j-1] - a[i-1] + b[i-1]);
                max3[diag] = max(max3[diag], dp[i-1][j-1] + a[i-1] - b[i-1]);
                max4[diag] = max(max4[diag], dp[i-1][j-1] + a[i-1] + b[i-1]);

                dp[i][j] = max(dp[i][j], max1[diag] + a[i-1] + b[i-1]);
                dp[i][j] = max(dp[i][j], max2[diag] - a[i-1] + b[i-1]);
                dp[i][j] = max(dp[i][j], max3[diag] + a[i-1] - b[i-1]);
                dp[i][j] = max(dp[i][j], max4[diag] - a[i-1] - b[i-1]);
            }
        }

        cout << dp[n][k] << '\n';
    }
}