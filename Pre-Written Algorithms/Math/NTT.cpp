#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 132120577;
const ll root = 5;
const ll invRoot = 52848231;
const int modPow = 21;
const ll oddFactor = 63;

/*
MOD = oddFactor x 2^modPow + 1

Precomputed Constants
MOD = 998244353    root = 3    invRoot = 332748118    modPow = 23    oddFactor = 119
MOD = 132120577    root = 5    invRoot = 52848231     modPow = 21    oddFactor = 63
MOD = 7340033      root = 3    invRoot = 2446678      modPow = 20    oddFactor = 7
MOD = 786433       root = 10   invRoot = 235930       modPow = 18    oddFactor = 3;
*/

void generateConstants(const ll& MOD) {
	auto isPrimitveRoot = [&](ll x) {
		ll cur = x, N = 1;
		while (++N != MOD - 1) {
			cur = (cur * x) % MOD;
			if (cur == 1) { return false; }
		}
		return true;
	};

	int r = 2; while (!isPrimitveRoot(r)) { r++; }
	int p = 0; ll cur = MOD - 1, rInv = modInv(r);
	while ((cur & 1) == 0) { p++; cur >>= 1; }

	cout << "Prime: " << MOD << '\n';
	cout << "Primitive Root: " << r << '\n';
	cout << "Inverse of Primitive Root: " << rInv << '\n';
	cout << "Highest Power of 2 in (Prime-1): " << p << ' ' << (1ll << p) << '\n';
	cout << "Highest Odd factor of (Prime-1): " << (MOD - 1) / (1ll << p) << '\n';
}

ll power(ll x, ll n) {
	ll res = 1;
	for (; n; n >>= 1, x = (x * x) % mod) {
		if (n & 1) { res = (res * x) % mod; }
	}
	return res;
}

// Assumes mod is prime
ll modInv(ll x) { return power(x, mod - 2); }

void NTT(vector<ll>& a, const ll& curRoot) {
	int n = (int)a.size(); //Assumes n is a power of 2
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) { j ^= bit; }
		if (i < (j ^= bit)) { swap(a[i], a[j]); }
	}

	for (int len = 2; len <= n; len <<= 1) {
		ll Wn = curRoot;
		for (int i = len; i < n; i <<= 1) { Wn = (Wn * Wn) % mod; }

		for (int i = 0; i < n; i += len) {
			ll W = 1;
			for (int j = 0; j < (len >> 1); j++, W = (W * Wn) % mod) {
				ll even = a[i + j], odd = (W * a[i + j + (len >> 1)]) % mod;
				a[i + j] = even + odd < mod ? even + odd : even + odd - mod;
				a[i + j + (len >> 1)] = even - odd >= 0 ? even - odd : even - odd + mod;
			}
		}
	}
}

vector<ll> polyModMult(vector<ll>& a, vector<ll>& b) {
	vector<ll> A(a.begin(), a.end()), B(b.begin(), b.end());
	int N = (int)a.size(), M = (int)b.size();
	int n = 1, logN = 0;
	while (n < (N + M - 1)) { n <<= 1; logN++; }
	A.resize(n, 0); B.resize(n, 0);

	//Getting roots with cycle exactly n
	ll normFactor = oddFactor * power(2, modPow - logN);
	ll curRoot = power(root, normFactor);
	ll curInvRoot = power(invRoot, normFactor);

	NTT(A, curRoot); NTT(B, curRoot);
	for (int i = 0; i < n; i++) { A[i] = (A[i] * B[i]) % mod; }

	NTT(A, curInvRoot);
	ll invN = modInv(n);
	for (auto& x : A) { x = (x * invN) % mod; }

	while (A.size() > N + M - 1) { A.pop_back(); }
	return A;
}
