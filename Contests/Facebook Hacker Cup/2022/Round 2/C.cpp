#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;

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

const int SZ = (int)1e7 + 10;
ll fact[SZ];
void fillFact() {
    fact[0] = 1;
    for (int i = 1; i < SZ; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= mod;
    }
}

//Handles nCk with mod for large n,k; uses mult inverse (Assumes mod is prime, otherwise use egcd)
ll choose(ll n, ll k) {
    if (k > n) { return 0; }
    ll num = fact[n], denom = fact[k];
    denom *= fact[n - k]; denom %= mod;

    ll multInv = modinv(denom);
    num *= multInv; num %= mod;
    return num;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    fillFact();
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";

        int n, k; cin >> n >> k;

        int N = 0, numBigger = 0;
        int numSmaller = 0, numEqual = 0;
        pair<int, int> firstChip;
        for(int i = 0; i < n; i++){
            int c, w; cin >> c >> w;
            if (i == 0) { firstChip = {w, c}; }

            N += c;
            if (w > firstChip.first) { numBigger += c; }
            else if (w < firstChip.first) { numSmaller += c; }
            else if (i > 0) { numEqual += c; }
        }

        if (k + 1 > N - numBigger) { cout << 0 << '\n'; continue; }
        ll ans = choose(N-numBigger, k+1) * modinv(choose(N, k+1));
        ans %= mod;

        N -= numBigger;
        int numMe = firstChip.second;

        ll probNotGettingIt = choose(N-numMe-numEqual, k+1) * modinv(choose(N, k+1));
        probNotGettingIt %= mod;
        ll probGettingIt = 1 - probNotGettingIt;
        probGettingIt %= mod;
        if (probGettingIt < 0){ probGettingIt += mod; }

        ans *= probGettingIt; ans %= mod;

        ll tmp = numMe * modinv(numMe + numEqual); tmp %= mod;
        ans *= tmp; ans %= mod;
        cout << ans << '\n';
    }
}