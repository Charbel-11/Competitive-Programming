#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;
vector<string> grid;
vector<vector<pair<int, int>>> parent;

int n, m; 
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool check(int i, int j) {
	return (i >= 0 && j >= 0 && i < n && j < m);
}

bool dfs(int i, int j) {
	queue<pair<int, int>> Q; Q.push({ i,j });
	grid[i][j] = '#';

	while (!Q.empty()) {
		i = Q.front().first, j = Q.front().second; Q.pop();

		for (int k = 0; k < 4; k++) {
			int ni = i + dx[k], nj = j + dy[k];
			if (!check(ni, nj) || grid[ni][nj] == '#') { continue; }
			parent[ni][nj] = { i,j }; Q.push({ ni, nj });
			if (grid[ni][nj] == 'B') { return true; }
			grid[ni][nj] = '#';
		}
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> m; parent.resize(n, vector<pair<int, int>>(m));
	grid.resize(n); for (auto &x : grid) { cin >> x; }
	int si, sj, ei, ej;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 'A') { si = i; sj = j; }
			else if (grid[i][j] == 'B') { ei = i; ej = j; }
		}
	}

	if (dfs(si, sj)) {
		cout << "YES\n";
		string ans = "";
		int cI = ei, cJ = ej;
		while (cI != si || cJ != sj) {
			int pI = parent[cI][cJ].first, pJ = parent[cI][cJ].second;

			if (pI == cI - 1) { ans.push_back('D'); }
			else if (pI == cI + 1) { ans.push_back('U'); }
			else if (pJ == cJ - 1) { ans.push_back('R'); }
			else { ans.push_back('L'); }
			cI = pI; cJ = pJ;
		}
		reverse(ans.begin(), ans.end());
		cout << ans.size() << '\n' << ans << '\n';
	}
	else { cout << "NO\n"; }
	
}