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
		vector<int> nums(n);
		set<int> S;
		for (auto &x : nums) { cin >> x; S.insert(x); }

		int ans = -1;
		for (int k = 1; k < 1024; k++) {
			bool OK = true;
			for (int i = 0; i < n; i++) {
				if (S.count(nums[i] ^ k) == 0) { OK = false; break; }
			}
			if (OK) { ans = k; break; }
		}

		cout << ans << '\n';
	}
}