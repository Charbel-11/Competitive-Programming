#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector<vector<int>> dp;
string a, b;

int main() {
	cin >> a >> b;
	int n = a.size(), m = b.size();
	dp.resize(2); dp[0].resize(n + 1, -1); dp[1].resize(n + 1, 0);
	dp[0][n] = 0;

	bool col = 0;
	for (int j = m - 1; j >= 0; j--) {
		for (int i = n - 1; i >= 0; i--) {
			if (a[i] == b[j])
				dp[col][i] = 1 + dp[!col][i + 1];
			else
				dp[col][i] = max(dp[!col][i], dp[col][i + 1]);
		}
		col = !col;
	}

	cout << dp[0][0] << endl;
}