#include <iostream>
#include <vector>

using namespace std;

int main() {
	//assumes t >= 0
	int t = 28;
	int ns[] = { 1,20,10,6,9,12,2,3,8,4 };
	vector<int> nums;
	for (int i = 0; i < 10; i++) {
		nums.push_back(ns[i]);
	}
	int n = nums.size();

	vector<vector<int>> dp(n); for (auto &x : dp) { x.resize(t + 1, 0); }
	for (int i = 0; i < n; i++) { dp[i][0] = 1; }
	if (nums[0] <= t) { dp[0][nums[0]] = 2; }

	for (int i = 1; i < n; i++) {
		for (int j = t; j > 0; j--) {
			if (j - nums[i] >= 0) {
				dp[i][j] = dp[i - 1][j - nums[i]];
			}
			if (!dp[i][j] && dp[i - 1][j]) { dp[i][j] = 1; }
			else if (dp[i][j]) { dp[i][j] = 2; }
		}
	}

	int i = n - 1;
	while (i >= 0) {
		if (dp[i][t] == 2) {
			cout << nums[i] << " ";
			t -= nums[i];
		}
		i--;
	}
}