#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
typedef long long ll;

const long long mod = 1e9;
ll multiply(ll a, ll b) {
	ll res = 0;
	a %= mod; b %= mod;
	while (b > 0) {
		if (b % 2) {
			res += a; res %= mod;
		}
		a *= 2; a %= mod;
		b /= 2;
	}
	return res;
}

ll power(ll x, ll p) {
	ll res = 1; x %= mod;
	for (; p; p >>= 1, x = (x * x) % mod)
		if (p & 1) res = (res * x) % mod;
	return res;
}