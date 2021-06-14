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

		vector<bool> peak(n, 0);
		for (int i = 1; i < n-1; i++) {
			if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) { peak[i] = 1; }
		}

		int maxpeak = 0, cur = 0, l = 0;
		for (int i = 1; i < k-1; i++) {
			cur += peak[i];
		}
		maxpeak = cur;

		for (int i = k; i < n; i++) {
			cur -= peak[i - k + 1]; cur += peak[i - 1];
			if (cur > maxpeak) { maxpeak = cur; l = i - k + 1; }
		}

		cout << maxpeak+1 << " " << l+1 << endl;
	}
}