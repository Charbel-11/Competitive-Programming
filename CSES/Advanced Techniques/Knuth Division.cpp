#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;

ll dp[5002][5002];
int choice[5002][5002];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<ll> x(n); for (auto& xx : x) { cin >> xx; }

	for (int i = 0; i < n; i++) { choice[i][i] = i; }
	for (int i = 1; i < n; i++) { x[i] += x[i - 1]; }

	for (int i = n - 2; i >= 0; i--) {
		for (int j = i + 1; j < n; j++) {
			dp[i][j] = LLONG_MAX;
			ll curSum = x[j] - (i ? x[i - 1] : 0);
			for (int k = choice[i][j - 1]; k <= min(j - 1, choice[i + 1][j]); k++) {
				ll cur = curSum + dp[i][k] + dp[k + 1][j];
				if (cur < dp[i][j]) { dp[i][j] = cur; choice[i][j] = k; }
			}
		}
	}

	cout << dp[0][n - 1] << '\n';
}
