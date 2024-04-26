#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, p; cin >> n >> p;
    vector<pair<int, int>> intervals(n);
    for(auto &curp : intervals){ cin >> curp.first >> curp.second; }
    sort(intervals.begin(), intervals.end());

    vector<pair<int, int>> goodIntervals, badIntervals;
    for(int i = 0; i < n; i++){
        bool good = false;
        for(int j = 0; j < n; j++){
            if (i == j){ continue; }
            if (intervals[i].first < intervals[j].first && intervals[i].second > intervals[j].second){
                good = true; break;
            }
        }
        if (good){ goodIntervals.push_back(intervals[i]); }
        else{ badIntervals.push_back(intervals[i]); }
    }

    n = badIntervals.size();
    vector<vector<int>> dp(p + 1, vector<int>(n, -1e8));
    dp[1][0] = badIntervals[0].second - badIntervals[0].first;
    int R = badIntervals[0].second;
    for(int i = 1; i < n; i++){
        if (R <= badIntervals[i].first){ break; }
        dp[1][i] = R - badIntervals[i].first;
    }

    for(int i = 2; i <= p; i++){
        for(int j = i - 1; j < n; j++){
            for(int k = j; k > i-2; k--){
                if (badIntervals[k].second <= badIntervals[j].first){ break; }
                dp[i][j] = max(dp[i][j], dp[i-1][k-1] + badIntervals[k].second - badIntervals[j].first);
            }
        }
    }

    vector<int> goodLengths;
    for(auto &p : goodIntervals){ goodLengths.push_back(p.second - p.first); }
    sort(goodLengths.rbegin(), goodLengths.rend());
    if (goodLengths.size() > 0) {
        int maxSum = goodLengths[0];
        for (int i = 1; i < p; i++) {
            dp[p][n - 1] = max(dp[p][n - 1], dp[p - i][n - 1] + maxSum);
            if (i < goodLengths.size()){ maxSum += goodLengths[i]; }
            else{ break; }
        }
    }

    cout << dp[p][n-1] << '\n';
}

