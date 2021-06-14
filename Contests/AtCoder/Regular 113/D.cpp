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

ll power(ll x, ll p) {
	ll res = 1; x %= mod;
	for (; p; p >>= 1, x = (x * x) % mod)
		if (p & 1) res = (res * x) % mod;
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m, k; cin >> n >> m >> k;
	if (n == m && n == 1) { cout << k << '\n'; return 0; }
	if (m == 1) { cout << power(k, n) << '\n'; return 0; }
	if (n == 1) { cout << power(k, m) << '\n'; return 0; }

	ll ans = 0;
	for (int max1 = 1; max1 <= k; max1++) {
		ll numSeq = power(max1, n) - power(max1 - 1, n) + mod; numSeq %= mod;
		int dif = k - max1 + 1;
		ll numSeq2 = power(dif, m);

		ans += (numSeq * numSeq2) % mod;
		ans %= mod;
	}

	cout << ans << '\n';
}