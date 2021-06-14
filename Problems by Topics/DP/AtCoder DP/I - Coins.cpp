#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
vector<double> p;
double DP[3001][3001];
int N;

double probHead(int i, int heads) {
	if (i >= p.size()) {
		if (heads >= (N + 1) / 2) { return 1; }
		return 0;
	}
	if (DP[i][heads] != -1) { return DP[i][heads]; }

	double h = probHead(i + 1, heads + 1)*p[i];
	double t = probHead(i + 1, heads)*(1 - p[i]);

	DP[i][heads] = h + t;
	return DP[i][heads];
}

int main() {
	cin >> N;
	p.resize(N);
	for (auto &x : p) { cin >> x; }
	for (int i = 0; i < 3001; i++)
		for (int j = 0; j < 3001; j++)
			DP[i][j] = -1;

	cout << setprecision(9) << fixed << probHead(0, 0) << endl;
}