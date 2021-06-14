#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll dp[101][101][101];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; ll x; cin >> n >> x;
	vector<ll> A(n); for (auto& xx : A) { cin >> xx; }

	for (int j = 0; j <= n; j++)
		for (int k = 0; k <= j; k++)
			for (int m = 0; m < j; m++)
				dp[j][k][m] = -1e12;

	for (int j = 0; j <= n; j++)
		dp[j][0][0] = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = j; k >= 1; k--) {
				for (int m = 0; m < j; m++) {
					int prevM = (m - A[i]) % j; prevM += j; prevM %= j;
					dp[j][k][m] = max(dp[j][k][m], dp[j][k - 1][prevM] + A[i]);
				}
			}
		}
	}

	ll ans = 2e18;
	for (int j = 1; j <= n; j++) {
		for (int m = 0; m < j; m++) {
			if (dp[j][j][m] < 0 || x % j != m) { continue; }
			ll curX = x - dp[j][j][m];
			ans = min(ans, curX / j);
		}
	}

	cout << ans << '\n';
}