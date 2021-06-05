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

int dp[(int)1e5 + 5][102];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<int> nums(n); 
	for (auto &x : nums) { cin >> x; }

	if (nums[0] != 0) { dp[0][nums[0]] = 1; }
	else { for (int i = 1; i <= m; i++) dp[0][i] = 1; }
	
	for (int i = 1; i < n; i++) {
		if (nums[i] != 0) {
			dp[i][nums[i]] = dp[i - 1][nums[i] - 1] + dp[i - 1][nums[i]]; dp[i][nums[i]] %= mod;
			dp[i][nums[i]] += dp[i - 1][nums[i] + 1]; dp[i][nums[i]] %= mod;
			continue;
		}
		for (int j = 1; j <= m; j++) {
			dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; dp[i][j] %= mod;
			dp[i][j] += dp[i - 1][j + 1]; dp[i][j] %= mod;
		}
	}

	int res = 0;
	for (int j = 1; j <= m; j++) {
		res += dp[n - 1][j];
		res %= mod;
	}

	cout << res << '\n';
}