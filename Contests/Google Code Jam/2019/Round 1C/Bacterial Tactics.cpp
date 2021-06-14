#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;
vector<vector<char>> grid;
int DP[16][16][16][16];
int winM[16][16][16][16];

int mex(int i1, int i2, int j1, int j2) {
	if (i2 < i1 || j2 < j1) { return 0; }
	if (DP[i1][i2][j1][j2] != -1) { return DP[i1][i2][j1][j2]; }

	set<int> moves;
	for (int i = i1; i <= i2; i++) {
		bool OK = true; 
		for (int j = j1; j <= j2; j++) {
			if (grid[i][j] == '#') { OK = false; break; }
		}
		if (OK) {
			int nM = mex(i1, i - 1, j1, j2) ^ mex(i + 1, i2, j1, j2);
			moves.insert(nM);
			if (!nM) { winM[i1][i2][j1][j2] += (j2 - j1 + 1); }
		}
	}
	for (int j = j1; j <= j2; j++) {
		bool OK = true;
		for (int i = i1; i <= i2; i++) {
			if (grid[i][j] == '#') { OK = false; break; }
		}
		if (OK) { 
			int nM = mex(i1, i2, j1, j - 1) ^ mex(i1, i2, j + 1, j2);
			moves.insert(nM);
			if (!nM) { winM[i1][i2][j1][j2] += (i2 - i1 + 1); }
		}
	}

	int cur = 0;
	for (auto it : moves) {
		if (cur != it) { break; }
		cur++;
	}

	return DP[i1][i2][j1][j2] = cur;
}

int main() {
	int T; cin >> T;

	for (int qq = 1; qq <= T; qq++) {
		int R, C; cin >> R >> C;
		grid.clear();
		grid.resize(R);

		for (int i = 0; i < R; i++) {
			grid[i].resize(C);
			string s; cin >> s;
			for (int j = 0; j < C; j++) { grid[i][j] = s[j]; }
		}

		for (int i = 0; i < 16; i++)
			for (int j = 0; j < 16; j++)
				for (int k = 0; k < 16; k++)
					for (int l = 0; l < 16; l++) {
						DP[i][j][k][l] = -1;
						winM[i][j][k][l] = 0;
					}

		int mm = mex(0, R - 1, 0, C - 1);
		int ans = winM[0][R - 1][0][C - 1];
		cout << "Case #" << qq << ": " << ans << endl;
	}
}