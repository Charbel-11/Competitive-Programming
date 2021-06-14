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
		int n; cin >> n;
		vector<int> nums(2 * n); for (auto &x : nums) { cin >> x; }
		vector<bool> found(n + 1, 0);
		vector<int> ans;

		for (int i = 0; i < 2 * n; i++) {
			int cur = nums[i];
			if (!found[cur]) {
				found[cur] = 1;
				ans.push_back(cur);
			}
		}

		for (auto &x : ans) { cout << x << ' '; }
		cout << '\n';
	}
}