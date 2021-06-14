#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long m, k;
vector<long long> nums;
long long DP[300003][11];

long long maxCost(int i, int j) {
	if (i == nums.size()) { return 0; }
	if (DP[i][j] != -1) { return DP[i][j]; }

	long long c = nums[i] + maxCost(i + 1, (j + 1) % m);
	if (j == 0) { c -= k; }

	DP[i][j] = max(c, 0ll);
	return DP[i][j];
}

void resetDP() {
	for (int i = 0; i < 300003; i++) {
		for (int j = 0; j < 11; j++) {
			DP[i][j] = -1;
		}
	}
}

int main() {
	int n;
	cin >> n >> m >> k;
	resetDP();

	for (int i = 0; i < n; i++) {
		long long temp;
		cin >> temp;
		nums.push_back(temp);
	}
	
	long long res = 0;
	for (int i = 0; i < n; i++) {
		long long cur = maxCost(i, 0);
		if (cur > res) { res = cur; }
	}
	
	cout << res << endl;
}