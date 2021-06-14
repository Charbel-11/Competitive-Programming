#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int DP[2002][2002];
int n, h, l, r;
vector<int> a;

int maxGood(int i, int curH) {
	if (i >= n) { 
		if (curH >= l && curH <= r) { return 1; }
		return 0;
	}
	if (DP[i][curH] != -1) { return DP[i][curH]; }

	int c1 = maxGood(i + 1, (curH + a[i]) % h);
	int c2 = maxGood(i + 1, (curH + a[i] - 1) % h);
	int res = max(c1, c2);

	if (i > 0 && curH >= l && curH <= r) {
		res++;
	}

	return DP[i][curH] = res;
}

void resetDP() {
	for (int i = 0; i < 2002; i++)
		for (int j = 0; j < 2002; j++)
			DP[i][j] = -1;
}

int main() {
	cin >> n >> h >> l >> r;
	a.resize(n);
	for (auto &x : a) { cin >> x; }

	resetDP();

	cout << maxGood(0, 0) << endl;
}