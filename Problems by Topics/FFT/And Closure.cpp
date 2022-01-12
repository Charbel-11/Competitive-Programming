// https://csacademy.com/contest/archive/task/and-closure/

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
const ll mod = 1e9 + 7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
    ll res = 1;
    for (; p; p >>= 1, x = (x * x) % mod) {
        if (p & 1) { res = (res * x) % mod; }
    }
    return res;
}

void andTransform(vector<ll>& a, bool inverse) {
    int n = a.size();       // Assumes n is a power of 2

    for (int len = 2; len <= n; len <<= 1) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < (len >> 1); j++) {
                ll u = a[i + j];
                ll v = a[i + j + (len >> 1)];

                if (!inverse) {
                    a[i + j] = v;
                    a[i + j + (len >> 1)] = (u + v) % mod;
                }
                else {
                    a[i + j] = (v - u + mod) % mod;
                    a[i + j + (len >> 1)] = u;
                }
            }
        }
    }
}

//Xor convolution in O(nlogn)
vector<ll> xorExp(vector<ll>& a, int N) {
    vector<ll> fa(a.begin(), a.end());

    int s = a.size(), n = 1;
    while (n < s) { n <<= 1; }
    fa.resize(n);

    andTransform(fa, false);
    for (int i = 0; i < n; i++) { fa[i] = powe(fa[i], N); }
    andTransform(fa, true);

    return move(fa);
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

    auto numWays = xorExp(freq, n);
    int ans = 0;
    for (auto& x : numWays) {
        if (x) { ans++; }
    }
    cout << ans << '\n';
}