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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
	vector<ll> dp(26, 0);
	ll ans = 0, S = 0;

	for (auto& c : s) {
		int idx = c - 'a';
		ll add = (S + 1 - dp[idx] + mod) % mod;

		ans += add; ans %= mod;
		dp[idx] += add; dp[idx] %= mod;
		S += add; S %= mod;
	}

	cout << ans << '\n';
}