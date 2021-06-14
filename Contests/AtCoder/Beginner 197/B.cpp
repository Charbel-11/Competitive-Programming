#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int h, w, x, y; cin >> h >> w >> x >> y; x--; y--;
	vector<string> grid(h);
	for (auto& s : grid) { cin >> s; }

	int ans = -3;
	for (int k = 0; k < 4; k++) {
		int i = x, j = y;
		while (i < h && j < w && i >= 0 && j >= 0) {
			if (grid[i][j] == '#') { break; }
			ans++; i += dx[k]; j += dy[k];
		}
	}

	cout << ans << '\n';
}