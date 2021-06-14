#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int N; cin >> N;
	vector<double> dp(N + 1, 0); dp[0] = 1;			//dp[i] = prob to have i heads
	double ans = 0;

	for (int i = 0; i < N; i++) {
		double curP; cin >> curP;
		//We now have to use this new coin, so for each i either we use it (hence with i-1 other coins) or we don't (hence with i)
		for (int j = N; j >= 0; j--)
			dp[j] = (j == 0 ? 0 : dp[j - 1] * curP) + dp[j] * (1 - curP);
	}

	for (int i = (N + 1) / 2; i <= N; i++) { ans += dp[i]; }

	cout << setprecision(9) << fixed << ans << endl;
}