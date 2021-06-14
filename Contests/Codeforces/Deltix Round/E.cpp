#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int SZ = 1e5 + 10;

ll fact[SZ];
void buildFact() {
    fact[0] = 1;
    for (int i = 1; i < SZ; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= mod;
    }
}

ll powe(ll x, ll p) {
    ll ans = 1;
    for (; p > 0; x = (x * x) % mod, p >>= 1) {
        if (p & 1) { ans *= x; ans %= mod; }
    }
    return ans;
}

ll modinv(ll n) {
    return powe(n, mod - 2);
}

ll choose(ll n, ll k) {
    if (k > n) { return 0; }

    ll ans = fact[n];
    ll den = fact[n - k] * fact[k]; den %= mod;
    ans *= modinv(den); ans %= mod;

    return ans;
}

int main() {
    buildFact();

    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        ll ans = 1;

        for (ll p = 1; n - (k - 1) * (p - 1) >= p - 1; p++) {
            ans += choose(n - (k - 1) * (p - 1), p) * modinv(choose(n, p));
            ans %= mod;
        }

        cout << ans << '\n';
    }
}