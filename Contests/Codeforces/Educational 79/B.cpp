#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	int t; cin >> t;
	
	while (t--) {
		long long n, s; cin >> n >> s;
		vector<long long> nums(n);
		for (auto &x : nums) { cin >> x; }

		int cMax = nums[0], cIdx = 0;
		bool used = false;
		long long cur = nums[0];

		for (int i = 1; i < n; i++) {
			cur += nums[i];
			if (cMax < nums[i]) {
				if (used) { break; }
				cMax = nums[i];
				cIdx = i;
			}
		
			if (cur > s) {
				used = true;
				cur -= cMax;
			}
		}

		if (used) { cout << cIdx + 1 << endl; }
		else { cout << 0 << endl; }
	}
}