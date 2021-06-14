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

int maxFreq(int l, int r, vector<vector<int>>& freq) {
	if (l > r) { return 0; }
	int ans = 1;
	for (int x = 1; x <= 200; x++) {
		ans = max(ans, freq[r][x] - (l ? freq[l - 1][x] : 0));
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }

		vector<vector<int>> freq(n+1, vector<int>(201, 0));
		vector<vector<int>> occ(201);
		for (int x = 1; x <= 200; x++) {
			for (int i = 0; i < n; i++) {
				freq[i][x] = (i ? freq[i - 1][x] : 0);
				if (nums[i] == x) { freq[i][x]++; occ[x].push_back(i); }
			}
		}

		int ans = 1;
		for (int x = 1; x <= 200; x++) {
			int l = 0, r = occ[x].size() - 1;
			while (l < r) {
				int curAns = 2 * (l + 1) + maxFreq(occ[x][l] + 1, occ[x][r] - 1, freq);
				ans = max(ans, curAns);
				l++; r--;
			}
		}

		cout << ans << endl;
	}
}