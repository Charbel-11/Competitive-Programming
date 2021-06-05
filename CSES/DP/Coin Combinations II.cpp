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

	for (int j = 0; j < n; j++) {
		if (coins[j] > x) { continue; }
		dp[coins[j]]++;
		for (int i = 1; i <= x; i++) {
			int nxt = i + coins[j];
			if (nxt > x) { break; }
			dp[nxt] += dp[i]; dp[nxt] %= mod;
		}
	}

	cout << dp[x] << '\n';
}