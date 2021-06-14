#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<ll> a(n); for (auto& x : a) { cin >> x; }
		vector<ll> dp(n + 1, 0); ll ans = 0;
		for (int i = n - 1; i >= 0; i--) {
			dp[i] = a[i];
			ll nxt = i + a[i];
			if (nxt > n) { continue; }
			dp[i] += dp[nxt];
		}
		for (int i = 0; i < n; i++) { ans = max(ans, dp[i]); }
		cout << ans << '\n';
	}
}