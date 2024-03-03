#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while(t--){
        int n; ll c; cin >> n >> c; n++;
        vector<ll> r(n), f(n, 0); cin >> r[0];
        for(int i = 1; i < n; i++){
            cin >> f[i] >> r[i];
        }

        vector<vector<ll>> dp(n, vector<ll>(2, 1e15));
        dp[0][1] = r[0] * c;
        for(int i = 1; i < n; i++){
            ll dist = 0;
            for(int j = i-1; j >= 0; j--){
                dist += f[j+1];

                if (dist > c){ break; }
                dp[i][0] = min(dp[i][0], dp[j][1]);
                dp[i][1] = min(dp[i][1], dp[j][1] + dist * r[i] + 500);
            }
        }

        cout << min(dp[n-1][0], dp[n-1][1]) << '\n';
    }
}