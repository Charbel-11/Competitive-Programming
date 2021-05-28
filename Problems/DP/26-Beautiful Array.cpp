#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> nums;
long long x;
long long DP[300002][4];

long long maxB(int i, int s) {
	if (DP[i][s] != -1) { return DP[i][s]; }
	if (i >= nums.size()) { return 0; }

	long long c1, c2, c3;
	c3 = 0;

	if (s == 0) {
		c1 = maxB(i + 1, 0);
		c2 = maxB(i + 1, 1);
		c3 = maxB(i + 1, 2);
	}
	else if (s == 1) {
		c1 = nums[i] + maxB(i + 1, 1);
		c2 = nums[i] + maxB(i + 1, 2);
		c3 = nums[i] + maxB(i + 1, 3);
	}
	else if (s == 2) {
		c1 = nums[i] * x + maxB(i + 1, 2);
		c2 = nums[i] * x + maxB(i + 1, 3);
		c3 = nums[i] * x;
	}
	else {
		c1 = nums[i] + maxB(i + 1, 3);
		c2 = nums[i];
	}

	c1 = max(c1, c2);
	c1 = max(c1, c3);
	c1 = max(c1, 0ll);

	DP[i][s] = c1;
	return c1;
}

void resetDP() {
	for (int i = 0; i < 300002; i++) {
		for (int j = 0; j < 4; j++) {
			DP[i][j] = -1;
		}
	}
}

int main() {
	int n;
	cin >> n >> x;
	resetDP();

	nums.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	long long c1 = maxB(0, 0);
	long long c2 = maxB(0, 1);
	long long c3 = maxB(0, 2);

	c1 = max(c1, c2);
	c1 = max(c1, c3);

	cout << c1 << endl;
}