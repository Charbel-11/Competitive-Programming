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
const int INF = 1e9;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int x, y; cin >> x >> y;
		string s; cin >> s; int n = s.size();
		vector<vector<int>> dp(n + 1, vector<int>(2, INF));
		if (s[0] != 'C') { dp[0][0] = 0; }
		if (s[0] != 'J') { dp[0][1] = 0; }

		for (int i = 1; i < n; i++) {
			int cJ = min(dp[i - 1][0], dp[i - 1][1] + x);
			int cC = min(dp[i - 1][1], dp[i - 1][0] + y);
			if (s[i] != 'C') { dp[i][0] = cJ; }
			if (s[i] != 'J') { dp[i][1] = cC; }
		}

		int ans = min(dp[n-1][0], dp[n-1][1]);
		cout << "Case #" << qq << ": " << ans << '\n';
	}
}