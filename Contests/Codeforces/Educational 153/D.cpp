#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
    int n = s.size();

    int num0 = 0, num1 = 0;
    for(auto &c : s){
        num0 += c == '0';
        num1 += c == '1';
    }

    vector dp(n+1, vector(n+1, vector<int>(n * n / 2 + 1, 1e9)));
    dp[0][0][0] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= i; j++){
            for(int k = 0; k <= n*n/2; k++){
                if (j > 0){ dp[i][j][k] = min(dp[i][j][k], dp[i-1][j-1][k] + (s[i-1] != '0')); }
                if (j <= k){ dp[i][j][k] = min(dp[i][j][k], dp[i-1][j][k-j] + (s[i-1] != '1')); }
            }
        }
    }

    cout << dp[n][num0][num0*num1/2]/2 << '\n';
}