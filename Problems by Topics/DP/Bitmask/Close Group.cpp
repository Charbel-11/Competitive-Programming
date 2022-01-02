// https://atcoder.jp/contests/abc187/tasks/abc187_f

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
	vector<vector<bool>> adj(n, vector<bool>(n, 0));
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		adj[u][v] = adj[v][u] = 1;
	}

	vector<bool> isClique((1 << n), 1);
	for (int mask = 1; mask < (1 << n); mask++) {
		for (int u = 0; u < n; u++) {
			for (int v = u + 1; v < n; v++) {
				if (((mask >> u) & 1) && ((mask >> v) & 1)) {
					if (!adj[u][v]) { isClique[mask] = 0; break; }
				}
			}
			if (!isClique[mask]) { break; }
		}
	}

	vector<int> dp((1 << n), n); dp[0] = 0;
	for (int mask = 1; mask < (1 << n); mask++) {
		if (isClique[mask]) { dp[mask] = 1; continue; }
		for (int subM = mask - 1; subM; subM = (subM - 1) & mask) {
			dp[mask] = min(dp[mask], dp[subM] + dp[mask ^ subM]);
		}
	}

	cout << dp[(1 << n) - 1] << '\n';
}