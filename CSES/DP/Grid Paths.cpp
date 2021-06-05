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
const ll mod = (ll)1e9 + 7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<string> grid(n);
	for (auto &s : grid) { cin >> s; }

	vector<vector<int>> dp(n, vector<int>(n, 0)); 
	for (int i = 0; i < n; i++) { 
		if (grid[i][0] == '*') { break; }
		dp[i][0] = 1;
	}
	for (int i = 0; i < n; i++) {
		if (grid[0][i] == '*') { break; }
		dp[0][i] = 1;
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			if (grid[i][j] == '*') { continue; }
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			dp[i][j] %= mod;
		}
	}

	cout << dp[n - 1][n - 1] << '\n';
}