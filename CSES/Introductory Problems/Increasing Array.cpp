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
	vector<ll> nums(n); for (auto &x : nums) { cin >> x; }
	ll res = 0;
	for (int i = 1; i < n; i++) {
		if (nums[i] < nums[i - 1]) { res += nums[i - 1] - nums[i]; nums[i] = nums[i - 1]; }
	}
	cout << res << '\n';
}