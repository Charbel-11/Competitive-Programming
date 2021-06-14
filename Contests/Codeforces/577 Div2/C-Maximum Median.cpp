#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	long long n, k;
	cin >> n >> k;

	vector<long long> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	sort(nums.begin(), nums.end());

	int med = (n + 1) / 2;
	med--;
	int next = med + 1;
	long long factor = 1;

	while (k > 0) {
		while (next < n && nums[med] == nums[next]) { next++; factor++; }
		if (next == n) {
			nums[med] += (k / factor);
			break;
		}

		long long temp = min(k, factor*(nums[next] - nums[med]));
		nums[med] += temp/factor;
		k -= temp;
	}

	cout << nums[med] << endl;
}