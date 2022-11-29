#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void FWHT(vector<ll>& a, bool inverse) {
    int n = a.size();       // Assumes n is a power of 2

    for (int len = 2; len <= n; len <<= 1) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < (len >> 1); j++) {
                ll u = a[i + j];
                ll v = a[i + j + (len >> 1)];
                a[i + j] = u + v;
                a[i + j + (len >> 1)] = u - v;
            }
        }
    }

    if (inverse) {
        for (ll& x : a) { x /= n; }
    }
}

//Xor convolution in O(nlogn)
vector<ll> xorMultiply(const vector<ll>& a, const vector<ll>& b) {
    vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int s = max(a.size(), b.size()), n = 1;
    while (n < s) { n <<= 1; }
    fa.resize(n);  fb.resize(n);

    FWHT(fa, false); FWHT(fb, false);
    for (int i = 0; i < n; i++) { fa[i] *= fb[i]; }
    FWHT(fa, true);

    return fa;
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
                    a[i + j + (len >> 1)] = u + v;
                }
                else {
                    a[i + j] = v - u;
                    a[i + j + (len >> 1)] = u;
                }
            }
        }
    }
}

//And convolution in O(nlogn)
vector<ll> andMultiply(const vector<ll>& a, const vector<ll>& b) {
    vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int s = max(a.size(), b.size()), n = 1;
    while (n < s) { n <<= 1; }
    fa.resize(n);  fb.resize(n);

    andTransform(fa, false); andTransform(fb, false);
    for (int i = 0; i < n; i++) { fa[i] *= fb[i]; }
    andTransform(fa, true);

    return fa;
}


void orTransform(vector<ll>& a, bool inverse) {
    int n = a.size();       // Assumes n is a power of 2

    for (int len = 2; len <= n; len <<= 1) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < (len >> 1); j++) {
                ll u = a[i + j];
                ll v = a[i + j + (len >> 1)];

                if (!inverse) {
                    a[i + j] = u;
                    a[i + j + (len >> 1)] = u + v;
                }
                else {
                    a[i + j] = u;
                    a[i + j + (len >> 1)] = v - u;
                }
            }
        }
    }
}

//Or convolution in O(nlogn)
vector<ll> orMultiply(const vector<ll>& a, const vector<ll>& b) {
    vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int s = max(a.size(), b.size()), n = 1;
    while (n < s) { n <<= 1; }
    fa.resize(n);  fb.resize(n);

    orTransform(fa, false); orTransform(fb, false);
    for (int i = 0; i < n; i++) { fa[i] *= fb[i]; }
    orTransform(fa, true);

    return fa;
}