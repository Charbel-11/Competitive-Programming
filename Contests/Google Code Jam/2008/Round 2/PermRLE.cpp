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
		int k; cin >> k;
		string s; cin >> s;
		int m = s.size() / k;

		vector<vector<int>> diff(k, vector<int>(k, 0)), diffEnd(k, vector<int>(k, 0));
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				if (i == j) { continue; }
				for (int r = 0; r < m; r++) {
					int id1 = r * k + i, id2 = r * k + j; 
					if (s[id1] != s[id2]) { diff[i][j]++; }
					if (r < m - 1) {
						id2 += k;
						if (s[id1] != s[id2]) { diffEnd[i][j]++; }
					}
				}
			}
		}

		int ans = 1e6;
		for (int e = 0; e < k; e++) {
			vector<vector<int>> dp((1 << k), vector<int>(k, 1e6));
			dp[1][0] = 1;

			for (int i = 3; i < (1 << k); i += 2) {
				for (int j = 0; j < k; j++) {
					if (!((1 << j) & i)) { continue; }

					int prevS = i ^ (1 << j);
					for (int l = 0; l < k; l++) {
						if (!((1 << l) & prevS)) { continue; }

						if (e == l){ dp[i][j] = min(dp[i][j], dp[prevS][l] + diffEnd[l][j]); }
						else { dp[i][j] = min(dp[i][j], dp[prevS][l] + diff[l][j]); }
					}
				}
			}

			for (int i = 1; i < k; i++) {
				int candidate = dp[(1 << k) - 1][i];
				if (e == i) { candidate += diffEnd[i][0]; }
				else { candidate += diff[i][0]; }
				ans = min(ans, candidate);
			}
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}