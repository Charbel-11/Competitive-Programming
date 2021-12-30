#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int M = 1000002;

int dp[M][22];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	for (int i = 0; i < M; i++)
		for (int k = 0; k < 22; k++)
			dp[i][k] = M;

	int n, q; cin >> n >> q;
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b; a--; b--;
		dp[a][0] = min(dp[a][0], b);
	}

	for (int i = M - 2; i >= 0; i--) { dp[i][0] = min(dp[i][0], dp[i + 1][0]); }

	for (int k = 1; k < 22; k++) {
		for (int i = 0; i < M; i++) {
			if (dp[i][k - 1] != M) {
				dp[i][k] = dp[dp[i][k - 1]][k - 1];
			}
		}
	}

	while (q--) {
		int a, b; cin >> a >> b; a--; b--;

		int ans = 0;
		while (a < b) {
			int k = 0; 
			while (dp[a][k] <= b) { k++; }
			if (k == 0) { break; }

			k--;
			ans += (1 << k); 
			a = dp[a][k];
		}

		cout << ans << '\n';
	}
}