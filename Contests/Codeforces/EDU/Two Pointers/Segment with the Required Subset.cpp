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

	int n, s; cin >> n >> s;
	vector<int> a(n); for (auto& x : a) { cin >> x; }

	int ans = n + 1;
	vector<int> dp(s + 1, -1);
	for (int i = 0; i < n; i++) {
		dp[0] = i;
		for (int j = s; j >= 0; j--) {
			if (dp[j] == -1 || j + a[i] > s) { continue; }
			dp[j + a[i]] = max(dp[j + a[i]], dp[j]);
		}

		if (dp[s] != -1) { ans = min(ans, i - dp[s] + 1); }
	}

	if (ans == n + 1) { cout << -1 << '\n'; }
	else { cout << ans << '\n'; }
}