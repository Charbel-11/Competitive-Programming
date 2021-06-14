#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> nums(n);
		map<int, int> m;
		for (auto &x : nums) { cin >> x; }

		bool OK = false;
		for (int i = 0; i < n; i++) {
			if (m[nums[i]] && ((nums[i - 1] != nums[i]) || (m[nums[i]] > 1))) {
				OK = true; break;
			}
			m[nums[i]]++;
		}

		cout << (OK ? "YES" : "NO") << endl;
	}
}