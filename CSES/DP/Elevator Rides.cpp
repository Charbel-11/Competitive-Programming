#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, x; cin >> n >> x;
	vector<int> w(n); for (auto& xx : w) { cin >> xx; }

	vector<pair<int, int>> dp((1 << n), { n + 1, 0 }); dp[0] = { 1,0 };
	for (int i = 1; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if (!(i & (1 << j))) { continue; }
			int curI = i ^ (1 << j);
			if (dp[curI].second + w[j] <= x) 
				dp[i] = min(dp[i], { dp[curI].first, dp[curI].second + w[j] });
			else 
				dp[i] = min(dp[i], { dp[curI].first + 1, w[j] });
		}
	}

	cout << dp[(1 << n) - 1].first << '\n';
}
