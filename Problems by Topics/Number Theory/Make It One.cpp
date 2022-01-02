// https://codeforces.com/contest/1043/problem/F

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
	ll res = 1;
	for (; p; p >>= 1, x = (x * x) % mod)
		if (p & 1) res = (res * x) % mod;
	return res;
}
// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

const int SZ = (int)3e5 + 5;
ll fact[SZ];
void fillFact() {
	fact[0] = 1;
	for (int i = 1; i < SZ; i++) {
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
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	fillFact();
	int n; cin >> n;
	vector<int> freq(SZ, 0);
	for (int i = 0; i < n; i++) {
		int cur; cin >> cur;
		freq[cur]++;
	}

	vector<vector<ll>> dp(8, vector<ll>(SZ, 0));

	int ans = -1;
	for (int i = 1; i < 8; i++) {
		for (int j = SZ - 1; j >= 1; j--) {
			ll cnt = 0;
			for (int k = j; k < SZ; k += j) { cnt += freq[k]; }
			
			dp[i][j] = choose(cnt, i);
			for (int k = 2 * j; k < SZ; k += j) { 
				dp[i][j] = dp[i][j] - dp[i][k] + mod; dp[i][j] %= mod;
			}
		}
		if (dp[i][1] > 0) { ans = i; break; }
	}

	cout << ans << '\n';
}