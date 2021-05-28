//https://codeforces.com/contest/1332/problem/E

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = 998244353ll;

ll egcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}

	ll d = egcd(b, a%b, y, x);
	y = a - x * (a / b) - y;
	x = b - x;
	return d;
}
ll inverse(ll a, ll p=mod) {
	ll x, y;
	egcd(a%p + p, p, x, y);
	return x % p;
}

ll power(ll x, ll p) {
	if (p == 0) { return 1ll; }
	x %= mod; 
	ll temp = power(x, p / 2) % mod;
	temp *= temp; temp %= mod;
	if (p & 1) { temp *= x; temp %= mod; }
	return temp;
}

int main() {
	ll n, m, L, R; cin >> n >> m >> L >> R;

	if (n*m % 2) {
		cout << power(R - L + 1, n*m) << endl;
		return 0;
	}
	
	ll E = (R - L) / 2 + 1;
	ll O = R - L + 1 - E;

	cout << ((power(O + E, n*m) + power(abs(O - E), n*m)) * inverse(2))%mod << endl;
}