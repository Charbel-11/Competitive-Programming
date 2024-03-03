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

    while (A.size() > N + M - 1) { A.pop_back(); }
    return A;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    int n, k; cin >> n >> k; ll ans = 0;
    vector<ll> initWays(7, 1); initWays[0] = 0;
    vector<ll> curWays = initWays;

    ll inv6 = modInv(6);
    vector<ll> modInv6(k + 1, 1);
    for(int i = 1; i <= k; i++){
        modInv6[i] = modInv6[i-1] * inv6;
        modInv6[i] %= mod;
    }

    vector<vector<ll>> expWays;
    expWays.push_back({1, 0, 0, 0, 0, 0, 0});
    expWays.push_back(initWays);
    while(expWays.back().size() <= n/2){
        curWays = polyModMult(curWays, curWays);
        expWays.push_back(curWays);
    }

    curWays.clear(); curWays.resize(7, 0);
    curWays[0] = 1; int idx = 1;
    int neededRounds = (n+5)/6, passedRounds = (n+5)/6;
    while(neededRounds){
        if (neededRounds & 1){
            curWays = polyModMult(curWays, expWays[idx]);
        }
        idx++; neededRounds /= 2;
    }

    ll kInv = modInv(k);
    for(int i = passedRounds; i <= k; i++){
        ll curFact = (curWays[n] * kInv) % mod;
        curFact *= modInv6[i]; curFact %= mod;
        ans += curFact; ans %= mod;

        curWays = polyModMult(curWays, initWays);
        while(curWays.size() > n + 1){ curWays.pop_back(); }
    }

    cout << ans << '\n';
}

