#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll dp[402][402][2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; ll d; cin >> n >> d;
		vector<ll> v(n); for (auto& x : v) { cin >> x; }

		for (int l = 0; l < n; l++) {
			for (int i = 0; i + l < n; i++) {
				int curL = i, curR = i + l;

				for (int k = 0; k < 2; k++) {

					ll add = 0;
					if (k == 0 && curL != 0) { add = d - v[curL - 1]; }
					else if (k == 1 && curR != n - 1) { add = d - v[curR + 1]; }

					if (l == 0) {
						ll curV = v[i] + add; curV %= d;
						dp[i][i][k] = min(curV, d - curV);
					}
					else {
						ll curVL = v[curL] + add; curVL %= d;
						ll curVR = v[curR] + add; curVR %= d;

						ll c1 = dp[curL + 1][curR][0] + min(curVL, d - curVL);
						ll c2 = dp[curL][curR - 1][1] + min(curVR, d - curVR);
						dp[curL][curR][k] = min(c1, c2);
					}
				}
			}
		}

		cout << "Case #" << qq << ": " << dp[0][n-1][0] << '\n';
	}
}
