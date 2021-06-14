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

	int n, q; cin >> n >> q;
	vector<ll> nums(n);
	set<ll> pos; multiset<ll> diff;

	for (int i = 0; i < n; i++) {
		ll tmp; cin >> tmp;
		pos.insert(tmp); nums[i] = tmp;
	}
	sort(nums.begin(), nums.end());

	ll totalDiff = 0;
	for (int i = 1; i < n; i++) {
		ll curDiff = nums[i] - nums[i - 1];
		totalDiff += curDiff;
		diff.insert(curDiff);
	}

	if (diff.empty()) { cout << 0 << '\n'; }
	else { cout << totalDiff - (*prev(diff.end())) << '\n'; }

	while (q--) {
		int t, x; cin >> t >> x;

		if (!t) { pos.erase(x); }
		auto it = pos.lower_bound(x);
		ll pos1 = -1, pos2 = -1;
		if (it != pos.end()) { pos2 = *it; }
		if (it != pos.begin()) { pos1 = *(--it); }

		if (t) {	
			pos.insert(x);
			if (pos1 != -1 && pos2 != -1) { diff.erase(diff.find(pos2 - pos1)); totalDiff -= (pos2 - pos1); }
			if (pos1 != -1) { diff.insert(x - pos1); totalDiff += (x - pos1); }
			if (pos2 != -1) { diff.insert(pos2 - x); totalDiff += (pos2 - x); }
		}
		else {
			if (pos1 != -1 && pos2 != -1) { diff.insert(pos2 - pos1); totalDiff += (pos2 - pos1); }
			if (pos1 != -1) { diff.erase(diff.find(x - pos1)); totalDiff -= (x - pos1); }
			if (pos2 != -1) { diff.erase(diff.find(pos2 - x)); totalDiff -= (pos2 - x); }
		}

		if (diff.empty()) { cout << 0 << '\n'; continue; }
		cout << totalDiff - (*prev(diff.end())) << '\n';
	}
}