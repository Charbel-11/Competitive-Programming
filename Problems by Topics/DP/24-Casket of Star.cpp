#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> nums;
int DP[52][52];

int maxEnergy(int i, int j) {
	if (i == j-1) { return 0; }

	int maxRes = 0;

	for (int k = i + 1; k < j; k++) {
		int cur = nums[i] * nums[j] + maxEnergy(i, k) + maxEnergy(k, j);
		maxRes = max(maxRes, cur);
	}

	return maxRes;
}

void resetDP() {
	for (int i = 0; i < 52; i++)
		for (int j = 0; j < 52; j++)
			DP[i][j] = -1;
}

int main() {
	resetDP();
	int n;
	cin >> n;
	nums.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	cout << maxEnergy(0, n - 1) << endl;
}