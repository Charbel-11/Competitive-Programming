#include <bits/stdc++.h>
using namespace std;

int n, w;
bool check(vector<vector<int>>& dp, int h, const vector<int>& len, const vector<vector<int>>& mx){
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= i; j++) {
            dp[i][j] = w + 1;
        }
    }
    dp[0][0] = 0;

    vector<int> minDPs(n + 1, w + 1); minDPs[0] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= min(i, h); j++){
            if (j == 1){ dp[i][j] = minDPs[i-1] + len[i-1] + (i != 1); }
            else{
                int diffLen = mx[i-j+1][i] - mx[i-j+1][i-1];
                dp[i][j] = dp[i-1][j-1] + diffLen;
            }
            minDPs[i] = min(minDPs[i], dp[i][j]);
        }
    }
    return *min_element(dp[n].begin(), dp[n].end()) <= w;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> w;
    vector<string> names(n); vector<int> len(n);
    for(int i = 0; i < n; i++){
        cin >> names[i];
        len[i] = names[i].size();
    }

    vector<vector<int>> mx(n + 1, vector<int>(n+1, 0));
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j++)
            mx[i][j] = max(mx[i][j-1], len[j-1]);

    int l = 1, r = n;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, w + 1));
    while(l < r){
        int mid = (l + r) / 2;
        if (check(dp, mid, len, mx)){ r = mid; }
        else{ l = mid + 1; }
    }
    check(dp, l, len, mx);

    vector<vector<string>> columns;
    int i = n, idx = n-1, j;
    while(i > 0){
        int minWidth = *min_element(dp[i].begin(), dp[i].end());
        for(j = 1; j <= i; j++){
            if (dp[i][j] == minWidth){ break;}
        }
        vector<string> curCol;
        for(int k = 0; k < j; k++){
            curCol.push_back(names[idx--]);
        }
        columns.push_back(curCol); i -= j;
    }

    vector<int> widths(columns.size(), 0);
    reverse(columns.begin(), columns.end());
    cout << l << " " << columns.size() << '\n';
    for(int i = 0; i < columns.size(); i++){
        widths[i] = columns[i][0].size();
        for(int j = 1; j < columns[i].size(); j++){
            widths[i] = max(widths[i], (int)columns[i][j].size());
        }

        for(int j = 0; j < columns[i].size(); j++) {
            while (columns[i][j].size() < widths[i]) {
                columns[i][j].push_back(' ');
            }
        }
        reverse(columns[i].begin(), columns[i].end());
    }

    for(auto &x : widths){ cout << x << ' '; } cout << '\n';
    for(int i = 0; i < l; i++){
        for(int j = 0; j < columns.size(); j++){
            if (columns[j].size() > i){ cout << columns[j][i] << ' '; }
            else{ cout << string(widths[j] + 1, ' '); }
        }
        cout << '\n';
    }
}