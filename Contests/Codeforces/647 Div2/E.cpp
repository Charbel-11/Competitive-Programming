#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

const ll mod = 1000000007;

ll power(ll x, ll p) {
	if (p == 0) { return 1ll; }
	x %= mod;
	ll temp = power(x, p / 2) % mod;
	temp *= temp; temp %= mod;
	if (p & 1) { temp *= x; temp %= mod; }
	return temp;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n, p; cin >> n >> p;
		vector<int> nums(n);
		for (auto &x : nums) { cin >> x; }
		if (p == 1) {
			if (n % 2 == 0) { cout << 0 << '\n'; }
			else { cout << 1 << '\n'; }
			continue;
		}

		sort(nums.rbegin(), nums.rend());

		vector<int> set1, set2;
		bool reset = true;
		for (int i = 0; i < n; i++) {
			if (reset) { set1.push_back(nums[i]); reset = false; continue; }
			if (set1.back() == nums[i]) { set2.push_back(nums[i]); reset = true; continue; }

			int target = set1.back();
			vector<pair<int, int>> s;
			for (; i < n; i++) {
				if (s.empty()) { s.push_back({ nums[i], 1 }); continue; }

				int curNum = nums[i]; bool done = false;
				while(!s.empty() && s.back().first == curNum){
					pair<int, int> curP = s.back();	s.pop_back();
					if (curP.second + 1 < p) { s.push_back({ curP.first, curP.second + 1 }); done = true; break; }
					else { curNum++; }
				}
				if (!done) { s.push_back({ curNum, 1 }); }

				if (!s.empty() && s.back().first == target) { reset = true; break; }
			}

			while (!s.empty()) {
				pair<int, int> curP = s.back();	s.pop_back();
				for (int mm = 0; mm < curP.second; mm++) {
					set2.push_back(curP.first);
				}
			}
		}

		ll res = 0;
		for (int i = 0; i < set1.size(); i++) { res += power(p, set1[i]); res %= mod; }
		for (int i = 0; i < set2.size(); i++) { res -= power(p, set2[i]); res %= mod; }

		while (res < 0) { res += mod; res %= mod; }

		cout << res << '\n';
	}
}