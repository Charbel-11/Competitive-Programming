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
	vector<ll> nums(n);
	for (auto &x : nums) { cin >> x; }

	ll res = nums[0], cur = nums[0];
	for (int i = 1; i < n; i++) {
		if (cur < 0) { cur = nums[i]; }
		else { cur += nums[i]; }
		res = max(res, cur);
	}
	cout << res << '\n';
}