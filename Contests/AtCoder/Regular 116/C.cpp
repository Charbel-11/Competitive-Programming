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
const int SZ = (int)3e5;
int spf[SZ]; //Smallest Prime Factor

void buildSieve() {
	vector<int> primes; spf[0] = spf[1] = 1;
	for (int i = 2; i < SZ; i++) {
		if (spf[i] == 0) { primes.push_back(i);	spf[i] = i; }
		for (int j = 0; j < int(primes.size()) && primes[j] <= spf[i] && i * primes[j] < SZ; j++)
			spf[i * primes[j]] = primes[j];
	}
}

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	if (p == 0) return 1;
	ll w = powe((x * x) % mod, p / 2);
	if (p & 1) w = (w * x) % mod;
	return w;
}
// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

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

//Prime factorization
vector<pair<int, int>> getDivisors(int x) {
	vector<pair<int, int>> v;
	while (x > 1) {
		int d = spf[x], cnt = 0;
		while (x % d == 0) { x /= d; cnt++; }
		v.push_back({ d, cnt });
	}
	return move(v);
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	fillFact(); buildSieve();
	int n, m; cin >> n >> m;
	ll ans = 0;

	for (int i = 1; i <= m; i++){
		auto v = getDivisors(i);
		ll cur = 1;
		for (auto& d : v) {
			cur *= choose(d.second + n - 1, n - 1); cur %= mod;
		}
		ans += cur; ans %= mod;
	}

	cout << ans << '\n';
}