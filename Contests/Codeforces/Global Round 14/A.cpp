#include <iostream>
#include <string>
#include <map>
#include <set>
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
		int n, x; cin >> n >> x;
		int S = 0;
		vector<int> nums(n); for (auto& xx : nums) { cin >> xx; S += xx; }
		if (S == x) { cout << "NO" << '\n'; continue; }

		cout << "YES" << '\n';
		int cur = 0;
		for (int i = 0; i < n - 1; i++) {
			cur += nums[i];
			if (cur == x) { swap(nums[i], nums[i + 1]); break; }
		}

		for (auto& xx : nums) { cout << xx << " "; } cout << '\n';
	}
}
