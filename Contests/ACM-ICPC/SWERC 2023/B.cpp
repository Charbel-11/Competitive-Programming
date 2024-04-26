#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1e15;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; ll h; cin >> n >> h;
    vector<ll> x(n); for(auto &xx : x){ cin >> xx; }
    vector<vector<pair<ll, ll>>> dp(n, vector<pair<ll, ll>>(n, {INF, 0}));

    for(int i = 0; i < n; i++){
        dp[i][i] = {0, h};
    }
    for(int i = 0; i < n-1; i++){
        dp[i][i+1] = {2 * h, 0};

        ll diff = x[i+1]-x[i];
        ll numBricks = 2*((diff+1)/2)-1;
        ll height = h-(diff+1)/2;
        if (height >= 0) {
            dp[i][i + 1] = min(dp[i][i+1], {numBricks, height});
        }
    }

    for(int k = 2; k < n; k++){
        for(int i = 0; i + k < n; i++){
            int l = i, r = i+k;
            for(int j = i; j < i+k; j++) {
                ll numBricks = dp[l][j].first + dp[j + 1][r].first;
                if (numBricks > INF) {
                    dp[l][r].first = INF;
                    continue;
                }

                ll h1 = dp[l][j].second, h2 = dp[j + 1][r].second;

                dp[l][r] = min(dp[l][r], {numBricks + h1 + h2, 0});

                ll diff1 = x[j] - x[l], diff2 = x[r] - x[j + 1];
                ll xl = x[l] + (diff1 + 1) / 2, xr = x[r] - (diff2 + 1) / 2;

                ll curH = min(h1, h2);
                if (h1 < h2) { xr -= (h2 - h1); }
                else { xl += (h1 - h2); }
                numBricks += abs(h2-h1);

                if (xl > xr) {
                    numBricks++; curH--;
                    if (curH >= 0) { dp[l][r] = min(dp[l][r], {numBricks, curH}); }
                    continue;
                }

                ll diff = xr - xl;
                ll extraBricks = 2 * ((diff + 1) / 2) - 1;
                ll extraH = (diff + 1) / 2;

                if (curH - extraH >= 0) {
                    dp[l][r] = min(dp[l][r], {numBricks + extraBricks, curH - extraH});
                }
            }
        }
    }

    cout << dp[0][n-1].first + dp[0][n-1].second << '\n';
}