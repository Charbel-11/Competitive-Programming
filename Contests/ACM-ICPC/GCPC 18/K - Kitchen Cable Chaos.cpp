#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

double dp[65][1005][65];
int d[65];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n, g; cin >> n >> g;
	for (int i = 0; i < n; i++) {
		cin >> d[i]; d[i] -= 10;
	}

	for (int used = 0; used <= n; used++) {
		for (int rem = 0; rem <= g; rem++) {
			double temp = rem;
			temp /= (used + 1);
			if (temp < 5 || temp > 10) { temp = 11; }
			dp[n][rem][used] = temp;
		}
	}

	for (int ind = n - 1; ind >= 0; ind--) {
		for (int rem = 0; rem <= g; rem++) {
			for (int used = n; used >= 0; used--) {
				if (rem - d[ind] >= 0)
					dp[ind][rem][used] = min(dp[ind + 1][rem][used], dp[ind + 1][rem - d[ind]][used + 1]);
				else 
					dp[ind][rem][used] = dp[ind + 1][rem][used];
			}
		}
	}
	cout << setprecision(8);
	if (dp[0][g][0] > 10) { cout << "impossible\n"; }
	else { cout << 10 - dp[0][g][0] << "\n"; }
}