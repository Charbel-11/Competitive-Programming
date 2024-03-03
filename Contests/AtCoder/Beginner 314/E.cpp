#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const double INF = 1e18;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
    vector<int> c(n); vector<vector<int>> S;
    for(int i = 0; i < n; i++){
        cin >> c[i];
        int curP; cin >> curP;
        vector<int> curS(curP);
        for(auto &x : curS){ cin >> x; }
        S.push_back(curS);
    }

    vector<ld> dp(m+1, INF); dp[0] = 0;
    for (int j = 1; j <= m; j++) {
        for (int i = 0; i < n; i++) {
            int numWays = 0;
            ld curVal = 0;
            for (auto &s: S[i]) {
                if (s == 0) { continue; }
                numWays++;
                int prevJ = max(j - s, 0);
                curVal += dp[prevJ];
            }
            ld curP = 1.0 / (ld) numWays;
            ld fact = (ld) S[i].size() * curP;
            curVal *= curP;
            curVal += fact * c[i];
            dp[j] = min(dp[j], curVal);
        }
    }

    cout << setprecision(7) << fixed << dp[m] << '\n';
}