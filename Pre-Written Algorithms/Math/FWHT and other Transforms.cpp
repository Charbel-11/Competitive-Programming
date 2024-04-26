#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//By X convolution, we mean (ax^i).(bx^j) becomes abx^(iXj) where X can be XOR, AND, OR
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
        for (ll& x : a) { x /= n; }
    }
}
vector<ll> convolution(const vector<ll>& a, const vector<ll>& b, type T) {
    vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int s = max(a.size(), b.size()), n = 1;
    while (n < s) { n <<= 1; }
    fa.resize(n);  fb.resize(n);

    FWHT(fa, false, T); FWHT(fb, false, T);     //If fa=fb, no need to call it twice
    for (int i = 0; i < n; i++) { fa[i] *= fb[i]; }
    FWHT(fa, true, T);

    return fa;
}