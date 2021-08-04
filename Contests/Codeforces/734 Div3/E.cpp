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
		int n, k; cin >> n >> k;
		vector<int> a(n); for (auto& x : a) { cin >> x; }
		
		int zeroCnt = 0;
		vector<int> diff(n + 1, 0);
		for (int i = 1; i <= n; i++) {
			diff[i] = i - a[i - 1];
			if (diff[i] == 0) { zeroCnt++; }
		}

		int ans = n + 10;
		if (zeroCnt >= k) { ans = 0; }

		//dp[i][j] = fixed pts we get in first i elements by removing j elements from them
		vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
		for (int i = 1; i <= n; i++) {
			vector<int> freq(n + 1, 0);
			for (int j = i + 1; j <= n; j++) { 
				if (diff[j] >= 0) { freq[diff[j]]++; } 
			}

			for (int j = 1; j <= i; j++) {
				if (diff[j] == 0) { dp[i][0]++; }

				int curFixedPts = freq[j];
				int add = dp[i - 1][j - 1];
				if (i > j) {
					add = max(add, dp[i - 1][j] + (diff[i] == j));
				}
				curFixedPts += add;
				dp[i][j] = add;

				if (curFixedPts >= k) { ans = min(ans, j); }
			}
		}

		if (ans == n + 10) { cout << -1 << '\n'; }
		else { cout << ans << '\n'; }
	}
}