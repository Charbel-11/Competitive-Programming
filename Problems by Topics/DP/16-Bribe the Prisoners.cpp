//https://code.google.com/codejam/contest/189252/dashboard
#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> prisPos;
int DP[102][102];

int coinNeeded(int p1, int p2) {
	if (p1 > p2) { return 0; }
	if (DP[p1][p2] != -1) { return DP[p1][p2]; }

	int minCoins = INT_MAX;
	for (int i = p1; i <= p2; i++) {
		int l = coinNeeded(p1, i - 1); int r = coinNeeded(i + 1, p2);
		int curC = l + r + prisPos[p2 + 1] - prisPos[p1 - 1] - 2;

		minCoins = min(minCoins, curC);
	}

	DP[p1][p2] = minCoins; return minCoins;
}

void resetDP() {
	for (int i = 0; i < 102; i++)
		for (int j = 0; j < 102; j++)
			DP[i][j] = -1;
}

int main() {
	int T; cin >> T;

	for (int i = 0; i < T; i++) {
		resetDP();
		int P, Q; cin >> P >> Q;

		prisPos.resize(Q + 2); prisPos[0] = 0; prisPos[Q + 1] = P + 1;	//P+1 is such that P is relevant, 0 such that 1 is relevant
		for (int j = 1; j <= Q; j++) { cin >> prisPos[j]; }

		int res = coinNeeded(1, Q);
		cout << "Case #" << i + 1 << ": " << res << endl;
	}
}