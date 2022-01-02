// https://www.hackerrank.com/contests/w16/challenges/vim-war

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <bitset>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int M = (1 << 20);

ll power(ll x, ll k) {
	ll ans = 1;
	for (; k; x = (x * x) % mod, k /= 2) {
		if (k & 1) { ans *= x; ans %= mod; }
	}
	return ans;
}

int countBits(int x) {
	int ans = 0;
	while (x) { ans++; x = x & (x - 1); }
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<int> a(n + 1), dp(M, 0);
	for (auto& x : a) {
		bitset<20> cur; 
		cin >> cur; cur.flip();
		x = cur.to_ulong();
	}

	int want = a[n];
	for (int i = 0; i < n; i++) {
		if ((a[i] | want) > a[i]) { continue; }
		dp[a[i] ^ want]++;
	}

	for (int k = 0; k < 20; k++) {
		for (int mask = 0; mask < M; mask++) {
			if (!((1 << k) & mask)) { dp[mask] += dp[mask ^ (1 << k)]; }
		}
	}

	ll ans = 0;
	for (int x = 0; x < M; x++) {
		int parity = (countBits(x) % 2 ? -1 : 1);
		ans += parity * (power(2, dp[x]) - 1); ans %= mod;
	}
	if (ans < 0) { ans += mod; }
	cout << ans << '\n';
}