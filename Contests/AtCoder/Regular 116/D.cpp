#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
int n, m;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	if (p == 0) return 1;
	ll w = powe((x * x) % mod, p / 2);
	if (p & 1) w = (w * x) % mod;
	return w;
}
// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

const int SZ = (int)2e4 + 1;
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
	cin >> n >> m;
	if (m & 1 || n == 1) { cout << 0 << '\n'; return 0; }

	vector<ll> dp(m + 1, 0); dp[0] = 1;
	for (int i = 2; i <= m; i += 2) {
		for (int cnt = 0; cnt <= n && i >= cnt; cnt += 2) {
			dp[i] += (dp[(i - cnt) / 2] * choose(n, cnt)) % mod;
			dp[i] %= mod;
		}
	}

	cout << dp[m] << '\n';
}