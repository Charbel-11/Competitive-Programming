#include <iostream>
#include <string>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll choose[1000][1000];
//A choose B up to 1000C1000
void fillComb() {
	int limit = 1000;	//change if needed
	for (int i = 0; i < limit; i++) { choose[i][i] = 1; choose[i][0] = 1; }
	for (int i = 1; i < limit; i++)
		for (int j = 1; j < i; j++)
			choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % mod;
}


// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	ll res = 1;
	for (; p; p >>= 1, x = (x * x) % mod)
		if (p & 1) res = (res * x) % mod;
	return res;
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
	cin.tie(0); cout.tie(0);
}