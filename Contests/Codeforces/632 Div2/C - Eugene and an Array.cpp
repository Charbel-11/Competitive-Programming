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
	ll n; cin >> n;
	vector<ll> nums(n);
	for (auto &x : nums) { cin >> x; }

	map<ll, ll> m; m[0] = -1;
	ll cur = 0, l = 0, ans = 0;
	for (int i = 0; i < n; i++) {
		if (nums[i] == 0) {
			l = i + 1; continue;
		}
		cur += nums[i];
		if (m.count(cur)) {	l = max(l, m[cur] + 2); }
		m[cur] = i;
		ans += i - l + 1;
	}

	cout << ans << endl;
}