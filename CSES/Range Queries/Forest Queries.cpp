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

	int n, q; cin >> n >> q;
	vector<string> grid(n);
	for (auto &s : grid) { cin >> s; }

	vector<vector<int>> pref(n, vector<int>(n, 0));
	pref[0][0] = (grid[0][0] == '*');
	for (int i = 1; i < n; i++) { 
		pref[i][0] = pref[i - 1][0] + (grid[i][0] == '*'); 
		pref[0][i] = pref[0][i - 1] + (grid[0][i] == '*');
	}

	for (int i = 1; i < n; i++)
		for (int j = 1; j < n; j++)
			pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + (grid[i][j] == '*');

	while (q--) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		x1--; y1--; x2--; y2--;
		int res = pref[x2][y2];
		if (x1) { res -= pref[x1 - 1][y2]; }
		if (y1) { res -= pref[x2][y1 - 1]; }
		if (x1 && y1) { res += pref[x1 - 1][y1 - 1]; }
		cout << res << '\n';
	}
}