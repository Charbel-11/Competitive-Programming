#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <vector>
#include <cmath>
using namespace std;

int A[30][30];
int grundyNum[30][30][30][30];
bool prime[10];

bool allPrime(int i, int j, int k, int l) {
	for (int ii = i; ii <= k; ii++) {
		for (int jj = j; jj <= l; jj++) {
			if (!prime[A[ii][jj]]) { return false; }
		}
	}
	return true;
}

int getGrundyNumber(int i, int j, int k, int l) {
	if (grundyNum[i][j][k][l] != -1) { return grundyNum[i][j][k][l]; }
	if (allPrime(i, j, k, l) || (i == k && j == l)) { grundyNum[i][j][k][l] = 0; return 0; }
	
	bool nextMoves[62];
	for (int i = 0; i < 62; i++) { nextMoves[i] = false; }

	for (int rowCut = i; rowCut < k; rowCut++) {
		int g1 = getGrundyNumber(i, j, rowCut, l);
		int g2 = getGrundyNumber(rowCut + 1, j, k, l);
		if ((g1 ^ g2) < 62) { nextMoves[g1 ^ g2] = true; }
	}

	for (int colCut = j; colCut < l; colCut++) {
		int g1 = getGrundyNumber(i, j, k, colCut);
		int g2 = getGrundyNumber(i, colCut + 1, k, l);
		if ((g1 ^ g2) < 62) { nextMoves[g1 ^ g2] = true; }
	}

	for (int ii = 0; ii < 62; ii++) {
		if (nextMoves[ii] == 0) {
			return grundyNum[i][j][k][l] = ii;
		}
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	for (int i = 2; i < 10; i++) {
		prime[i] = true;
		for (int j = 2; j < i; j++) {
			if (i % j == 0) { prime[i] = false; break; }
		}
	}

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> A[i][j];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					for (int l = 0; l < n; l++)
						grundyNum[i][j][k][l] = -1;

		int GN = getGrundyNumber(0, 0, n - 1, n - 1);
		if (GN) { cout << "First" << '\n'; }
		else { cout << "Second" << '\n'; }
	}
}