#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<long long> nums;
	long long sum = 0;
	for (int i = 0; i < n; i++) {
		long long temp;
		cin >> temp;
		sum += temp;
		nums.push_back(temp);
	}

	sort(nums.begin(), nums.end());
	sum -= nums[n - 1];
	
	if ((sum + nums[n - 1]) % 2 == 0 && sum >= nums[n - 1]) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
}

