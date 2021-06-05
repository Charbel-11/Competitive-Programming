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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<vector<int>> adj(n, vector<int>(n, 0));
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		adj[u][v]++;
	}

	vector<vector<ll>> dp((1 << n), vector<ll>(n, 0)); dp[1][0] = 1;
	for (int i = 3; i < (1 << n); i += 2) {
		if (i & (1 << (n - 1)) && i < (1 << n) - 1) { continue; }
		for (int j = 1; j < n; j++) {
			if (!(i & (1 << j))) { continue; }

			int cur = i ^ (1 << j);
			for (int k = 0; k < n; k++) {
				if ((cur & (1 << k)) && adj[k][j]) {
					dp[i][j] += dp[cur][k] * adj[k][j];
					dp[i][j] %= mod;
				}
			}
		}
	}

	cout << dp[(1 << n) - 1][n - 1] << '\n';
}