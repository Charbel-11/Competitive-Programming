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

ll choose[510][510];
void fillComb() {
	int limit = 510;	
	for (int i = 0; i < limit; i++) { choose[i][i] = 1; choose[i][0] = 1; }
	for (int i = 1; i < limit; i++)
		for (int j = 1; j < i; j++)
			choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % mod;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s; int n = s.size();
	vector<vector<ll>> dp(n, vector<ll>(n, 0));
	fillComb();

	for (int i = 0; i < n - 1; i++) { 
		if (s[i] == s[i + 1]) { dp[i][i + 1] = 1; } 
	}

	for (int l = 3; l < n; l += 2) {
		for (int i = 0; i + l < n; i++) {
			int j = i + l;
			for (int k = i + 1; k <= j; k += 2) {
				if (s[i] == s[k]) {
					int sizeL = (k - i + 1) / 2, sizeR = (j - (k + 1) + 1) / 2;
					ll numP = choose[sizeL + sizeR][sizeL];

					ll curWays = 1;
					if (i + 1 < k - 1) { curWays *= dp[i + 1][k - 1]; }
					if (k + 1 < j) { curWays *= dp[k + 1][j]; }
					curWays %= mod;

					curWays *= numP; curWays %= mod;
					dp[i][j] += curWays; dp[i][j] %= mod;
				}
			}
		}
	}

	cout << dp[0][n - 1] << '\n';
}