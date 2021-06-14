#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> a, b;
int c;
int DP[(int)2e5 + 1][2];

int minDist(int i, bool st) {
	if (DP[i][st] != -1) { return DP[i][st]; }
	if (i == 0) {
		if (st) { return DP[i][st] = 0; }
		return DP[i][st] = c;
	}

	int add = st ? a[i-1] : b[i-1];
	int c1 = minDist(i - 1, 0);
	int c2 = minDist(i - 1, 1);
	if (!st) { c2 += c; }

	DP[i][st] = min(c1, c2) + add;
	return DP[i][st];
}

void resetDP() {
	for (int i = 0; i < 2e5 + 1; i++)
		for (int j = 0; j < 2; j++)
			DP[i][j] = -1;
}

int main() {
	int n; cin >> n >> c;
	resetDP();

	a.resize(n); b.resize(n);
	for (int i = 0; i < n - 1; i++) { cin >> a[i]; }
	for (int i = 0; i < n - 1; i++) { cin >> b[i]; }

	cout << 0 << " ";
	for (int i = 1; i < n; i++) {
		cout << min(minDist(i, 0), minDist(i, 1)) << " ";
	}cout << endl;
}