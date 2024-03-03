#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
    ll res = 1; x %= mod;
    for (; p; p >>= 1, x = (x * x) % mod)
        if (p & 1) res = (res * x) % mod;
    return res;
}
// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

const int SZ = (int)2e7 + 1;
ll fact[SZ];
void fillFact() {
    fact[0] = 1;
    for (int i = 1; i < SZ; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= mod;
    }
}

ll choose(ll n, ll k) {
    if (k > n) { return 0; }
    ll num = fact[n], denom = fact[k];
    denom *= fact[n - k]; denom %= mod;

    ll multInv = modinv(denom);
    num *= multInv; num %= mod;
    return num;
}


int main() {
    int k, n; cin >> k >> n;
    vector<ll> ans((1<<k), 0);

    if (k == 1){ cout << (1<<(n-1)) << '\n'; return 0; }

    fillFact();
    for(int i = 0; i <= n; i++){
        int m = i % (1 << k);
        ans[m] += choose(n, i);
    }

    for(auto &x : ans){ cout << x << ' '; }
}