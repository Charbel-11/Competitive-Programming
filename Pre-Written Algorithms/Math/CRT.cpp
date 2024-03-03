#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

//bx1+(a%b)y1=gcd -> bx1+(a-b*a/b)y1=gcd -> ay1+b(x1-y1.a/b)
//ax+by=gcd(a,b); sol of the form (x+k.b/gcd(a,b), y-k.a/gcd(a,b))
ll extGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0;	return a; }
    ll x1, y1, d = extGCD(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b);
    return d;
}
// works for any mod m coprime with a
ll modInv(ll a, ll m) {
    ll x, y, g = extGCD(a % m, m, x, y);
    if (g != 1) { return 0; }
    return (x % m + m) % m;
}

// solves the system of congruences for any a, b, n, m: x = a mod m  and  x = b mod n
// returns res such that x = res mod lcm(m,n) or -1 if there is no solution
ll CRT(ll a, ll m, ll b, ll n) {
	b = (b + n - (a % n)) % n;
	ll d = gcd(m, n);
	if (b % d != 0) { return -1; }

	ll oldM = m; m /= d; b /= d; n /= d;
	return ((b * modInv(m, n)) % n) * oldM + a;;
}

/*
x = a mod m = mk + a
x = b mod n = nk' + b
mk + a = nk' + b
mk + nk' = b-a -> divide by gcd(m,n) so that modinv is defined
mk = (b-a) mod n
k = modInv(m) * ((b-a)%n)
*/