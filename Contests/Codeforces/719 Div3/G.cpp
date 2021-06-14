#include <iostream>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF = 1e17;

int n, m;
ll w;
vector<vector<ll>> grid;

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

vector<vector<ll>> bfs(int si, int sj) {
	vector<vector<ll>> d(n, vector<ll>(m, INF));
	queue<pair<int, int>> Q; vector<vector<bool>> vis(n, vector<bool>(m, 0));
	vis[si][sj] = 1; Q.push({ si, sj }); d[si][sj] = 0;

	while (!Q.empty()) {
		auto p = Q.front(); Q.pop();
		int curI = p.first, curJ = p.second;

		for (int k = 0; k < 4; k++) {
			int ni = curI + dx[k], nj = curJ + dy[k];
			if (ni < 0 || nj < 0 || ni >= n || nj >= m) { continue; }
			if (vis[ni][nj] || grid[ni][nj] == -1) { continue; }
			vis[ni][nj] = true; d[ni][nj] = d[curI][curJ] + w;
			Q.push({ ni, nj });
		}
	}

	return move(d);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> m >> w;
	grid.resize(n, vector<ll>(m));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> grid[i][j];
	
	vector<vector<ll>> distS = bfs(0, 0), distD = bfs(n - 1, m - 1);
	ll ans = distS[n - 1][m - 1];

	ll minPortalS = INF, minPortalD = INF;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] <= 0) { continue; }
			if (distS[i][j] < INF) {
				ll curC = grid[i][j] + distS[i][j];
				if (curC < minPortalS) { minPortalS = curC; }
			}
			if (distD[i][j] < INF) {
				ll curC = grid[i][j] + distD[i][j];
				if (curC < minPortalD) { minPortalD = curC; }
			}
		}
	}
	ans = min(ans, minPortalS + minPortalD);

	if (ans >= INF) { cout << -1 << '\n'; }
	else { cout << ans << '\n'; }
}
