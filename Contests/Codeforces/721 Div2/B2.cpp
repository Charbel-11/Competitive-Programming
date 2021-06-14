#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int dp[502][502][2][2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	for (int z = 0; z < 502; z++)
		for (int d = 0; d < 502; d++)
			for (int m = 1; m >= 0; m--)
				for (int r = 1; r >= 0; r--)
					dp[z][d][m][r] = 20000;

	dp[0][0][0][0] = dp[0][0][0][1] = 0;
	for (int z = 0; z < 502; z++) {
		for (int d = 0; d < 502; d++) {
			for (int m = 0; m < 2; m++) {
				for (int r = 1; r >= 0; r--) {
					if (m) { dp[z][d][m][r] = min(dp[z][d][m][r], 1 - dp[z][d][0][0]); }
					if (!r && d) { dp[z][d][m][r] = min(dp[z][d][m][r], -dp[z][d][m][1]); }
					
					if (z && d < 501) { dp[z][d][m][r] = min(dp[z][d][m][r], 1 - dp[z - 1][d + 1][m][0]); }
					if (d) { dp[z][d][m][r] = min(dp[z][d][m][r], 1 - dp[z][d - 1][m][0]); }
				}
			}
		}
	}

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		string s; cin >> s;
		int zeros = 0, diff = 0, mid0 = 0;
		
		for (int i = 0; i < n / 2; i++) {
			if (s[i] == s[n - i - 1] && s[i] == '0') { zeros++; }
			else if (s[i] != s[n - i - 1]) { diff++; }
		}
		if (n % 2 && s[n / 2] == '0') { mid0 = 1; }

		if (dp[zeros][diff][mid0][0] == 0) { cout << "DRAW" << '\n'; }
		else if (dp[zeros][diff][mid0][0] < 0) { cout << "ALICE" << '\n'; }
		else if (dp[zeros][diff][mid0][0] > 0) { cout << "BOB" << '\n'; }
	}
}
