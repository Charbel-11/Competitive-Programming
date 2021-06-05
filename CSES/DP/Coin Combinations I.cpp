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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, x; cin >> n >> x;
	vector<int> coins(n);
	for (auto &x : coins) { cin >> x; }

	vector<int> dp(x + 1, 0);
	for (int i = 0; i < n; i++) {
		if (coins[i] > x) { continue; }
		dp[coins[i]] = 1;
	}

	for (int i = 0; i <= x; i++) {
		for (int j = 0; j < n; j++) {
			int nxt = i + coins[j];
			if (nxt > x) { continue; }
			dp[nxt] += dp[i]; dp[nxt] %= mod;
		}
	}

	cout << dp[x] << '\n';
}