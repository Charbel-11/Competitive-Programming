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

ll dp[5002][5002];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dp[i][j] = -(ll)1e15;
	vector<ll> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
		dp[i][i] = nums[i];
	}
	for (int i = 0; i < n - 1; i++) { dp[i][i + 1] = max(nums[i], nums[i + 1]); }

	for (int i = n - 3; i >= 0; i--) {
		for (int j = i + 2; j < n; j++) {
			dp[i][j] = nums[i] + min(dp[i + 2][j], dp[i + 1][j - 1]);
			dp[i][j] = max(dp[i][j], nums[j] + min(dp[i + 1][j - 1], dp[i][j - 2]));
		}
	}

	cout << dp[0][n - 1] << '\n';
}