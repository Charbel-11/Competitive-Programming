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

const int SZ = (int)1e6 + 1;
ll fact[SZ];
void fillFact() {
	fact[0] = 1;
	for (int i = 1; i < SZ; i++) {
		fact[i] = fact[i - 1] * i;
		fact[i] %= mod;
	}
}

//Handles nCk with mod for large n,k; uses mult inverse (Assumes mod is prime, otherwise use egcd)
//Be sure to fillFact() before using this
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
	int n, k; cin >> n >> k;
	
	ll ans = 0;
	for (int i = 0; i <= k; i++) {
		ll cur = choose(k, i) * powe(k - i, n); cur %= mod;
		if (i % 2 == 1) {
			ans -= cur; ans %= mod;
			if (ans < 0) { ans += mod; }
		}
		else {
			ans += cur; ans %= mod;
		}
	}

	cout << ans << '\n';
}