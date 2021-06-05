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

pair<int, int> sum2(vector<pair<ll, int>> &nums, int t, int skip) {
	int n = nums.size(); bool found = false;
	int i = 0, j = n - 1;
	while (i < j) {
		if (i == skip) { i++; continue; }
		else if (j == skip) { j--; continue; }

		int cur = nums[i].first + nums[j].first;
		if (cur == t) { found = true; break; }
		if (cur > t) { j--; }
		else { i++; }
	}

	if (found) { return { nums[i].second, nums[j].second }; }
	return { -1,-1 };
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; ll t; cin >> n >> t;
	vector<pair<ll, int>> nums(n);
	for (int i = 0; i < n; i++) {
		int cur; cin >> cur;
		nums[i] = { cur, i };
	}
	sort(nums.begin(), nums.end());

	for (int k = 0; k < n; k++) {
		pair<int, int> p = sum2(nums, t - nums[k].first, k);
		if (p.first != -1) {
			cout << p.first + 1 << ' ' << p.second + 1 << ' ' << nums[k].second + 1 << '\n'; 
			return 0;
		}
	}

	cout << "IMPOSSIBLE\n";
}