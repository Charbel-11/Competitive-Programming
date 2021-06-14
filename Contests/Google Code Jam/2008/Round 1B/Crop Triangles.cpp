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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		ll n, A, B, C, D, x0, y0, M;
		cin >> n >> A >> B >> C >> D >> x0 >> y0 >> M;

		vector<vector<ll>> occ(3, vector<ll>(3, 0));
		ll X = x0, Y = y0;
		occ[X % 3][Y % 3]++;
		for (int i = 1; i <= n - 1; i++) {
			X = (A * X + B) % M;
			Y = (C * Y + D) % M;
			occ[X % 3][Y % 3]++;
		}

		ll ans = 0;
		for (int x1 = 0; x1 < 3; x1++) {
			for (int y1 = 0; y1 < 3; y1++) {
				for (int x2 = 0; x2 < 3; x2++) {
					for (int y2 = 0; y2 < 3; y2++) {
						for (int x3 = 0; x3 < 3; x3++) {
							for (int y3 = 0; y3 < 3; y3++) {
								if ((x1 + x2 + x3) % 3 || (y1 + y2 + y3) % 3) { continue; }
								if ((x1 == x2 && y1 == y2) || (x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3)) { continue; }
								ans += occ[x1][y1] * occ[x2][y2] * occ[x3][y3];
							}
						}
					}
				}
			}
		}
		ans /= 6;

		for (int x1 = 0; x1 < 3; x1++)
			for (int y1 = 0; y1 < 3; y1++)
				ans += (occ[x1][y1] * (occ[x1][y1] - 1) * (occ[x1][y1] - 2)) / 6;

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}