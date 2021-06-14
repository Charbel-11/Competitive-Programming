#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

int main() {
	int t;  cin >> t;

	while (t--) {
		int n, k, d; cin >> n >> k >> d;
		map<int, int> showF;
		vector<int> nums(n);
		for (int i = 0; i < n; i++) {
			int temp; cin >> temp;
			nums[i] = temp;
		}

		for (int i = 0; i < d; i++) {
			showF[nums[i]]++;
		}

		int res = (int)showF.size();
		for (int i = d; i < n; i++) {
			showF[nums[i - d]]--; showF[nums[i]]++;
			if (showF[nums[i - d]] == 0) { showF.erase(nums[i - d]); }
			res = min(res, (int)showF.size());
		}

		cout << res << endl;
	}
}