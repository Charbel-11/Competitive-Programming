// https://csacademy.com/contest/archive/task/and-closure/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
    ll res = 1;
    for (; p; p >>= 1, x = (x * x) % mod) {
        if (p & 1) { res = (res * x) % mod; }
    }
    return res;
}


//By X convolution, we mean ax^i.bx^j becomes abx^(iXj) where X can be XOR, AND, OR
//Modular arithmetic works here (just add mod after each operation and use modInv)
enum type {XOR, AND, OR};
void FWHT(vector<ll>& a, bool inverse, type T) {
    int n = a.size();       // Assumes n is a power of 2
    for (int len = 2; len <= n; len <<= 1) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < (len >> 1); j++) {
                ll u = a[i + j], v = a[i + j + (len >> 1)];
                if (T == XOR) { a[i + j] = u + v; a[i + j + (len >> 1)] = u - v; }
                else if (T == AND){
                    if (!inverse) { a[i + j] = v; a[i + j + (len >> 1)] = (u + v) % mod; }
                    else { a[i + j] = (v - u + mod) % mod; a[i + j + (len >> 1)] = u; }
                }
                else if (T == OR){
                    if (!inverse) { a[i + j] = u; a[i + j + (len >> 1)] = u + v; }
                    else { a[i + j] = u; a[i + j + (len >> 1)] = v - u; }
                }
            }
        }
    }
    if (T == XOR && inverse) {
        for (ll& x : a) { x /= n; }
    }
}
vector<ll> convolution(const vector<ll>& a, int N, type T) {
    vector<ll> fa(a.begin(), a.end());

    int s = a.size(), n = 1;
    while (n < s) { n <<= 1; }
    fa.resize(n);

    FWHT(fa, false, T);
    for (int i = 0; i < n; i++) { fa[i] = powe(fa[i], N); }
    FWHT(fa, true, T);

    return fa;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    vector<ll> freq(1e6 + 2, 0); freq[0] = 1;
    for (int i = 0; i < n; i++) {
        int cur; cin >> cur;
        freq[cur] = 1;
    }

    auto numWays = convolution(freq, n, AND);
    int ans = 0;
    for (auto& x : numWays) {
        if (x) { ans++; }
    }
    cout << ans << '\n';
}