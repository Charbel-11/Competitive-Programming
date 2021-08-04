#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <bitset>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

const int M = (int)1e5 + 2;
bitset<M + 1> dp;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		dp |= dp << nums[i];
	}

	vector<int> ans;
	for (int i = 1; i <= M; i++) {
		if (dp[i]) { ans.push_back(i); }
	}

	cout << ans.size() << '\n';
	for (auto &x : ans) { cout << x << ' '; }
	cout << '\n';
}