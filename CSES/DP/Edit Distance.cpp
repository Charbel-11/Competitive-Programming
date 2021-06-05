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

int dp[5002][5002];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s, t; cin >> s >> t;
	int n = (int)s.size(), m = (int)t.size();

	for (int i = 0; i < n; i++) { dp[i][m] = n - i; }
	for (int j = 0; j < m; j++) { dp[n][j] = m - j; }

	for (int i = n - 1; i >= 0; i--) {
		for (int j = m - 1; j >= 0; j--) {
			dp[i][j] = n * m + 2;
			if (s[i] == t[j]) { dp[i][j] = dp[i + 1][j + 1]; continue; }
			dp[i][j] = min(dp[i][j], 1 + dp[i + 1][j + 1]);
			dp[i][j] = min(dp[i][j], 1 + dp[i + 1][j]);	
			dp[i][j] = min(dp[i][j], 1 + dp[i][j + 1]);
		}
	}

	cout << dp[0][0] << '\n';
}