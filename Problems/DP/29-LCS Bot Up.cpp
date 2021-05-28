#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<vector<int>> dp;
string a, b;

void printLCS() {
	int n = a.size(), m = b.size();
	int i = 0, j = 0;
	
	while (i < n && j < n) {
		if (dp[i][j] == dp[i + 1][j + 1] + 1 && a[i] == b[j]) {
			cout << a[i];
			i++; j++;
		}
		else {
			if (dp[i][j] == dp[i + 1][j]) { i++; }
			else { j++; }
		}
	}
}

int main() {
	cin >> a >> b;
	int n = a.size(), m = b.size();
	dp.resize(n + 1, vector<int>(m + 1, -1));

	for (int i = 0; i <= n; i++) { dp[i][m] = 0; }
	for (int i = 0; i <= m; i++) { dp[n][i] = 0; }

	for (int i = n - 1; i >= 0; i--) {
		for (int j = m - 1; j >= 0; j--) {
			if (a[i] == b[j])
				dp[i][j] = 1 + dp[i + 1][j + 1];
			else 
				dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
		}
	}

	cout << dp[0][0] << endl;
	printLCS();
}