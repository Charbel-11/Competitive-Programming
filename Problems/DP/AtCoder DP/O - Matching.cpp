#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

int countOnes(int m) {
	int ans = 0;
	while (m) { ans++; m = m & (m - 1); }
	return ans;
}

int main() {
	int n; cin >> n;
	vector<vector<int>> match(n);
	for (auto &v : match) { v.resize(n); for (auto &x : v) { cin >> x; } }
	vector<ll> dp((1 << n) + 1, 0); dp[0] = 1;

	//This works since we don't care about the order in which we match people in A
	//And at each iteration, we increment the dp value of a bigger mask hence at a given mask we have the correct answer
	//Since we care about the subset of matches, given the state of B we assume we matched the first numBit(mask) in A
	for (int mask = 0; mask < (1 << n) - 1; mask++) {		//mask houwe states l B
		int a = countOnes(mask);	//first a bits are already matched
		for (int b = 0; b < n; b++) {
			if (match[a][b] && !(mask & (1<<b))) {
				int newM = mask ^ (1 << b);
				dp[newM] += dp[mask]; dp[newM] %= mod;
			}
		}
	}

	cout << dp[(1 << n) - 1] << endl;
}