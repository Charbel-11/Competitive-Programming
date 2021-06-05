#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = (ll)1e9 + 7;

const int M = 126000;
ll dp[M + 1];

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	if (p == 0) return 1;
	ll w = powe((x*x) % mod, p / 2);
	if (p & 1) w = (w*x) % mod;
	return w;
}

// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	ll sum = n * (n + 1) / 2;
	if (sum % 2) { cout << 0 << '\n'; return 0; }

	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = M - i; j >= 0; j--) {
			int nxt = j + i;
			dp[nxt] += dp[j];
			dp[nxt] %= mod;
		}
	}

	cout << (dp[sum / 2] * modinv(2)) % mod << '\n';
}