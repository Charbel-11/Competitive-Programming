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
int n, m;
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> n >> m >> t;
	vector<vector<bool>> grid(n, vector<bool>(m));
	vector<vector<int>> change(n, vector<int>(m, -1)); vector<pair<int, int>> toCheck;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		for (int j = 0; j < m; j++) { grid[i][j] = (s[j] == '1'); }
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 4; k++) {
				int ni = i + dx[k], nj = j + dy[k];
				if (ni < 0 || nj < 0 || ni >= n || nj >= m) { continue; }
				if (grid[i][j] == grid[ni][nj]) { change[i][j] = 1; break; }
			}
			if (change[i][j] != -1) { toCheck.push_back({ i,j }); }
		}
	}

	while (!toCheck.empty()) {
		vector<pair<int, int>> toCheckNext;
		for (auto &p : toCheck) {
			int i = p.first, j = p.second;
			for (int k = 0; k < 4; k++) {
				int ni = i + dx[k], nj = j + dy[k];
				if (ni < 0 || nj < 0 || ni >= n || nj >= m) { continue; }
				if (change[ni][nj] == -1) { 
					change[ni][nj] = change[i][j] + 1;
					toCheckNext.push_back({ ni,nj });
				}
			}
		}
		toCheck = toCheckNext;
	}

	while (t--) {
		int i, j; cin >> i >> j; i--; j--;
		ll p; cin >> p;
		
		if (p < change[i][j] || change[i][j] == -1) { cout << grid[i][j] << endl; }
		else {
			p -= change[i][j];
			cout << (p % 2 == 0 ? !grid[i][j] : grid[i][j]) << endl;
		}
	}
}