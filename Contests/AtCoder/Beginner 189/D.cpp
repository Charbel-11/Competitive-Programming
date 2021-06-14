#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll dp[62][2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<string> S(n);
	for (auto& x : S) { cin >> x; }
	dp[0][0] = dp[0][1] = 1;
	for (int i = 1; i <= n; i++) {
		if (S[i - 1] == "AND") {
			dp[i][1] = dp[i - 1][1];
			dp[i][0] = dp[i - 1][0] * 2 + dp[i - 1][1];
		}
		else {
			dp[i][1] = dp[i - 1][0] + dp[i - 1][1] * 2;
			dp[i][0] = dp[i - 1][0];
		}
	}

	cout << dp[n][1] << '\n';
}