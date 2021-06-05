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
const ll mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string K; cin >> K;
	int n = K.size();
	int D; cin >> D;

	vector<vector<vector<ll>>> dp(2, vector<vector<ll>>(D, vector<ll>(2, 0)));
	dp[0][0][1] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < D; j++) {
			for (int b = 0; b < 2; b++) {
				for (int k = 0; k < 10; k++) {
					int ni = (i + 1)%2, nj = (j + k) % D, nb = 0;
					int curNum = K[i] - '0';

					if (b) {
						if (k > curNum) { break; }
						else if (k == curNum) { nb = 1; }
					}
					dp[ni][nj][nb] += dp[(i%2)][j][b]; dp[ni][nj][nb] %= mod;
				}
				dp[i%2][j][b] = 0;
			}
		}
	}

	ll ans = dp[(n%2)][0][0] + dp[(n%2)][0][1]; ans %= mod;
	ans--; ans %= mod;
	if (ans < 0) { ans += mod; }
	cout << ans << '\n';
}