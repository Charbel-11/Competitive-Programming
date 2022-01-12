// https://csacademy.com/contest/archive/task/random_nim_generator/

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <complex>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 30011;

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



void FWHT(vector<ll>& a, bool inverse) {
    int n = a.size();       // Assumes n is a power of 2

    for (int len = 2; len <= n; len <<= 1) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < (len >> 1); j++) {
                ll u = a[i + j];
                ll v = a[i + j + (len >> 1)];
                a[i + j] = (u + v) % mod;
                a[i + j + (len >> 1)] = (u - v + mod) % mod;
            }
        }
    }

    if (inverse) {
        ll mInv = modinv(n);
        for (ll& x : a) { x *= mInv; x %= mod; }
    }
}

//Xor convolution in O(nlogn)
vector<ll> xorMultiply(const vector<ll>& a, const vector<ll>& b) {
    vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int s = max(a.size(), b.size()), n = 1;
    while (n < s) { n <<= 1; }
    fa.resize(n);  fb.resize(n);

    FWHT(fa, false); FWHT(fb, false);
    for (int i = 0; i < n; i++) { fa[i] *= fb[i]; fa[i] %= mod; }
    FWHT(fa, true);

    return move(fa);
}

vector<ll> xorExponentiate(vector<ll> a, ll n) {
    vector<ll> x; bool doneFirst = false;
    for (; n; n >>= 1, a = xorMultiply(a, a)) {
        if (n & 1) {
            if (!doneFirst) { x = a; doneFirst = true; }
            else { x = xorMultiply(x, a); }
        }
    }
    return move(x);
}

int N;

//Xor convolution in O(nlogn)
vector<ll> xorMultiply2(const vector<ll>& a) {
    vector<ll> fa(a.begin(), a.end());

    int s = a.size(), n = 1;
    while (n < s) { n <<= 1; }
    fa.resize(n);

    FWHT(fa, false);
    for (int i = 0; i < n; i++) { fa[i] = powe(fa[i], N); }
    FWHT(fa, true);

    return move(fa);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int k; cin >> N >> k;
    vector<ll> xorCand(k + 1, 1);
//    auto numW = xorMultiply2(xorCand);
    auto numW = xorExponentiate(xorCand, N);

    ll ans = 0;
    for (int i = 1; i < numW.size(); i++) {
        ans += numW[i]; ans %= mod;
    }
    cout << ans << '\n';
}