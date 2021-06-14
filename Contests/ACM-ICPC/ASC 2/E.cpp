#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("quant.in");
	ofstream ofs("quant.out");

	int n; ifs >> n;
	vector<int> x(n);
	for (auto &xx : x) { ifs >> xx; }
	int m, s; ifs >> m >> s;

	int p = 0; while ((1 << p) != m) { p++; }
	vector<vector<int>> levels(m, vector<int>(s));
	for (int i = 0; i < m; i++) {
		for (auto &xx : levels[i]) { ifs >> xx; }
	}

	vector<vector<int>> dp(n, vector<int>(m, (int)1e9 + 5));

	for (int j = 0; j < m; j++)
		for (int k = 0; k < s; k++)
			dp[n - 1][j] = min(dp[n - 1][j], abs(x[n - 1] - levels[j][k]));

	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < s; k++) {
				int curC = abs(x[i] - levels[j][k]);
				int nxt = k & ((1 << p) - 1);
				dp[i][j] = min(dp[i][j], curC + dp[i + 1][nxt]);
			}
		}
	}

	vector<int> ans; int j = 0;
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < s; k++) {
			int curC = abs(x[i] - levels[j][k]);
			int nxt = k & ((1 << p) - 1);
			if (dp[i][j] == curC + (i < n - 1 ? dp[i + 1][nxt] : 0)) { ans.push_back(k); j = nxt; break; }
		}
	}

	ofs << dp[0][0] << '\n';
	for (auto &x : ans) { ofs << x << ' '; }
	ofs << '\n';
}