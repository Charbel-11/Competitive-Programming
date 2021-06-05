#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int vis[8][8];
int dx[] = { 1,1,2,2,-1,-1,-2,-2 }, dy[] = { 2,-2,1,-1,2,-2,1,-1 };

bool valid(int x, int y) {
	return x >= 0 && y >= 0 && x < 8 && y < 8 && !vis[x][y];
}

int deg(int x, int y) {
	int ans = 0;
	for (int i = 0; i < 8; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		ans += valid(nx, ny);
	}
	return ans;
}

void dfs(int x, int y, int cnt) {
	vis[x][y] = cnt;
	if (cnt == 64) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				cout << vis[i][j] << ' ';
			}
			cout << '\n';
		}
		exit(0);
	}

	vector<pair<int, int>> nxtMoves;
	for (int i = 0; i < 8; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (valid(nx, ny)) { nxtMoves.push_back({ nx, ny }); }
	}

	auto comp = [&](const pair<int, int>& p1, const pair<int, int>& p2) {
		return deg(p1.first, p1.second) < deg(p2.first, p2.second); 
	};
	sort(nxtMoves.begin(), nxtMoves.end(), comp);

	for (auto& p : nxtMoves) { dfs(p.first, p.second, cnt + 1); }
	vis[x][y] = 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int x, y; cin >> y >> x; x--; y--;
	dfs(x, y, 1);
}