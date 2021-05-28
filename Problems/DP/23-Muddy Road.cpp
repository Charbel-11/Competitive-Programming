//https://community.topcoder.com/stat?c=problem_statement&pm=11420

#include <iostream>
#include <string>
#include <vector>

using namespace std;

double DP[100];
vector<double> nums;

double expected(int i) {
	if (DP[i] != -1) { return DP[i]; }
	if (i >= nums.size() - 2) { return 0;  }

	double c1 = nums[i + 1] * nums[i + 2] *(1 + expected(i + 2));
	double c2 = nums[i + 1] * (1 - nums[i + 2]) * expected(i + 2);
	double c3 = (1 - nums[i + 1]) * expected(i + 1);

	DP[i] = c1 + c2 + c3;
	return DP[i];
}

void resetDP() {
	for (int i = 0; i < 100; i++) { DP[i] = -1; }
}

int main() {
	int n; cin >> n;
	nums.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
		nums[i] = double(nums[i])/100.0;
	}
	resetDP();

	cout << expected(0) << endl;
}