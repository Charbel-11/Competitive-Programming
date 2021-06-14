#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	int A = 0, B = 0;
	sort(nums.rbegin(), nums.rend());

	bool alt = true;
	for (auto &x : nums) {
		if (alt) { A += x; }
		else { B += x; }

		alt = !alt;
	}

	cout << A << " " << B << endl;
}