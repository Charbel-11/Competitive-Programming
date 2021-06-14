#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll dp[3002][3002];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	string s; cin >> s;
	dp[0][0] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			if (s[i - 1] == '>') { dp[i][j] += (dp[i - 1][i - 1] - (j ? dp[i - 1][j - 1] : 0)); dp[i][j] %= mod; }
			else { dp[i][j] += (j ? dp[i - 1][j - 1] : 0); dp[i][j] %= mod; }
			if (j) { dp[i][j] += dp[i][j - 1]; dp[i][j] %= mod; }
		}
	}

	if (dp[n - 1][n - 1] < 0) { dp[n - 1][n - 1] += mod; }
	cout << dp[n - 1][n - 1] << '\n';
}