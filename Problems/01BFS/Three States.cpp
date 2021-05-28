//https://codeforces.com/contest/590/problem/C

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <deque>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

const int INF = 1 << 30;
int n, m;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

bool visited[3][1002][1002];
int dist[3][1002][1002];

bool check(int i, int j) {
	if (i < 0 || j < 0 || i >= n || j >= m) { return false; }
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	vector<string> grid(n);
	for (auto &s : grid) { cin >> s; }

	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			dist[0][i][j] = dist[1][i][j] = dist[2][i][j] = INF;

	for (int c = 0; c < 3; c++) {
		deque<pair<int, int>> dq;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == c + '1') { dist[c][i][j] = 0; dq.push_front({ i,j }); }
			}
		}

		while (!dq.empty()) {
			pair<int, int> cur = dq.front(); dq.pop_front();
			while (visited[c][cur.first][cur.second] && !dq.empty()) { cur = dq.front(); dq.pop_front(); }
			if (visited[c][cur.first][cur.second]) { break; } 
			visited[c][cur.first][cur.second] = 1;

			int i = cur.first, j = cur.second;

			for (int k = 0; k < 4; k++) {
				int ni = i + dx[k], nj = j + dy[k];
				if (!check(ni, nj) || grid[ni][nj] == '#') { continue; }

				int w = grid[ni][nj] == '.';
				if (visited[c][ni][nj] || dist[c][ni][nj] < dist[c][i][j] + w) { continue; }
				dist[c][ni][nj] = dist[c][i][j] + w;
				if (w) { dq.push_back({ ni,nj }); }
				else { dq.push_front({ ni,nj }); }
			}
		}
	}

	int ans = n * m + 2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int d1 = dist[0][i][j], d2 = dist[1][i][j], d3 = dist[2][i][j];
			if (d1 == INF || d2 == INF || d3 == INF) { continue; }
			ans = min(ans, d1 + d2 + d3 - 2 * (grid[i][j] == '.'));
		}
	}

	if (ans == n * m + 2) { cout << -1 << '\n'; }
	else { cout << ans << '\n'; }
}