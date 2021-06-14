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
		int n; cin >> n;
		vector<vector<int>> grid(n, vector<int>(n));
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> grid[i][j];
			}
		}

		ll ans = 0;
		for (int j = 0; j < n; j++) {
			ll cur = 0;
			for (int i = 0; i < n; i++) {
				if (j + i >= n) { break; }
				cur += grid[i][j + i];
			}
			ans = max(ans, cur);
		}

		for (int i = 0; i < n; i++) {
			ll cur = 0;
			for (int j = 0; j < n; j++) {
				if (j + i >= n) { break; }
				cur += grid[i + j][j];
			}
			ans = max(ans, cur);
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}