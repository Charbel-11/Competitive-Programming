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

	while (t--) {
		int n, m, x, y; cin >> n >> m >> x >> y;
		vector<string> grid(n);
		for (auto &x : grid) { cin >> x; }

		int w = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == '.') { w++; }
			}
		}

		if (2 * x <= y) { cout << x * w << endl; continue; }

		int res = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 1; j < m; j++) {
				if (grid[i][j - 1] == '.' && grid[i][j] == '.') {
					grid[i][j - 1] = grid[i][j] = '*';
					res += y;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == '.') { res += x; }
			}
		}

		cout << res << endl;
	}
}