#include <iostream>
#include <string>
#include <vector>
using namespace std;

int DP[1003][33]; int n;
vector<int> prices;
vector<int> weights;
vector<int> maxCap;

int maxVal(int maxCap, int i) {
	if (i >= n) { return 0; }
	if (DP[i][maxCap] != -1) { return DP[i][maxCap]; }

	int a = 0, b = 0;
	if (maxCap >= weights[i]) { a = prices[i] + maxVal(maxCap - weights[i], i + 1); }
	b = maxVal(maxCap, i + 1);

	DP[i][maxCap] = (a > b) ? a : b; return DP[i][maxCap];
}

void resetDP() {
	for (int i = 0; i < 1003; i++)
		for (int j = 0; j < 33; j++)
			DP[i][j] = -1;
}

int main() {
	int T; cin >> T;
	for (int z = 0; z < T; z++) {
		resetDP(); cin >> n;
		prices.resize(n); weights.resize(n);
		for (int i = 0; i < n; i++) { cin >> prices[i] >> weights[i]; }
		int numOfPeople; cin >> numOfPeople;
		maxCap.resize(numOfPeople); for (auto &x : maxCap) { cin >> x; }

		int tot = 0;
		for (int i = 0; i < numOfPeople; i++) { int cur = maxVal(maxCap[i], 0); tot += cur; }
		cout << tot << endl;
	}
}