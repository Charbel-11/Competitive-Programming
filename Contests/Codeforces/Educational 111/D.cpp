#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	if (p == 0) return 1;
	ll w = powe((x * x) % mod, p / 2);
	if (p & 1) w = (w * x) % mod;
	return w;
}
// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

const int SZ = (int)2e5 + 1;
ll fact[SZ];
void fillFact() {
	fact[0] = 1;
	for (int i = 1; i < SZ; i++) {
		fact[i] = fact[i - 1] * i;
		fact[i] %= mod;
	}
}

ll choose(ll n, ll k) {
	if (k > n) { return 0; }
	ll num = fact[n], denom = fact[k];
	denom *= fact[n - k]; denom %= mod;

	ll multInv = modinv(denom);
	num *= multInv; num %= mod;
	return num;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	fillFact();
	int t; cin >> t;
	while (t--) {
		int n; ll l, r; cin >> n >> l >> r;
		ll ans = 0;
		
		ll maxSafe = max(0ll, min(1 - l, r - n));
		if (maxSafe >= 1) {
			ll mult = choose(n, n / 2);
			if (n & 1) { mult += choose(n, n / 2 + 1); mult %= mod; }
			ans += maxSafe * mult; ans %= mod;
		}

		int i1 = 1, i2 = n;
		ll k = maxSafe;
		while (true) {
			k++;

			while (i1 - k < l) { i1++; }
			while (i2 + k > r) { i2--; }
			if (i1 > i2 + 1) { break; }

			int fixedM = i1 - 1, fixedP = n - i2;
			if (fixedP > (n + 1) / 2 || fixedM > (n + 1) / 2) { break; }

			int rem = n - fixedP - fixedM;
			ll mult = choose(rem, n / 2 - fixedM);
			if (n & 1) { mult += choose(rem, n / 2 + 1 - fixedM); mult %= mod; }
			
			ans += mult; ans %= mod;
		}

		cout << ans << '\n';
	}
}