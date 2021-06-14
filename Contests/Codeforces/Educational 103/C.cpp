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
		vector<ll> c(n); for (auto& x : c) { cin >> x; };
		vector<ll> a(n); for (auto& x : a) { cin >> x; };
		vector<ll> b(n); for (auto& x : b) { cin >> x; };

		vector<ll> dp(n, 0);
		dp[0] = c[0] - 1;
		for (int i = 1; i < n; i++) {
			if (a[i] == b[i]) { dp[i] = c[i] + 1; continue; }
			if (a[i] > b[i]) { swap(a[i], b[i]); }
			ll curC = c[i] + 1;
			ll c1 = dp[i - 1] - (c[i - 1] - 1) + (a[i] - 1) + c[i - 1] - b[i];
			ll c2 = b[i] - a[i];
			if (i == 1) { c1 = 0; }
			dp[i] = curC + max(c1, c2);
		}

		ll ans = 0;
		for (int i = 1; i < n; i++) { ans = max(ans, dp[i]); }
		cout << ans << '\n';
	}
}