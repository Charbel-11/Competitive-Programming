#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll dp[19][10][2][2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string a, b; cin >> a >> b;
	reverse(b.begin(), b.end());
	b.push_back('0' - 1);
	reverse(b.begin(), b.end());

	reverse(a.begin(), a.end());
	while (a.size() < b.size()) { a.push_back('0' - 1); }
	reverse(a.begin(), a.end());
	int n = a.size();

	dp[0][0][1][1] = 1;
	for (int i = 1; i < n; i++) {
		int curA = a[i] - '0', curB = b[i] - '0';
		int prevA = a[i - 1] - '0', prevB = b[i - 1] - '0';

		if (curA == curB && prevA == prevB && (curA != prevA || curA < 0)) { 
			dp[i][max(0, curA)][1][1] += dp[i - 1][max(0, prevA)][1][1];
		}
		if (curA != prevA || curA < 0) {
			dp[i][max(0, curA)][1][0] += dp[i - 1][max(0, prevA)][1][0];
			if (curA < curB) { dp[i][max(0, curA)][1][0] += dp[i - 1][max(0, prevA)][1][1]; }
		}
		if (curB != prevB) {
			dp[i][curB][0][1] += dp[i - 1][max(0, prevB)][0][1];
			if (curA < curB) { dp[i][curB][0][1] += dp[i - 1][max(0, prevB)][1][1]; }
		}

		for (int j = 0; j <= 9; j++) {
			for (int prevJ = 0; prevJ <= 9; prevJ++) {
				if (j != prevJ) { 
					dp[i][j][0][0] += dp[i - 1][prevJ][0][0];
					if (j > curA) { dp[i][j][0][0] += dp[i - 1][prevJ][1][0]; }
					if (j < curB) { dp[i][j][0][0] += dp[i - 1][prevJ][0][1]; }
					if (j > curA && j < curB) { dp[i][j][0][0] += dp[i - 1][prevJ][1][1]; }
				}
			}
		}				
	}

	ll ans = 0;
	for (int i = 0; i <= 9; i++)
		for (int b1 = 0; b1 < 2; b1++)
			for (int b2 = 0; b2 < 2; b2++)
				ans += dp[n - 1][i][b1][b2];
	
	cout << ans << '\n';
}
