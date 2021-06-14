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

int dp[4002][2000];
int n; int inf = 2e5;
vector<int> boats;

int minTime(int i, int wait) {
	if (dp[i][wait] != -1) { return dp[i][wait]; }
	if (wait > 60 * 30) { return inf; }
	if (i == n - 1) { return dp[i][wait] = 20; }

	int c1 = inf, c2 = inf;
	int dif = boats[i + 1] - boats[i];

	//c1: Keep it raised
	int newDif = max(0, dif - 20 - wait);
	int nWait = max(0, 20 + wait - dif);
	c1 = 20 + newDif + minTime(i + 1, nWait);

	//c2: Lower than raise
	nWait = max(0, 120 + 20 + wait - dif);

	for (int w = nWait; w < 60 * 30 + 1; w++) {
		c2 = 20 + 120 + minTime(i + 1, w);
	}

//	c2 = 20 + 120 + minTime(i + 1, nWait);

	return dp[i][wait] = min(c1, c2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	memset(dp, -1, sizeof(dp));
	cin >> n; boats.resize(n);
	for (auto &x : boats) { cin >> x; }

	int res = inf;
	for (int w = 0; w < 60 * 30 + 1; w++) {
		int cur = 60 + minTime(0, w);
		
		res = min(res, cur);
	}
	cout << res + 60 << endl;
}