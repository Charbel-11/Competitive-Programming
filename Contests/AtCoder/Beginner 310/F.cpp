#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
    ll res = 1;
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

	int n; cin >> n;
    vector<ll> A(n); for(auto &x : A){ cin >> x; }

    vector<vector<ll>> dp(n + 1, vector<ll>((1<<11), 0));
    dp[0][1] = 1;

    for(int i = 0; i < n; i++){
        ll curMInv = modinv(A[i]);
        for(int j = 1; j < (1<<11); j++){
            if (dp[i][j] == 0){ continue; }
            for(int k = 1; k <= min(A[i], 10ll); k++){
                int nxtMask = (j | (j << k)) & ((1 << 11)-1);
                dp[i+1][nxtMask] += (dp[i][j] * curMInv) % mod;
                dp[i+1][nxtMask] %= mod;
            }
            if (A[i] > 10){
                ll fact = ((A[i]-10) * curMInv) % mod;
                dp[i+1][j] += (dp[i][j] * fact) % mod;
                dp[i+1][j] %= mod;
            }
        }
    }

    ll ans = 0;
    for(int j = (1<<10); j < (1<<11); j++) {
        ans += dp[n][j];
        ans %= mod;
    }
    if (ans < 0){ ans+=mod; }
    cout << ans << '\n';
}