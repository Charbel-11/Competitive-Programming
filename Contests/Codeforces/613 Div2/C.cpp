#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (ll)(a / gcd(a, b)) * b; }

int main() {
	ll x; cin >> x;

	if (x == 1) { cout << 1 << " " << 1 << endl; return 0; }

	ll a = 1, b = x;
	for (ll d = 2ll; d*d <= x; d++) {
		if (x%d == 0) {
			ll d2 = x / d;
			if (lcm(d, d2) == x) {
				if (max(a, b) > max(d, d2)) {
					a = d; b = x / d;
				}
			}
		}
	}

	cout << a << " " << b << endl;
}