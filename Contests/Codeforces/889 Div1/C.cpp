#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
    ll res = 1; x %= mod;
    for (; p; p >>= 1, x = (x * x) % mod) {
        if (p & 1) { res = (res * x) % mod; }
    }
    return res;
}
// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
    vector<int> S(n); for(auto &x : S){ cin >> x; x--; }

    vector<vector<ll>> dp(m + 1, vector<ll>(m + 1, m + 5));
    for(int i = 0; i <= m; i++){
        dp[i][m] = m - i;
        dp[i][i] = 0;
    }

    ll inv2 = modinv(2);
    for(int i = m - 1; i >= 0; i--){
        for(int j = m - 1; j >= i + 1; j--){
            dp[i][j] = (inv2 * ((1 + dp[i+1][j]) + dp[i][j+1])) % mod;
        }
    }

    ll ans = 0; S.push_back(m);
    for(int i = 0; i < n; i++){
        ans += dp[S[i]][S[i+1]];
        ans %= mod;
    }
    cout << ans << '\n';
}