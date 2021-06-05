#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	if (p == 0) return 1;
	ll w = powe((x*x) % mod, p / 2);
	if (p & 1) w = (w*x) % mod;
	return w;
}

// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

//With mod; FIX SIZE IF NEEDED
ll fact[(int)1e6 + 2];
void fillFact() {
	fact[0] = 1;
	for (int i = 1; i < 1e6 + 2; i++) {
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
	fillFact();

	int n; cin >> n;
	while (n--) {
		int a, b; cin >> a >> b;
		cout << choose(a, b) << '\n';
	}
}