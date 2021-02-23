#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	ll res = 1;
	for (; p; p >>= 1, x = (x * x) % mod)
		if (p & 1) res = (res * x) % mod;
	return res;
}

// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }


// a*x - b*y = return value = GCD(a,b). x,y >= 0
ll egcd(ll a, ll b, ll &x, ll &y) { // MINUS B*Y
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}

	ll d = egcd(b, a%b, y, x);
	y = a - x * (a / b) - y;
	x = b - x;
	return d;
}
// modular inverse; works for any mod p (coprime with a)
ll inverse(ll a, ll p = mod) {
	ll x, y;
	egcd(a%p + p, p, x, y);
	return x % p;
}


ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
// solves the system of congruences:
// x = a (mod m)
// x = b (mod n)
// returns res such that x = res (mod lcm(m,n))
// no such res => throws 0 (so you must wrap it in try { ... } catch (int _) { ... }
ll CRT(ll a, ll m, ll b, ll n) {
	b = (b + n - (a%n)) % n;
	ll d = gcd(m, n);
	if (b%d != 0) throw 0;

	ll oldM = m;
	m /= d; b /= d; n /= d;
	return ((b*inverse(m, n)) % n)*oldM + a;
}