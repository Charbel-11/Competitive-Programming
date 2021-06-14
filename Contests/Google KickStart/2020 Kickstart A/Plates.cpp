#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int DP[52][32][1502];
int N, K, P;

void resetDP() {
	for (int i = 0; i <= N+1; i++)
		for (int j = 0; j <= K+1; j++)
			for(int k = 0; k <= P+1; k++)
				DP[i][j][k] = -1;
}

vector<vector<int>> stacks;
int maxBeauty(int i, int j, int P) {
	if (DP[i][j][P] != -1) { return DP[i][j][P]; }
	if (P == 0) { return DP[i][j][P] = 0; }
	if (j == K) { return DP[i][j][P] = maxBeauty(i + 1, 0, P); }
	if (i == N) { return DP[i][j][P] = 0; }
	if (K - j > P) { return DP[i][j][P] = maxBeauty(i, j + 1, P); }

	int c1 = 0, newP = P;
	for (int l = j; l < K; l++) { c1 += stacks[i][l]; newP--; }
	c1 += maxBeauty(i + 1, 0, newP);
	int c2 = maxBeauty(i, j + 1, P);

	DP[i][j][P] = max(c1, c2);
	return DP[i][j][P];
}

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		cin >> N >> K >> P;
		resetDP();

		stacks.clear(); stacks.resize(N);
		for (int i = 0; i < N; i++) {
			stacks[i].resize(K);
			for (auto &x : stacks[i]) { cin >> x; }
			reverse(stacks[i].begin(), stacks[i].end());
		}

		int res = maxBeauty(0, 0, P);
		cout << "Case #" << z + 1 << ": " << res << endl;
	}
}