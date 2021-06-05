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

	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	vector<int> maxAtLen(n + 1, (int)1e9 + 10);
	maxAtLen[0] = 0; int res = 0;
	for (int i = 0; i < n; i++) {
		int idx = lower_bound(maxAtLen.begin(), maxAtLen.end(), nums[i]) - maxAtLen.begin() - 1;
		maxAtLen[idx + 1] = min(maxAtLen[idx + 1], nums[i]);
		res = max(res, idx + 1);
	}

	cout << res << '\n';
}