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
	if (p == 0) return 1;
	ll w = powe((x * x) % mod, p / 2);
	if (p & 1) w = (w * x) % mod;
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
	int h, w, n; cin >> h >> w >> n;
	vector<pair<int, int>> blocks;
	for (int i = 0; i < n; i++) {
		int r, c; cin >> r >> c; r--; c--;
		blocks.push_back({ r,c });
	}
	sort(blocks.begin(), blocks.end());
	blocks.push_back({ h - 1,w - 1 });

	n++; vector<ll> dp(n, 0);
	for (int i = 0; i < n; i++) {
		dp[i] = choose(blocks[i].first + blocks[i].second, blocks[i].first);
		for (int j = 0; j < i; j++) {
			ll dx = blocks[i].first - blocks[j].first, dy = blocks[i].second - blocks[j].second;
			ll rem = dp[j] * (choose(dx + dy, dx)); rem %= mod;
			dp[i] -= rem; dp[i] %= mod;
		}
		if (dp[i] < 0) { dp[i] += mod; }
	}

	cout << dp[n - 1] << '\n';
}