#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = 998244353LL;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	if (p == 0) return 1;
	ll w = powe((x*x) % mod, p / 2);
	if (p & 1) w = (w*x) % mod;
	return w;
}

// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

//With mod
ll fact[(int)2e5+1];
void fillFact() {
	fact[0] = 1;
	for (int i = 1; i < 2e5+1; i++) {
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
	int n, m; cin >> n >> m;
	fillFact();
	ll ans = 0;

	for (int i = n - 1; i <= m; i++) {
		ll cur = choose(i - 1, n - 2);
		cur *= powe(2, n - 3ll); cur %= mod;

		ans += cur; ans %= mod;
	}
	ans *= (n - 2); ans %= mod;
	if (ans < 0) { ans += mod; }

	cout << ans << endl;
}