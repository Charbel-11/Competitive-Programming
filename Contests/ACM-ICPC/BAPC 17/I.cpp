#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int p, q;
int DP[102][102][2][2];

//b is 1 if top left is black
int maxDiff(int p, int q, bool b, bool t) {
	if (DP[p][q][b][t] != -1) { return DP[p][q][b][t]; }
	if (p == 0 || q == 0) { return 0; }

	int finalDiff = -INT_MAX;
	//Remove col
	if (t) {
		//q num of cols
		for (int i = 1; i <= q; i++) {
			int diff = 0;
			if (i % 2 && p % 2) {
				if (b) { diff++; }
				else { diff--; }
			}

			if (i % 2) { diff -= maxDiff(p, q - i, !b, !t); }
			else { diff -= maxDiff(p, q - i, b, !t); }

			finalDiff = max(diff, finalDiff);
		}
	}
	//Remove rows
	else {
		for (int i = 1; i <= p; i++) {
			int diff = 0;
			if (i % 2 && q % 2) {
				if (b) {
					if (p % 2) { diff++; }
					else { diff--; }
				}
				else {
					if (p % 2) { diff--; }
					else { diff++; }
				}
			}

			diff -= maxDiff(p - i, q, b, !t);
			finalDiff = max(diff, finalDiff);
		}
	}

	return DP[p][q][b][t] = finalDiff;
}

void resetDP() {
	for (int i = 0; i < 102; i++)
		for (int j = 0; j < 102; j++)
			for (int k = 0; k < 2; k++)
				for(int t = 0; t < 2; t++)
					DP[i][j][k][t] = -1;
}

int main() {
	cin >> p >> q;
	resetDP();

	cout << maxDiff(p, q, 1, 1) << endl;
}