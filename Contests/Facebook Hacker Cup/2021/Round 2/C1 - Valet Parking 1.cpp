#include <iostream>
#include <string>
#include <map>
#include <set>
#include <stack>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int findMinMoves(int r, int c, int k, vector<string>& grid) {
	vector<int> above(c, 0);
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < c; j++) {
			if (grid[i][j] == 'X') { above[j]++; }
		}
	}

	int ans = 0;
	vector<bool> cur(c, 0);
	for (int j = 0; j < c; j++) {
		if (grid[k][j] == 'X') { ans++; cur[j] = 1; }
	}

	vector<stack<int>> belowDist(c);
	for (int i = r - 1; i >= k + 1; i--) {
		for (int j = 0; j < c; j++) {
			if (grid[i][j] == 'X') {
				belowDist[j].push(i - k);
			}
		}
	}

	int depth = k, movesUp = 0;
	for (int i = k; i < r; i++) {
		movesUp++; 
		int curAns = movesUp; 
		for (int j = 0; j < c; j++) {
			if (above[j] == depth) {
				if (cur[j]) { curAns++; }
				else if (!belowDist[j].empty() && belowDist[j].top() == movesUp){
					cur[j] = 1; curAns++;
					belowDist[j].pop();
				}
			}
			else if (above[j] < depth) {
				if (cur[j]) { above[j]++; }

				if (belowDist[j].empty() || belowDist[j].top() != movesUp) {
					cur[j] = 0;
				}
				else {
					cur[j] = 1; curAns++;
					belowDist[j].pop();
				}
			}
		}
		ans = min(ans, curAns);
	}

	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		int r, c, k; ifs >> r >> c >> k; k--;
		vector<string> grid(r); for (auto& s : grid) { ifs >> s; }

		int ans = c;
		ans = min(ans, findMinMoves(r, c, k, grid));
		reverse(grid.begin(), grid.end());
		ans = min(ans, findMinMoves(r, c, r - k - 1, grid));

		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}