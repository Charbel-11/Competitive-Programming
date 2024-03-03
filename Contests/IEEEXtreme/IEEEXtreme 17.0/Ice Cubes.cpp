#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for(int T = 1; T <= t; T++){
		int n, m, k, b; cin >> n >> m >> k >> b;
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k, -1)));
        vector<vector<int>> grid(n, vector<int>(m));
        for(auto &v : grid){
            for(auto &x : v){
                cin >> x;
            }
        }

        if (grid[0][0] >= b){ dp[0][0][0] = grid[0][0]; }
        else if (k > 1) { dp[0][0][1] = grid[0][0]; }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if (i == 0 && j == 0){ continue; }
                if (grid[i][j] >= b) {
                    for (int l = 0; l < k; l++) {
                        if (i && dp[i - 1][j][l] != -1) dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][l] + grid[i][j]);
                        if (j && dp[i][j - 1][l] != -1) dp[i][j][0] = max(dp[i][j][0], dp[i][j - 1][l] + grid[i][j]);
                    }
                }
                else {
                    for (int l = 1; l < k; l++) {
                        if (i && dp[i - 1][j][l - 1] != -1)
                            dp[i][j][l] = max(dp[i][j][l], dp[i - 1][j][l - 1] + grid[i][j]);
                        if (j && dp[i][j - 1][l - 1] != -1)
                            dp[i][j][l] = max(dp[i][j][l], dp[i][j - 1][l - 1] + grid[i][j]);
                    }
                }
            }
        }

        int ans = *max_element(dp[n-1][m-1].begin(), dp[n-1][m-1].end());
        cout << "Case " << T << ": ";
        if (ans == -1){ cout << "IMPOSSIBLE\n"; }
        else { cout << ans << '\n'; }
	}
}

