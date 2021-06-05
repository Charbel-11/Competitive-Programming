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

int n, k;
vector<int> nums;

bool check(ll mid) {
	int neededDiv = 1;
	ll cur = 0;
	for (int i = 0; i < n; i++) {
		if (nums[i] > mid) { return false; }
		cur += nums[i];
		if (cur > mid) { cur = nums[i]; neededDiv++; }
	}
	return neededDiv <= k;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> k;
	nums.resize(n); for (auto &x : nums) { cin >> x; }

	ll l = 1, r = (ll)1e15;
	while (l < r) {
		ll mid = (l + r) / 2;
		bool b = check(mid);
		if (b) { r = mid; }
		else { l = mid + 1; }
	}

	cout << l << '\n';
}