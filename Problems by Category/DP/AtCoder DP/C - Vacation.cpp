#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int DP[(int)1e5 + 2][3];
vector<vector<int>> scores;

int maxHapiness(int i, int j) {
	if (DP[i][j] != -1) { return DP[i][j]; }
	if (i >= scores.size()) { return DP[i][j] = 0; }

	int c1 = maxHapiness(i + 1, (j + 1) % 3);
	int c2 = maxHapiness(i + 1, (j + 2) % 3);

	DP[i][j] = max(c1, c2) + scores[i][j];
	return DP[i][j];
}

int main() {
	for (int i = 0; i < (int)1e5 + 2; i++)
		for (int j = 0; j < 3; j++)
			DP[i][j] = -1;

	int N; cin >> N;
	scores.resize(N);
	for (auto &x : scores) { x.resize(3); cin >> x[0] >> x[1] >> x[2]; }

	cout << max(maxHapiness(0, 0), max(maxHapiness(0, 1), maxHapiness(0, 2))) << endl;
}