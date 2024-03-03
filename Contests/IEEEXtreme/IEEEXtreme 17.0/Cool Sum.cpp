#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const ll root = 3;
const ll invRoot = 332748118;
const int modPow = 23;
const ll oddFactor = 119;

ll power(ll x, ll n) {
    ll res = 1;
    for (; n; n >>= 1, x = (x * x) % mod) {
        if (n & 1) { res = (res * x) % mod; }
    }
    return res;
}

//bx1+(a%b)y1=gcd -> bx1+(a-b*a/b)y1=gcd -> ay1+b(x1-y1.a/b)
//ax+by=gcd(a,b); sol of the form (x+k.b/gcd(a,b), y-k.a/gcd(a,b))
ll extGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0;	return a; }
    ll x1, y1, d = extGCD(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b);
    return d;
}
ll modInv(ll a, ll m=mod) {
    ll x, y, g = extGCD(a % m, m, x, y);
    if (g != 1) { return 0; }
    return (x % m + m) % m;
}

void NTT(vector<ll>& a, const ll& curRoot) {
    int n = (int)a.size(); //Assumes n is a power of 2
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) { j ^= bit; }
        if (i < (j ^= bit)) { swap(a[i], a[j]); }
    }

    for (int len = 2; len <= n; len <<= 1) {
        ll Wn = curRoot;
        for (int i = len; i < n; i <<= 1) { Wn = (Wn * Wn) % mod; }

        for (int i = 0; i < n; i += len) {
            ll W = 1;
            for (int j = 0; j < (len >> 1); j++, W = (W * Wn) % mod) {
                ll even = a[i + j], odd = (W * a[i + j + (len >> 1)]) % mod;
                a[i + j] = even + odd < mod ? even + odd : even + odd - mod;
                a[i + j + (len >> 1)] = even - odd >= 0 ? even - odd : even - odd + mod;
            }
        }
    }
}

vector<ll> polyModMult(vector<ll>& a, vector<ll>& b) {
    vector<ll> A(a.begin(), a.end()), B(b.begin(), b.end());
    int N = (int)a.size(), M = (int)b.size();
    int n = 1, logN = 0;
    while (n < (N + M - 1)) { n <<= 1; logN++; }
    A.resize(n, 0); B.resize(n, 0);

    //Getting roots with cycle exactly n
    ll normFactor = oddFactor * power(2, modPow - logN);
    ll curRoot = power(root, normFactor);
    ll curInvRoot = power(invRoot, normFactor);

    NTT(A, curRoot); NTT(B, curRoot);
    for (int i = 0; i < n; i++) { A[i] = (A[i] * B[i]) % mod; }

    NTT(A, curInvRoot);
    ll invN = modInv(n);
    for (auto& x : A) { x = (x * invN) % mod; }
    for(int i = N; i < n; i++){ A[i % N] += A[i]; A[i%N] %= mod; }

    while (A.size() > N) { A.pop_back(); }
    return A;
}

struct Matrix {
    int n, m; vector<vector<ll>> v; Matrix() {}
    Matrix(vector<vector<ll>> &_v) : n(_v.size()), m(_v.front().size()), v(_v) {}
    Matrix(int _n, int _m, ll _x) : n(_n), m(_m), v(_n, vector<ll>(_m, _x)) {}
    Matrix(int _n) : n(_n), m(_n), v(_n, vector<ll>(_n, 0)) {
        for (int i = 0; i < _n; i++) { v[i][i] = 1; }
    }
    vector<ll>& operator[](int idx) { return v[idx]; }

    Matrix operator +(Matrix &rhs) {
        Matrix res(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res[i][j] = (v[i][j] + rhs[i][j]) % mod;
        return res;
    }
    Matrix operator *(Matrix &rhs) {
        Matrix res(n, rhs.m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < rhs.m; j++)
                for (int k = 0; k < m; k++)
                    res[i][j] = (res[i][j] + v[i][k] * rhs[k][j]) % mod;
        return res;
    }
    Matrix operator ^(ll x) {
        Matrix res(n), a(v); //Change if (*) changes
        for (; x; x >>= 1, a = a * a)
            if (x & 1) { res = res * a; }
        return res;
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int k, n; cin >> k >> n; int sz = (1<<k);

    if (k <= 0){
        Matrix M(sz); int idx = 0;
        M[0][0] = 1; M[sz-1][0] = 1;
        for(int j = 1; j < sz; j++){
            M[idx][j] = 1;
            M[++idx][j] = 1;
        }

        M = M ^ n;
        vector<ll> ans(sz);
        for(int i = 0; i < sz; i++){
            ans[i] = M[0][i];
        }
        for (auto &x: ans) { cout << x << ' '; }
    }
    else {
        vector<int> curDP(sz, 0); curDP[0] = 1;

        vector<ll> curWays(sz, 0);
        curWays[0] = curWays[1] = 1;

        int idx = 1;
        vector<vector<ll>> expWays;
        expWays.push_back(curWays);
        while(idx <= n/2){
            curWays = polyModMult(curWays, curWays);
            expWays.push_back(curWays);
            idx *= 2;
        }

        curWays.clear(); curWays.resize(sz, 0);
        curWays[0] = 1; idx = 0;
        int neededN = n;
        while(neededN){
            if (neededN & 1){
                curWays = polyModMult(curWays, expWays[idx]);
            }
            idx++; neededN /= 2;
        }

        vector<ll> only1(sz, 0); only1[0] = 1;
        curWays = polyModMult(curWays, only1);
        for(auto &x : curWays) { cout << x << ' '; }
    }
}

