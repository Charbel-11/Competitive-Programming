#include <iostream>
#include <string>
#include <map>
#include <climits>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

// a*x - b*y = return value = GCD(a,b). x,y >= 0
ll egcd(ll a, ll b, ll& x, ll& y) { // MINUS B*Y
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}

	ll d = egcd(b, a % b, y, x);
	y = a - x * (a / b) - y;
	x = b - x;
	return d;
}
// modular inverse; works for any mod p (coprime with a)
ll inverse(ll a, ll p) {
	ll x, y;
	egcd(a % p + p, p, x, y);
	return x % p;
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
// solves the system of congruences:
// x = a (mod m)
// x = b (mod n)
// returns res such that x = res (mod lcm(m,n))
// no such res => return -1
ll CRT(ll a, ll m, ll b, ll n) {
	b = (b + n - (a % n)) % n;
	ll d = gcd(m, n);
	if (b % d != 0) return -1;

	ll oldM = m;
	m /= d; b /= d; n /= d;
	return ((b * inverse(m, n)) % n) * oldM + a;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		ll X, Y, P, Q; cin >> X >> Y >> P >> Q;
		ll ans = LLONG_MAX;
		for (int i = X; i < X + Y; i++) {
			for (int j = P; j < P + Q; j++) {
				ll curT = CRT(i, 2 * (X + Y), j, P+Q);
				if (curT == -1) { continue; }
				ans = min(ans, curT);
			}
		}
		if (ans == LLONG_MAX) { cout << "infinity" << '\n'; }
		else { cout << ans << '\n'; }
	}
}