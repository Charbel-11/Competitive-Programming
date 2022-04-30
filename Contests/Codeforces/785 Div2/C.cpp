#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int N = 4 * 10000 + 10;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	vector<int> palindromes;
	for (int i = 1; i <= 9; i++) {
		palindromes.push_back(i);
		palindromes.push_back(i * 10 + i);
	}

	for (int i = 1; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			palindromes.push_back(i * 100 + j * 10 + i);
			palindromes.push_back(i * 1000 + j * 100 + j * 10 + i);
		}
	}

	for (int i = 1; i <= 3; i++) {
		for (int j = 0; j <= 9; j++) {
			for (int k = 0; k <= 9; k++) {
				palindromes.push_back(i * 10000 + j * 1000 + k * 100 + j * 10 + i);
			}
		}
	}

	sort(palindromes.begin(), palindromes.end());
	int m = palindromes.size();

	vector<vector<ll>> dp(N, vector<ll>(m + 1, 0));
	dp[0][0] = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < m; j++) {
			int curP = palindromes[j];
			if (j > 0) { dp[i][j] += dp[i][j - 1]; dp[i][j] %= mod; }
			if (i >= curP) { dp[i][j] += dp[i - curP][j]; dp[i][j] %= mod; }
		}
	}
	
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		cout << dp[n][m - 1] << '\n';
	}
}