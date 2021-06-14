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

ll dp[202][202][202];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int R, G, B; cin >> R >> G >> B;
	vector<ll> r(R), g(G), b(B);
	for (auto &x : r) { cin >> x; }
	for (auto &x : g) { cin >> x; }
	for (auto &x : b) { cin >> x; }
	sort(r.rbegin(), r.rend());
	sort(g.rbegin(), g.rend());
	sort(b.rbegin(), b.rend());

	ll ans = 0;
	for (int i = 0; i <= R; i++) {
		for (int j = 0; j <= G; j++) {
			for (int k = 0; k <= B; k++) {
				if (i && j) { dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][k] + r[i-1] * g[j-1]); }
				if (i && k) { dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k - 1] + r[i-1] * b[k-1]); }
				if (j && k) { dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k - 1] + g[j-1] * b[k-1]); }
				ans = max(ans, dp[i][j][k]);
			}
		}
	}

	cout << ans << '\n';
}