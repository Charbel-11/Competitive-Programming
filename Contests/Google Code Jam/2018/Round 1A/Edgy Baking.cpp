#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef long long ll;
int N; double P;

double hyp(ll x, ll y) {
	return sqrt(x * x + y * y);
}

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		cin >> N >> P;

		double perimeter = 0;
		vector<int> low(N);
		vector<double> range(N); double lowSum = 0.0;
		for (int i = 0; i < N; i++) {
			ll W, H; cin >> W >> H;
			low[i] = 2 * min(W, H);

			perimeter += 2 * (W + H);
			range[i] = 2 * hyp(W, H) - low[i];
			lowSum += low[i];
		}

		P -= perimeter; lowSum = min(lowSum, P);	//Shouldn't reach any additional value > P
		vector<double> DP(lowSum + 1, -1);

		DP[0] = 0;
		for (int i = 0; i < N; i++) {
			for (int j = lowSum; j >= low[i]; j--) {
				if (DP[j - low[i]] > -1)
					DP[j] = max(DP[j], DP[j - low[i]] + range[i]);
			}
		}

		double ans = 0;
		for (int j = 0; j <= lowSum; j++) {
			if (DP[j] != -1) ans = max(ans, min(DP[j] + j, P));
		}

		cout << "Case #" << z + 1 << ": " << setprecision(7) << ans + perimeter << endl;
	}
}