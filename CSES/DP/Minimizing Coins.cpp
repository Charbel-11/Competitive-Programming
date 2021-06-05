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

	int n, x; cin >> n >> x;
	vector<int> coins;
	for (int i = 0; i < n; i++) {
		int cur; cin >> cur;
		if (cur > x) { continue; }
		coins.push_back(cur);
	}
	n = (int)coins.size();

	vector<int> dp(x + 1, x + 1);
	for (int i = 0; i < n; i++) { dp[coins[i]] = 1; }
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j < n; j++) {
			int nxt = i + coins[j];
			if (nxt > x) { continue; }
			dp[nxt] = min(dp[nxt], dp[i] + 1);
		}
	}

	cout << (dp[x] == x + 1 ? -1 : dp[x]) << '\n';
}