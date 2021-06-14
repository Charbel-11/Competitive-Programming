#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	int even = 0, odd = 0;
	for (auto &x : nums) {
		if (x % 2) { odd++; }
		else { even++; }
	}

	int res = min(even, odd);
	cout << res << endl;
}