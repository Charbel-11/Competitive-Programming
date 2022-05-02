#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m, q; cin >> n >> m >> q;
	vector<vector<bool>> grid(n, vector<bool>(m, false));
	int numIcons = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c; cin >> c;
			if (c == '*') { grid[i][j] = true; numIcons++; }
		}
	}

	vector<vector<bool>> targetGrid(n, vector<bool>(m, false));
	int curCost = 0, lastI = 0, lastJ = 0;
	if (numIcons != 0) {
		for (int j = 0; j < m; j++) {
			for (int i = 0; i < n; i++) {
				targetGrid[i][j] = true;
				if (!grid[i][j]) { curCost++; }

				numIcons--;
				if (numIcons == 0) { lastI = i; lastJ = j; break; }
			}
			if (numIcons == 0) { break; }
		}
	}
	else {
		lastI = -1; lastJ = 0;
	}

	while (q--) {
		int i, j; cin >> i >> j; i--; j--;

		if (grid[i][j]) {
			targetGrid[lastI][lastJ] = false;
			if (!grid[lastI][lastJ]) { curCost--; }

			grid[i][j] = false;
			if (targetGrid[i][j]) { curCost++; }

			lastI--;
			if (lastI == -1) { lastI = n - 1; lastJ--; }
		}
		else {
			lastI++;
			if (lastI == n) { lastI = 0; lastJ++; }

			targetGrid[lastI][lastJ] = true;
			if (!grid[lastI][lastJ]) { curCost++; }

			grid[i][j] = true;
			if (targetGrid[i][j]) { curCost--; }
		}

		cout << curCost << '\n';
	}
}