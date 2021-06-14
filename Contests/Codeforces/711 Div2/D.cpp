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

	int n, m; cin >> n >> m;
	vector<int> dp(m + 1, -1); dp[0] = 0;

	for (int i = 0; i < n; i++) {
		ll t, x, y; cin >> t >> x >> y;
		vector<bool> vis(m + 1, 0);
		
		if (t == 1) { 
			x = (x + 99999) / 100000;
			for (int j = m; j >= 0; j--) {
				if (vis[j] || dp[j] == -1 || dp[j] == i + 1) { continue; }
				ll curY = y;

				for (ll k = j + x; k <= m && curY; k += x, curY--) {
					if (vis[k]) { break; }
					vis[k] = true;
					if (dp[k] == -1) { dp[k] = i + 1; }
					else { dp[k] = min(dp[k], i + 1); }
				}
			}
		}
		else {
			for (int j = m; j >= 1; j--) {
				if (vis[j] || dp[j] == -1 || dp[j] == i + 1) { continue; }
				ll curY = y;

				for (ll k = (x * j + 99999) / 100000; k <= m && curY; k = (k * x + 99999) / 100000, curY--) {
					if (vis[k]) { break; }
					vis[k] = true;
					if (dp[k] == -1) { dp[k] = i + 1; }
					else { dp[k] = min(dp[k], i + 1); }
				}
			}
		}
	}

	for (int i = 1; i <= m; i++) { cout << dp[i] << " "; } cout << '\n';
}
