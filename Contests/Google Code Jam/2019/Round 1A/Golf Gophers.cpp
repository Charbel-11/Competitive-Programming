#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

// a*x - b*y = return value = GCD(a,b). x,y >= 0
ll egcd(ll a, ll b, ll &x, ll &y) { // watch out: MINUS B*Y
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	} 
	ll d = egcd(b, a%b, y, x);
	y = a - x * (a / b) - y;
	x = b - x;
	return d;
}

// modular inverse (works for any modulus p)
ll inverse(ll a, ll p) {
	ll x, y;
	egcd(a%p + p, p, x, y);
	return x % p;
}

// x = a (mod m)
// x = b (mod n)
// returns res such that x = res (mod lcm(m,n))
// no such res => throws 0 (so you must wrap it in try { ... } catch (int _) { ... }
ll CRT(ll a, ll m, ll b, ll n) {
	b = (b + n - (a%n)) % n;
	ll d = gcd(m, n);
	if (b%d != 0) throw 0;
	ll old_m = m;
	m /= d; b /= d; n /= d;
	return ((b*inverse(m, n)) % n)*old_m + a;
}

int main() {	
	int T; cin >> T;
	int N, M; cin >> N >> M;

	for (int z = 1; z <= T; z++) {
		ll ans = 0, prevUsed = -1;

		int queries[] = { 4,9,5,7,11,13,17 };

		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 18; j++) {
				cout << queries[i];
				if (j == 17) { cout << endl; }
				else { cout << " "; }
			}
			cout.flush();

			ll cur = 0;
			for (int j = 0; j < 18; j++) {
				int temp; cin >> temp;
				cur += temp;
			}

			if (prevUsed == -1) { ans = cur; prevUsed = queries[0]; continue; }

			ans = CRT(ans, prevUsed, cur, queries[i]);
			prevUsed *= queries[i];
		}

		cout << ans << endl;
		cout.flush();
		int verdict; cin >> verdict;
		if (verdict == -1) { break; }
	}
}