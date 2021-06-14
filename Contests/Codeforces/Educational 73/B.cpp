#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
	int n; cin >> n;

	vector<vector<char>> grid(n);
	for (auto &x : grid) { x.resize(n, 'I'); }

	queue<pair<int, int>> Q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] != 'I') { continue; }
			else { grid[i][j] = 'W'; Q.push({ i, j }); }
			while (!Q.empty()) {
				pair<int, int> cur = Q.front(); Q.pop();
				int x = cur.first, y = cur.second;
				char other = grid[x][y] == 'W' ? 'B' : 'W';

				if (x + 1 < n) {
					if (y + 2 < n && grid[x + 1][y + 2] == 'I') { grid[x + 1][y + 2] = other; Q.push({ x + 1,y + 2 }); }
					if (y - 2 >= 0 && grid[x + 1][y - 2] == 'I') { grid[x + 1][y - 2] = other; Q.push({ x + 1,y - 2 }); }
				}
				if (x - 1 >= 0) {
					if (y + 2 < n && grid[x - 1][y + 2] == 'I') { grid[x - 1][y + 2] = other; Q.push({ x - 1,y + 2 }); }
					if (y - 2 >= 0 && grid[x - 1][y - 2] == 'I') { grid[x - 1][y - 2] = other; Q.push({ x - 1,y - 2 }); }
				}
				if (y + 1 < n) {
					if (x + 2 < n && grid[x + 2][y + 1] == 'I') { grid[x + 2][y + 1] = other; Q.push({ x + 2,y + 1 }); }
					if (x - 2 >= 0 && grid[x - 2][y + 1] == 'I') { grid[x - 2][y + 1] = other; Q.push({ x - 2,y + 1 }); }
				}
				if (y - 1 >= 0) {
					if (x + 2 < n && grid[x + 2][y - 1] == 'I') { grid[x + 2][y - 1] = other; Q.push({ x + 2,y - 1 }); }
					if (x - 2 >= 0 && grid[x - 2][y - 1] == 'I') { grid[x - 2][y - 1] = other; Q.push({ x - 2,y - 1 }); }
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}
}