#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int m, x, y, K; cin >> m >> x >> y >> K;
		vector<int> period(m * x);
		for (auto& xx : period) { cin >> xx; }

		vector<vector<vector<int>>> dp(m * x, vector<vector<int>>(y + 1, vector<int>(K + 1, INT_MIN)));
		dp[0][0][0] = 0; dp[0][1][1] = period[0];
		for (int i = 0; i < m * x; i++) {
			int curPeriod = i % x;
			for (int j = 0; j <= y; j++) {
				for (int k = 0; k <= K; k++) {
					if (j > curPeriod + 1) { continue; }
					if (!j && k) { continue; }

					if (curPeriod) {
						if (i && j && k) {
							dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][k - 1] + period[i]);
						}
						if (!k) {
							for (int kk = 0; kk <= K; kk++) {
								dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][kk]);
							}
						}
						if (!j) { dp[i][0][k] = max(dp[i][0][k], dp[i - 1][0][k]); }
					}
					else {
						if (i) {
							dp[i][0][0] = max(dp[i][0][0], dp[i - 1][y][0]);
							for (int k = 1; k <= K; k++) {
								dp[i][1][k] = max(dp[i][1][k], dp[i - 1][y][k - 1] + period[i]);
								dp[i][0][0] = max(dp[i][0][0], dp[i - 1][y][k]);
							}
						}
					}
				}
			}
		}

		int ans = -1;
		for (int k = 0; k <= K; k++) { ans = max(ans, dp[m * x - 1][y][k]); }
		if (ans == -1) { cout << "IMPOSSIBLE" << '\n'; }
		else { cout << ans << '\n'; }
	}
}