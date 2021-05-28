//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2022
#include <iostream>
#include <string>

using namespace std;

string s1, s2, f;
int DP[62][62][62];
const int mod = 10007;

int numOfWays(int i, int j, int cur) {
	if (DP[i][j][cur] != -1) { return DP[i][j][cur]; }
	if (cur >= f.size()) { return DP[i][j][cur] = 1; }

	int tot = 0;
	for (int a = i; a < s1.size(); a++) {
		if (f[cur] == s1[a]) { tot += numOfWays(a + 1, j, cur + 1); tot %= mod; }
	}
	for (int a = j; a < s2.size(); a++) {
		if (f[cur] == s2[a]) { tot += numOfWays(i, a + 1, cur + 1); tot %= mod; }
	}

	DP[i][j][cur] = tot % mod; return DP[i][j][cur];
}

void resetDP() {
	for (int i = 0; i < 62; i++)
		for (int j = 0; j < 62; j++)
			for (int k = 0; k < 62; k++)
				DP[i][j][k] = -1;
}

int main() {
	int T; cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> s1 >> s2 >> f;
		resetDP();

		int ways = numOfWays(0, 0, 0);
		cout << ways << endl;
	}
}