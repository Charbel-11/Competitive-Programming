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

	int n, t; cin >> n >> t;
	vector<pair<int, int>> nums(n);
	for (int i = 0; i < n; i++) {
		int cur; cin >> cur;
		nums[i] = { cur, i };
	}
	sort(nums.begin(), nums.end());

	bool found = false;
	int i = 0, j = n - 1;
	while (i < j) {
		int cur = nums[i].first + nums[j].first;
		if (cur == t) { found = true; break; }
		if (cur > t) { j--; }
		else { i++; }
	}

	if (found) { cout << nums[i].second + 1 << ' ' << nums[j].second + 1 << '\n'; }
	else { cout << "IMPOSSIBLE\n"; }
}