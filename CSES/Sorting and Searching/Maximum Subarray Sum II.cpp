#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, a, b; cin >> n >> a >> b;
	vector<ll> nums(n); for (auto &x : nums) { cin >> x; }
	vector<ll> pref(n, 0), maxPref(n, 0);
	pref[0] = nums[0];
	for (int i = 1; i < n; i++) { pref[i] = pref[i - 1] + nums[i]; }

	deque<ll> window; int sz = b - a;
	if (sz) {
		for (int i = 0; i < sz; i++) {
			while (!window.empty() && pref[i] > window.back()) { window.pop_back(); }
			window.push_back(pref[i]);
		}
		maxPref[0] = window.front();
		for (int i = sz; i < n; i++) {
			while (!window.empty() && pref[i] > window.back()) { window.pop_back(); }
			if (!window.empty() && window.front() == pref[i - sz]) { window.pop_front(); }
			window.push_back(pref[i]);
			maxPref[i - (sz - 1)] = window.front();
		}
		for (int i = n - sz + 1; i < n; i++) {
			if (window.front() == pref[i - 1]) { window.pop_front(); }
			maxPref[i] = window.front();
		}
	}

	ll res = -(ll)1e16;
	for (int i = a - 1; i < n; i++) {
		ll curP = pref[i] - (i < a ? 0ll : pref[i - a]);
		if (i < n - 1) { curP += max(0ll, maxPref[i + 1] - pref[i]); }
		res = max(res, curP);
	}

	cout << res << '\n';
}