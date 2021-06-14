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
	for (int qq = 1; qq <= t; qq++) {
		cout << "Case #" << qq << ": ";

		int n, A, B; cin >> n >> A >> B;
		vector<int> u(n); for (auto& x : u) { cin >> x; }

		vector<vector<ll>> dp(1e5, vector<ll>(n, 0));
		for (int i = 1; i < 1e5; i++) {
			if (i <= n) { dp[i][i - 1] = 1; continue; }
			int nA = i - A, nB = i - B;

			if (nA > 0) {
				for (int j = 0; j < n; j++) { 
					if (dp[i][j] > 1e13) { continue; }
					dp[i][j] += dp[nA][j];
				}
			}
			if (nB > 0) {
				for (int j = 0; j < n; j++) { 
					if (dp[i][j] > 1e13) { continue; }
					dp[i][j] += dp[nB][j];
				}
			}
		}

		int ans = 0;
		for (int i = 1; i < 1e5; i++) {
			vector<ll> cur = dp[i]; bool OK = true;
			for (int j = n - 1; j >= 0; j--) {
				if (u[j] > cur[j]) { OK = false; break; }
				cur[j] -= u[j];

				int nA = j - A, nB = j - B;
				if (nA >= 0) { cur[nA] += cur[j]; }
				if (nB >= 0) { cur[nB] += cur[j]; }
			}
			if (OK) { ans = i; break; }
		}

		if (ans == 0) { cout << "IMPOSSIBLE" << '\n'; }
		else { cout << ans << '\n'; }
	}
}
