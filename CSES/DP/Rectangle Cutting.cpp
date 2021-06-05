#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int a, b; cin >> a >> b;
	vector<vector<int>> dp(a, vector<int>(b, a*b + 2));
	for (int i = 0; i < min(a, b); i++) { dp[i][i] = 0; }
	
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			for(int k = 0; k < i; k++)
				dp[i][j] = min(dp[i][j], 1 + dp[k][j] + dp[i - k - 1][j]);
			
			for (int k = 0; k < j; k++)
				dp[i][j] = min(dp[i][j], 1 + dp[i][k] + dp[i][j - k - 1]);
		}
	}

	cout << dp[a-1][b-1] << '\n';
}