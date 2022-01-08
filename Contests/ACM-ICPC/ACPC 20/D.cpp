#include <iostream>
#include <string>
#include <map>
#include <set>
#include <complex>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll mod = 132120577;
const ll root = 5;
const ll invRoot = 52848231;
const int modPow = 21;
const ll oddFactor = 63;

ll power(ll x, ll n) {
	ll res = 1;
	for (; n; n >>= 1, x = (x * x) % mod) {
		if (n & 1) { res = (res * x) % mod; }
	}
	return res;
}
ll modInv(ll x) { return power(x, mod - 2); }

void NTT(vector<ll>& a, const ll& curRoot) {
	int n = (int)a.size();
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
	freopen("differences.in", "r", stdin);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int M = n;

        vector<ll> nums(n, 0);
        for (int i = 0; i < n; i++) {
            int x; ll f; cin >> x >> f; x--;
            nums[x] += f; nums[x] %= mod;
        }

		vector<ll> a = nums, b = nums;
		reverse(b.begin(), b.end());
		auto c = polyModMult(a, b);

		vector<ll> ans(n + 1, 0);
		for (int i = n - 1; i >= 0; i--) {
			ans[(n - 1) - i] = c[i];
		}
		
		for (int i = 1; i <= n; i++) {
			ans[i] += ans[i - 1];
			ans[i] %= mod;
		}

		int q; cin >> q;
		while (q--) {
			int l, r; cin >> l >> r;
			cout << (ans[r] - ans[l - 1] + mod) % mod << '\n';
		}
    }
}