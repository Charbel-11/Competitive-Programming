#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n, k; cin >> n >> k;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }

		bool found = false;
		for (int i = 0; i < n; i++) {
			if (nums[i] == k) { found = true; break; }
		}
		if (!found) { cout << "no" << endl; continue; }

		bool OK = false;
		for (int i = 0; i < n; i++) {
			if (nums[i] == k) {
				if (i < n - 1 && nums[i + 1] >= k) { OK = true; break; }
				if (i > 0 && nums[i - 1] >= k) { OK = true; break; }
			}
		}
		if (n == 1 && nums[0] == k) { OK = true; }

		if (OK) { cout << "yes" << endl; continue; }

		int smaller = 0, bigger = 0;
		for (int i = 0; i < n; i++) {
			if (nums[i] < k) { smaller++; }
			else { bigger++; }
			if (bigger > smaller && smaller + bigger > 1) { OK = true; break; }
			if (smaller > bigger) { bigger = smaller = 0; }
		}

		cout << (OK ? "yes" : "no") << endl;
	}
}