#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int h, w, n; cin >> h >> w >> n;
    vector<vector<bool>> isHole(h, vector<bool>(w, 0));
    for(int i = 0; i < n; i++){
        int u, v; cin >> u >> v; u--; v--;
        isHole[u][v] = true;
    }

    vector<vector<int>> dp(h, vector<int>(w, 0));
    vector<vector<int>> holeLeft(h, vector<int>(w, -1));
    vector<vector<int>> holeTop(h, vector<int>(w, -1));

    ll ans = 0;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if (isHole[i][j]){ holeLeft[i][j] = j; holeTop[i][j] = i; }
            else{
                int curWays = 1;
                if (i > 0 && j > 0){ curWays += dp[i-1][j-1]; }
                if (i > 0){ holeTop[i][j] = holeTop[i-1][j]; }
                if (j > 0){ holeLeft[i][j] = holeLeft[i][j-1]; }

                curWays = min({curWays, i - holeTop[i][j], j - holeLeft[i][j]});

                dp[i][j] = curWays;
                ans += curWays;
            }
        }
    }

    cout << ans << '\n';
}