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

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string rules; cin >> rules;
	int n, m; cin >> n >> m;
	vector<string> grid(n);
	for (auto& s : grid) { cin >> s; }

	while (m--) {
		vector<string> nGrid = grid;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int adj = 0;
				for (int k = 0; k < 4; k++) {
					int ni = (i + dx[k] + n) % n;
					int nj = (j + dy[k] + n) % n;
					adj += grid[ni][nj] == '1';
				}
				if (grid[i][j] == '0' && rules[adj] == '1') { nGrid[i][j] = '1'; }
				else if (grid[i][j] == '1' && rules[adj + 6] == '1') { nGrid[i][j] = '1'; }
				else { nGrid[i][j] = '0'; }
			}
		}
		swap(grid, nGrid);
	}

	for (auto& s : grid) { cout << s << '\n'; }
}