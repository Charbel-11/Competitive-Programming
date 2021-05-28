#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int DP[52][52];
vector<pair<int, int>> grow;			//sorted
int H, k;

int minTot(int i, int j) {
	if (i == grow.size() && j == 0) { return 0; }
	if (i == grow.size() && j > 0) { return H+1; }
	if (DP[i][j] != -1) { return DP[i][j]; }

	int c1 = grow[i].second + grow[i].first*k + minTot(i + 1, j);
	if (j == 0) { DP[i][j] = c1; return c1; }
	int c2 = (j-1)*grow[i].first + minTot(i + 1, j - 1);

	DP[i][j] = c1 > c2 ? c2 : c1;
	return DP[i][j];
}

void resetDP() {
	for (int i = 0; i < 52; i++) {
		for (int j = 0; j < 52; j++) {
			DP[i][j] = -1;
		}
	}
}

int main() {
	vector<int> init;

	char c;
	cin >> c;
	while (c != '}') {
		int a; cin >> a >> c;
		init.push_back(a);
	}
	cin >> c >> c; int n = 0;
	while (c != '}') {
		int a; cin >> a >> c;
		grow.push_back({ a, init[n] });
		n++;
	}
	cin >> c >> H;

	sort(grow.begin(), grow.end());

	k = 0;
	while (k <= n) {
		resetDP();

		int res = minTot(0, k);
		if (res <= H) {
			cout << k << endl;
			return 0;
		}

		k++;
	}

	cout << -1 << endl; 

}