//https://codeforces.com/contest/1341/problem/E

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
typedef long long ll;
const ll INF = 1ll << 60;

int safe, mod;
ll dist[10002][1002];
bool visited[10002][1002];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<int> d(m);
	for (auto &x : d) { cin >> x; }
	sort(d.begin(), d.end());
	d.erase(unique(d.begin(), d.end()), d.end());
	m = d.size();
	int g, r; cin >> g >> r;

	safe = m; mod = g;

	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < safe; i++)
		for (int j = 0; j < mod; j++)
			dist[i][j] = INF;

	deque<pair<int, int>> dq;
	dist[0][0] = 0; dq.push_back({ 0,0 });

	while (!dq.empty()) {
		pair<int, int> cur = dq.front(); dq.pop_front();
		while (visited[cur.first][cur.second] && !dq.empty()) { cur = dq.front(); dq.pop_front(); }
		if (visited[cur.first][cur.second]) { break; } visited[cur.first][cur.second] = 1;

		int curS = cur.first, curM = cur.second;

		for (int i = curS + 1; i < m; i++) {
			int diff = d[i] - d[curS];
			if (diff + curM > g) { break; }
			int newM = (diff + curM) % g;
			if (visited[i][newM]) { break; }

			int w = (newM ? 0 : g + r);
			if (dist[i][newM] > dist[curS][curM] + w) {
				dist[i][newM] = dist[curS][curM] + w;
				if (w) { dq.push_back({ i, newM }); }
				else { dq.push_front({ i, newM }); }
			}
		}

		for (int i = curS - 1; i >= 0; i--) {
			int diff = d[curS] - d[i];
			if (diff + curM > g) { break; }
			int newM = (diff + curM) % g;
			if (visited[i][newM]) { break; }

			int w = (newM ? 0 : g + r);
			if (dist[i][newM] > dist[curS][curM] + w) {
				dist[i][newM] = dist[curS][curM] + w;
				if (w) { dq.push_back({ i, newM }); }
				else { dq.push_front({ i, newM }); }
			}
		}
	}

	ll ans = INF;
	for (int i = 0; i < g; i++) {
		ll curD = dist[m - 1][i];
		if (curD == INF) { continue; }

		if (i == 0) { curD -= r; }
		else { curD += i; }
		ans = min(ans, curD);
	}

	cout << (ans == INF ? -1 : ans) << '\n';
}