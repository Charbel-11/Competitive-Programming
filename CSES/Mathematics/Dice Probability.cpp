#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, a, b; cin >> n >> a >> b;
	double* dp = new double[6 * n + 1];
	dp[0] = 1;
	for (int i = 1; i <= 6 * n; i++) { dp[i] = 0; }

	for (int i = 0; i < n; i++) {
		for (int j = 6 * n; j >= 0; j--) {
			double curS = 0;
			for (int k = j - 1; k >= max(0, j - 6); k--) {
				curS += dp[k];
			}
			dp[j] = curS / 6.0;
		}
	}

	double ans = 0;
	for (int i = a; i <= b; i++) { ans += dp[i]; }
	cout << fixed << setprecision(6) << ans << '\n';
}