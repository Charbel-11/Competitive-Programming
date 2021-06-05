#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;
typedef long long ll;

int n; ll res = INT_MAX;
vector<int> nums;

//diff could overflow because of the case where we always add
void minDiff(int i, ll diff) {
	if (i == n) { res = min(res, abs(diff)); return; }
	minDiff(i + 1, diff + nums[i]);
	minDiff(i + 1, diff - nums[i]);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n; nums.resize(n); 
	for (auto &x : nums) { cin >> x; }
	minDiff(0, 0);
	cout << res << '\n';
}