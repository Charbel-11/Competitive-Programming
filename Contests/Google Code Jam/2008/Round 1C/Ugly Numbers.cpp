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

ll dp[41][210];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		for (int i = 0; i < 41; i++)
			for (int j = 0; j < 210; j++)
				dp[i][j] = 0;

		dp[0][0] = 1;
		string s; cin >> s;
		int n = s.size();
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < 210; j++) {
				if (dp[i - 1][j] == 0) { continue; }
				int cur = 0;
				for (int k = i; k <= n; k++) {
					cur *= 10; cur += s[k - 1] - '0'; cur %= 210;

					int nxtModP = j + cur; nxtModP %= 210;
					dp[k][nxtModP] += dp[i - 1][j];

					if (i > 1) {
						int nxtModM = 210 + j - cur; nxtModM %= 210;
						dp[k][nxtModM] += dp[i - 1][j];
					}
				}
			}
		}
			
		ll ans = 0;
		for (int j = 0; j < 210; j++) {
			if (j % 2 && j % 3 && j % 5 && j % 7) { continue; }
			ans += dp[n][j];
		}
		cout << "Case #" << qq << ": " << ans << '\n';
	}
}