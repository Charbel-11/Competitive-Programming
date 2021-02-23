#include <iostream>
#include <string>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll comb[1000][1000];

//A choose B up to 1000C1000
void fillComb() {
	int limit = 1000;	//change if needed
	for (int i = 0; i < limit; i++) { comb[i][i] = 1; comb[i][0] = 1; }

	for (int i = 1; i < limit; i++)
		for (int j = 1; j < i; j++)
			comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
}


// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	if (p == 0) return 1;
	ll w = powe((x*x) % mod, p / 2);
	if (p & 1) w = (w*x) % mod;
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

//Handles nCk for large n,k
//Be sure to fillFact() before using this
//nCk with mod, uses mult inverse
//Assumes mod is prime, otherwise use egcd
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
	cin.tie(0); cout.tie(0);
}