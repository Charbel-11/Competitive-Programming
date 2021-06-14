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

	vector<vector<bool>> dp(2); dp[0].resize(t+1, 0); dp[1].resize(t+1, 0);
	dp[0][0] = 1; dp[1][0] = 1;
	
	bool col = 1;

	for (int i = 0; i < n; i++) {
		for (int j = t; j > 0; j--) {
			if (j - nums[i] >= 0) {
				dp[col][j] = dp[!col][j - nums[i]];
			}
			dp[col][j] = dp[col][j] | dp[!col][j];
		}
		col = !col;
	}

	cout << dp[!col][t] << endl;
}