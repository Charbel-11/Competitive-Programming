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

ll stoLL(string &s) {
	ll res = 0, w = 1;
	for (int i = s.size() - 1; i >= 0; i--) {
		if (s[i] == '1') { res += w; }
		w *= 2;
	}
	return res;
}

string llToS(ll num, int m) {
	string res = "";
	while (num) { res.push_back(num % 2 ? '1' : '0'); num /= 2; }
	while (res.size() < m) { res.push_back('0'); }
	reverse(res.begin(), res.end());
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n, m; cin >> n >> m;
		vector<ll> nums(n);
		for (auto &x : nums) {
			string s; cin >> s;
			x = stoLL(s);
		}
		sort(nums.begin(), nums.end());

		ll guess = (1ll << (m - 1)) - 101; guess = max(guess, 0ll);
		while(true) {
			while (binary_search(nums.begin(), nums.end(), guess)) { guess++; }

			ll l = guess + 1; ll r = (1ll << m) - guess;
			int removedR = n - (upper_bound(nums.begin(), nums.end(), guess) - nums.begin());
			int removedL = n - removedR;
			r -= removedR; l -= removedL;

			if (l == r || l == r - 1) { break; }
			guess++;
		}

		cout << llToS(guess, m) << endl;
	}
}