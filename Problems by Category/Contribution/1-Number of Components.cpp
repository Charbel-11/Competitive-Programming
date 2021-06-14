//https://codeforces.com/problemset/problem/1151/E
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<long long> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	long long res = nums[0]*(n-nums[0]+1);

	for (int i = 1; i < n; i++) {
		if (nums[i] == nums[i - 1]) {
			continue;
		}
		
		if (nums[i] > nums[i - 1]) {
			long long l = nums[i] - nums[i - 1];
			long long r = n - nums[i] + 1;

			res += r * l;
		}
		else {
			long long r = nums[i - 1] - nums[i];
			long long l = nums[i];

			res += r * l;
		}
	}

	cout << res << endl;
}