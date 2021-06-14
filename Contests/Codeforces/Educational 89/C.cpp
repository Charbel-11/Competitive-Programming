#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int n, m;
vector<vector<int>> grid;
vector<pair<int, int>> dist;

void bfs1(int i, int j) {
	vector<vector<bool>> visited(n, vector<bool>(m, 0));
	
	queue<pair<pair<int, int>, int>> Q; Q.push({ { i,j }, 0 }); visited[i][j] = 1;

	int curD = 0;
	while (!Q.empty()) {
		int cI = Q.front().first.first, cJ = Q.front().first.second; 
		curD = max(curD, Q.front().second);
		Q.pop();
		if (curD >= dist.size()) { break; }
		(grid[cI][cJ] ? dist[curD].first : dist[curD].second)++;
		if (cI < n - 1 && !visited[cI + 1][cJ]) { 
			visited[cI + 1][cJ] = 1;
			Q.push({ { cI + 1,cJ }, curD + 1 }); 
		}
		if (cJ < m - 1 && !visited[cI][cJ + 1]) { 
			visited[cI][cJ + 1] = 1; 
			Q.push({ { cI, cJ + 1 }, curD + 1 }); 
		}
	}
}

void bfs2(int i, int j) {
	vector<vector<bool>> visited(n, vector<bool>(m, 0));

	queue<pair<pair<int, int>, int>> Q; Q.push({ { i,j }, 0 }); visited[i][j] = 1;

	int curD = 0;
	while (!Q.empty()) {
		int cI = Q.front().first.first, cJ = Q.front().first.second;
		curD = max(curD, Q.front().second);
		Q.pop();
		if (curD >= dist.size()) { break; }
		(grid[cI][cJ] ? dist[curD].first : dist[curD].second)++;
		if (cI > 0 && !visited[cI - 1][cJ]) {
			visited[cI - 1][cJ] = 1;
			Q.push({ { cI - 1,cJ }, curD + 1 });
		}
		if (cJ > 0 && !visited[cI][cJ - 1]) {
			visited[cI][cJ - 1] = 1;
			Q.push({ { cI, cJ - 1 }, curD + 1 });
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		cin >> n >> m;
		grid.clear(); grid.resize(n, vector<int>(m));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> grid[i][j];
			}
		}
		dist.clear(); dist.resize((n + m - 1) / 2, { 0,0 });
		bfs1(0, 0); bfs2(n - 1, m - 1);

		int res = 0;
		for (int i = 0; i < dist.size(); i++) {
			res += min(dist[i].first, dist[i].second);
		}

		cout << res << '\n';
	}
}