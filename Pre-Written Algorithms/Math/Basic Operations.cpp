#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
    ll res = 1; x %= mod;
    for (; p; p >>= 1, x = (x * x) % mod) {
        if (p & 1) { res = (res * x) % mod; }
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

// mod must be prime
ll modInv(ll i) { return powe(i, mod - 2); }
// works for any mod m coprime with a
ll modInv(ll a, ll m) {
    ll x, y, g = extGCD(a % m, m, x, y);
    if (g != 1) { return 0; }
    return (x % m + m) % m;
}

ll eulerPhi(ll n) {
	ll res = n;
	for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) { n /= i; }
            res -= res / i;
        }
    }
	if (n > 1) { res -= res / n; }
	return res;
}