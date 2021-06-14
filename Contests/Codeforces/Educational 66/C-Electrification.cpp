#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int n, k;
		cin >> n >> k;

		vector<long long> nums(n);
		for (int i = 0; i < n; i++){
			cin >> nums[i];
		}

		long long answ = INT_MAX;
		long long x = 0;
		for (int i = k; i < n; i++) {		//Need to try every number such that we get k number before it; they are consecutive
			//We are testing only from k to n and nums[i-k] with nums[i] since if we did it from 0 to n-k and nums[i] with nums[i+k], 
			//it is the same. But we would need to take the ceil instead of the floor so its better this way
			long long c = (nums[i] + nums[i - k]) / 2;
			if (abs(nums[i] - c) < answ) {
				x = c;
				answ = abs(nums[i] - c);
			}
		}

		cout << x << endl;
	}
}