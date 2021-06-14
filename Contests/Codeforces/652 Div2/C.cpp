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

	int t; cin >> t;

	while (t--) {
		int n, k; cin >> n >> k;
		int bonus = 0;
		vector<ll> nums(n);	for (auto &x : nums) { cin >> x; }
		vector<int> w(k); for (auto &x : w) { cin >> x; x--; if (!x) { bonus++; } }

		sort(nums.begin(), nums.end());
		sort(w.begin(), w.end());
		ll res = 0;
		for (int i = 0; i < k; i++) {
			res += nums.back();
			if (bonus) { res += nums.back(); bonus--; }
			nums.pop_back();
		}

		for (int i = 0; i < k; i++) {
			if (w[i] == 0) { continue; }
			while (w[i] > 1) { nums.pop_back(); w[i]--; }
			res += nums.back(); nums.pop_back();
		}

		cout << res << '\n';
	}
}