#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }

		sort(nums.rbegin(), nums.rend());

		for (auto &x : nums) { cout << x << " "; }
		cout << endl;
	}
}