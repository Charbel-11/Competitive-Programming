#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
    vector<string> grid(n);
    for(auto &s : grid){ cin >> s; }

    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < m; j++){
            if (grid[i][j] == '#'){
                grid[i+1][j] = '#';
                if (j + 1 < m){ grid[i+1][j+1] = '#'; }
            }
        }
    }

    vector<ll> dp(n + 1, 0); dp[n] = 1;
    for(int j = 0; j < m; j++){
        dp[n] += dp[n-1];
        for(int i = n - 1; i >= 0; i--){
            dp[i] = dp[i+1] + (i ? dp[i-1] : 0);
            dp[i] %= mod;
        }
        for(int i = 1; i <= n; i++){
            if (grid[i-1][j] == '#'){ dp[i] = 0; }
        }
    }

    ll ans = 0;
    for(auto &x : dp){ ans += x; ans %= mod; }
    cout << ans << '\n';
}