// https://csacademy.com/contest/archive/task/random_nim_generator/
#include <bits/stdc++.h>
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


//By X convolution, we mean ax^i.bx^j becomes abx^(iXj) where X can be XOR, AND, OR
enum type {XOR, AND, OR};
void FWHT(vector<ll>& a, bool inverse, type T) {
    int n = a.size();       // Assumes n is a power of 2
    for (int len = 2; len <= n; len <<= 1) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < (len >> 1); j++) {
                ll u = a[i + j], v = a[i + j + (len >> 1)];
                if (T == XOR) { a[i + j] = u + v; a[i + j + (len >> 1)] = (u - v + mod) % mod; }
                else if (T == AND){
                    if (!inverse) { a[i + j] = v; a[i + j + (len >> 1)] = u + v; }
                    else { a[i + j] = v - u; a[i + j + (len >> 1)] = u; }
                }
                else if (T == OR){
                    if (!inverse) { a[i + j] = u; a[i + j + (len >> 1)] = u + v; }
                    else { a[i + j] = u; a[i + j + (len >> 1)] = v - u; }
                }
            }
        }
    }
    if (T == XOR && inverse) {
        for (ll& x : a) { x *= modinv(n); x %= mod; }
    }
}
vector<ll> convolution(const vector<ll>& a, const vector<ll>& b, type T) {
    vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int s = max(a.size(), b.size()), n = 1;
    while (n < s) { n <<= 1; }
    fa.resize(n);  fb.resize(n);

    FWHT(fa, false, T); FWHT(fb, false, T);
    for (int i = 0; i < n; i++) { fa[i] *= fb[i]; fa[i] %= mod; }
    FWHT(fa, true, T);

    return fa;
}

vector<ll> xorExponentiate(vector<ll> a, ll n) {
    vector<ll> x; bool doneFirst = false;
    for (; n; n >>= 1, a = convolution(a, a, XOR)) {
        if (n & 1) {
            if (!doneFirst) { x = a; doneFirst = true; }
            else { x = convolution(x, a, XOR); }
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

    FWHT(fa, false, XOR);
    for (int i = 0; i < n; i++) { fa[i] = powe(fa[i], N); }
    FWHT(fa, true, XOR);

    return fa;
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