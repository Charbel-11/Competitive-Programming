// https://judge.yosupo.jp/problem/convolution_mod

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
const ll root = 3;
const ll invRoot = 332748118;
const int modPow = 23;
const ll oddFactor = 119;

ll power(ll x, ll n) {
	ll res = 1;
	for (; n; n >>= 1, x = (x * x) % mod) {
		if (n & 1) res = (res * x) % mod;
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
	return move(A);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<ll> a(n), b(m);
	for (auto& x : a) { cin >> x; }
	for (auto& x : b) { cin >> x; }

	auto c = polyModMult(a, b);
	for (auto& x : c) { cout << x << ' '; }
}