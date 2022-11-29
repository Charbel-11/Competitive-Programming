#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }

ll extGCD(ll a, ll b, ll &x, ll &y) {
	if (b == 0) { x = 1; y = 0;	return a; }
	ll x1, y1, d = extGCD(b, a % b, x1, y1);
	x = y1; y = x1 - y1 * (a / b);
	return d;
}

ll modInv(ll a, ll m) {
	ll x, y, g = extGCD(a, m, x, y);
	if (g != 1) { return 0; }
	return (x % m + m) % m;
}

bool isPrime(ll n) {
	if (n < 2) { return false; }
	if (n < 4) { return true; }

	for (ll i = 3; i * i <= n; i += 2)
		if (n % i == 0) { return false; }
	return true;
}

ll eulerPhi(ll n) {
	ll res = n;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0) {
			while (n % i == 0) { n /= i; }
			res -= res / i;
		}
	if (n > 1) { res -= res / n; }
	return res;
}

int divisorCount(ll n) {
	if (n == 1) { return 1; }

	int res = 2; ll i = 2;
	for (; i * i < n; i++) {
        if (n % i == 0) { res += 2; }
    }
	if (i * i == n) { res++; }

	return res;
}

ll power(ll x, ll p) {
	ll res = 1; x %= mod;
	for (; p; p >>= 1, x = (x * x) % mod) {
        if (p & 1) { res = (res * x) % mod; }
    }
	return res;
}