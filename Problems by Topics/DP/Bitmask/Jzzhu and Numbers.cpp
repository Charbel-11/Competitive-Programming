// https://codeforces.com/contest/449/problem/D

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

	int n; cin >> n;
	vector<int> a(n), dp(M, 0); 
	for (auto& x : a) { cin >> x; dp[x]++; }

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