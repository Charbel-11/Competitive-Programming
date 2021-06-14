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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> a(n); for (auto &x : a) { cin >> x; }
		vector<vector<int>> dp(n + 2, vector<int>(2, INT_MAX));
		a.push_back(0);

		dp[n][1] = dp[n][0] = dp[n+1][0] = dp[n+1][1] = 0;
		for (int i = n - 1; i >= 0; i--) {
			for (int b = 0; b < 2; b++) {
				if (!b) { dp[i][b] = min(dp[i + 1][!b], dp[i + 2][!b]); continue; }
				
				int c1 = a[i] == 1;
				int c2 = c1 + (a[i + 1] == 1);
				dp[i][b] = min(c1 + dp[i + 1][!b], c2 + dp[i + 2][!b]);
			}
		}

		cout << dp[0][1] << '\n';
	}
}