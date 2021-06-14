//https://www.spoj.com/problems/KATHTHI/

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
typedef long long ll;
const int INF = 1 << 30;
int r, c;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

bool check(int i, int j) {
	if (i < 0 || j < 0 || i >= r || j >= c) { return false; }
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		cin >> r >> c;
		vector<string> prison(r);
		for (auto &x : prison) { cin >> x; }

		vector<vector<bool>> visited(r, vector<bool>(c, 0));
		vector<vector<int>> dist(r, vector<int>(c, INF));
		deque<pair<int, int>> dq;
		dist[0][0] = 0; dq.push_back({ 0,0 });

		while (!dq.empty()) {
			pair<int, int> cur = dq.front(); dq.pop_front();
			while (visited[cur.first][cur.second] && !dq.empty()) { cur = dq.front(); dq.pop_front(); }
			if (visited[cur.first][cur.second]) { break; } visited[cur.first][cur.second] = 1;

			int i = cur.first, j = cur.second;

			for (int k = 0; k < 4; k++) {
				int ni = i + dx[k], nj = j + dy[k];
				if (!check(ni, nj)) { continue; }

				int w = prison[i][j] == prison[ni][nj] ? 0 : 1;
				if (visited[ni][nj] || dist[ni][nj] < dist[i][j] + w) { continue; }
				dist[ni][nj] = dist[i][j] + w;
				if (w) { dq.push_back({ ni,nj }); }
				else { dq.push_front({ ni,nj }); }
			}			
		}

		printf("%d\n", dist[r-1][c-1]);
	}
}