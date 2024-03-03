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

vector<vector<ll>> grid;
ll totalCost;

ll findCost(ll r, ll c, ll n, ll m, int iS, int jS) {
	ll nN = n - iS, nM = m - jS;

	ll ans = totalCost * (nN / r) * (nM / c);
	ll add1 = 0, add2 = 0;

	for (int i = iS; i < iS + r; i++) {
		for (int j = m - nM % c; j < m; j++) {
			int nj = (j - jS) % c;
			add1 += grid[i - iS][nj];
		}
	}
	add1 *= max(1ll, (n / r)); ans += add1;

	for (int i = n - nN % r; i < n; i++) {
		for (int j = jS; j < jS + c; j++) {
			int ni = (i - iS) % r;
			add2 += grid[ni][j - jS];
		}
	}
	add2 *= max(1ll, (m / c)); ans += add2;

	for (int i = n - nN % r; i < n; i++) {
		for (int j = m - nM % c; j < m; j++) {
			int ni = (i - iS) % r, nj = (j - jS) % c;
			ans += grid[ni][nj];
		}
	}

	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll n, m, r, c; cin >> n >> m >> r >> c;
	grid.resize(r, vector<ll>(c));
	totalCost = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> grid[i][j];
			totalCost += grid[i][j];
		}
	}

	ll ans = findCost(r, c, n, m, 0, 0);

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (i == 0 && j == 0) { continue; }
			if (i + r >= n || j + c >= m) { continue; }

			ll cur = findCost(r, c, n, m, i, j);

			ll add1 = 0;
			for (int i2 = i; i2 < i + r; i2++) {
				for (int j2 = 0; j2 < j; j2++) {
					add1 += grid[i2 - i][c - j + j2];
				}
			}
			add1 *= ((n - i) / r);
			int startt = n - ((n - i) % r);
			for (int i2 = startt; i2 < n; i2++) {
				for (int j2 = 0; j2 < j; j2++) {
					add1 += grid[i2 - startt][c - j + j2];
				}
			}
			cur += add1;

			ll add2 = 0;
			for (int i2 = 0; i2 < i; i2++) {
				for (int j2 = j; j2 < j + c; j2++) {
					add2 += grid[r - i + i2][j2 - j];
				}
			}
			add2 *= ((m - j) / c);
			startt = m - ((m - j) % c);
			for (int i2 = 0; i2 < i; i2++) {
				for (int j2 = startt; j2 < m; j2++) {
					add2 += grid[r - i + i2][j2 - startt];
				}
			}
			cur += add2;

			for (int i2 = 0; i2 < i; i2++) {
				for (int j2 = 0; j2 < j; j2++) {
					cur += grid[r - i + i2][c - j + j2];
				}
			}

			ans = min(ans, cur);
		}
	}

	cout << ans << '\n';
}