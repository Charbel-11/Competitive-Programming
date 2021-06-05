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

string s;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
bool visited[7][7];

int numGrids(int i, int j, int it) {
	if (it == 48) { return 1; }
	if (i == 6 && j == 0) { return 0; }
	if ((j == 6 || visited[i][j + 1]) && (j == 0 || visited[i][j - 1]) && i > 0 && i < 6 && !visited[i - 1][j] && !visited[i + 1][j]) return 0;
	if ((j == 0 || visited[i][j - 1]) && (j == 6 || visited[i][j + 1]) && i > 0 && i < 6 && !visited[i - 1][j] && !visited[i + 1][j]) return 0;
	if ((i == 6 || visited[i + 1][j]) && (i == 0 || visited[i - 1][j]) && j > 0 && j < 6 && !visited[i][j - 1] && !visited[i][j + 1]) return 0;
	if ((i == 0 || visited[i - 1][j]) && (i == 6 || visited[i + 1][j]) && j > 0 && j < 6 && !visited[i][j - 1] && !visited[i][j + 1]) return 0;

	int ans = 0;
	if (s[it] != '?') {
		int ni = i, nj = j;
		if (s[it] == 'U') { ni--; }
		else if (s[it] == 'D') { ni++; }
		else if (s[it] == 'L') { nj--; }
		else { nj++; }

		if (ni < 0 || nj < 0 || ni >= 7 || nj >= 7 || visited[ni][nj]) { return 0; }
		visited[ni][nj] = 1;
		ans = numGrids(ni, nj, it + 1);
		visited[ni][nj] = 0;

		return ans;
	}

	for (int k = 0; k < 4; k++) {
		int ni = i + dx[k], nj = j + dy[k];
		if (ni < 0 || nj < 0 || ni >= 7 || nj >= 7 || visited[ni][nj]) { continue; }

		visited[ni][nj] = 1;
		ans += numGrids(ni, nj, it + 1);
		visited[ni][nj] = 0;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> s; visited[0][0] = 1;
	cout << numGrids(0, 0, 0) << '\n';
}