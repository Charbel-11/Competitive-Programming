#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int DP[10][10][10];
string s;

int minMoves(int mod, int x, int y, int k1, int k2) {		//answ + 1
	if (DP[mod][x][y] != -2) { return DP[mod][x][y]; }
	if (mod == 0) { return DP[mod][x][y] = 0; }
	if (k1 >= 5 || k2 >= 5) { return DP[mod][x][y] = -1; }

	int c1 = -1, c2 = -1;
	if (x > 0) c1 = minMoves((mod + x) % 10, x, y, k1 + 1, k2 > 0 ? k2 - 1 : 0);
	if (y > 0) c2 = minMoves((mod + y) % 10, x, y, k1 > 0 ? k1 - 1 : 0, k2 + 1);

	if (c1 == -1 && c2 != -1) { DP[mod][x][y] = c2 + 1; }
	else if (c1 != -1 && c2 == -1) { DP[mod][x][y] = c1 + 1; }
	else if (c1 == -1 && c2 == -1) { DP[mod][x][y] = -1; }
	else { DP[mod][x][y] = c1 > c2 ? c2 + 1 : c1 + 1; }

	//	cout << start << " " << end << " " << x << " " << y << " " << c1 << " " << c2 << " " << DP[start][end][x][y] << endl;
	return DP[mod][x][y];
}

void resetDP() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
				DP[i][j][k] = -2;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> s;

	resetDP();

	int answ[10][10];
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			answ[i][j] = -2;

	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 9; j++) {
			if (answ[i][j] != -2) { continue; }
			answ[i][j] = 0;
			for (int k = 0; k < s.size() - 1; k++) {
				int end = s[k + 1] - '0';
				int start = s[k] - '0';
				int mod = (end > start) ? end - start : 10 + end - start;
				int temp = minMoves(mod, i, j, 0, 0);
				if (temp == -1) { answ[i][j] = -1; break; }
				answ[i][j] += temp - 1;
			}
			answ[j][i] = answ[i][j];
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << answ[i][j] << " ";
		}
		cout << endl;
	}
}