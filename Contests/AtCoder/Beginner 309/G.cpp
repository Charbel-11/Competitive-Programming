#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

ll dp[102][102][1050];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    dp[0][0][0] = 1;
	int n, x; cin >> n >> x;
    int numTaken = (1 << (2*x - 1));
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= i; j++){
            for(int k = 0; k < numTaken; k++){
                dp[i+1][j][k/2] += dp[i][j][k];
                dp[i+1][j][k/2] %= mod;

                for(int m = -x + 1; m <= x-1; m++){
                    if (i+1 + m <= n && i+1 + m >= 1){
                        int b = m + x - 1;
                        if (!((1 << b) & (k/2))){
                            int curK = k/2 + (1<<b);
                            dp[i+1][j+1][curK] += dp[i][j][k];
                            dp[i+1][j+1][curK] %= mod;
                        }
                    }
                }
            }
        }
    }

    vector <ll> fact(n + 1, 1);
    for(int i = 2; i < fact.size(); i++){
        fact[i] = fact[i-1] * i;
        fact[i] %= mod;
    }

    ll ans = 0;
    for(int j = 0; j <= n; j++){
        int factor = (j % 2 == 0 ? 1 : -1);
        for(int k = 0; k < numTaken; k++){
            ans += factor * dp[n][j][k] * fact[n-j];
            ans %= mod;
        }
    }

    if (ans < 0){ ans += mod; }
    cout << ans << '\n';
}