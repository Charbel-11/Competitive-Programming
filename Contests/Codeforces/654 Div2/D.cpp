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
		int n, k; cin >> n >> k;
		vector<vector<int>> grid(n, vector<int>(n, 0));

		int i = 0, j = 0;
		while (k--) {
			grid[i][j] = 1; 
			i++; j++; i %= n; j %= n;
			if (grid[i][j]) { j++; j %= n; }
			if (grid[i][j]) { i++; i %= n; }
		}

		int maxR = 0, minR = n + 1;
		int maxC = 0, minC = n + 1;
		for (int i = 0; i < n; i++) {
			int curR = 0, curC = 0;
			for (int j = 0; j < n; j++) { curR += grid[i][j]; curC += grid[j][i]; }
			maxR = max(maxR, curR); minR = min(minR, curR);
			maxC = max(maxC, curC); minC = min(minC, curC);
		}

		int dR = maxR - minR, dC = maxC - minC;
		cout << dR * dR + dC * dC << '\n';
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) { cout << grid[i][j]; }
			cout << '\n';
		}
	}
}