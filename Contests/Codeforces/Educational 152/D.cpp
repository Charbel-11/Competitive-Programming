#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<int> a(n); for(auto &x : a){ cin >> x; }

    vector<int> last0(n, -1);
    int curLast = -1;
    for(int i = 0; i < n; i++){
        if (a[i] == 0){ curLast = i; }
        last0[i] = curLast;
    }

    vector<vector<int>> dp(n, vector<int>(3, n));
    dp[0][a[0]] = 1;
    for(int i = 1; i < n; i++){
        int minBef = min({dp[i-1][0], dp[i-1][1], dp[i-1][2]});

        // Buy and don't cover prev
        dp[i][a[i]] = min(dp[i][a[i]], 1 + minBef);

        // Buy and cover prev
        if (a[i] > 0){
            int prev0 = last0[i], extra = 0;
            if (prev0 > 0){ extra = min({dp[prev0 - 1][0], dp[prev0 - 1][1], dp[prev0 - 1][2]}); }
            dp[i][a[i] - 1] = min(dp[i][a[i] - 1], 1 + extra);
        }

        // Don't buy
        dp[i][a[i]] = min({dp[i][a[i]], dp[i-1][1], dp[i-1][2]});
    }

    int ans = min({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
    cout << ans << '\n';
}