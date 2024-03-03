#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
	vector<int> a(n), b(n);
	for (auto& x : a) { cin >> x; }
	for (auto& x : b) { cin >> x; }

	vector<vector<bool>> dp(n, vector<bool>(2, 0));
	dp[0][0] = dp[0][1] = true;

	for (int i = 1; i < n; i++) {
		if (dp[i - 1][0]) {
			if (abs(a[i] - a[i - 1]) <= k) { dp[i][0] = true; }
			if (abs(b[i] - a[i - 1]) <= k) { dp[i][1] = true; }
		}
		if (dp[i - 1][1]) {
			if (abs(a[i] - b[i - 1]) <= k) { dp[i][0] = true; }
			if (abs(b[i] - b[i - 1]) <= k) { dp[i][1] = true; }
		}
	}

	if (dp[n - 1][0] || dp[n - 1][1]) { cout << "Yes" << '\n'; }
	else { cout << "No" << '\n'; }
}
