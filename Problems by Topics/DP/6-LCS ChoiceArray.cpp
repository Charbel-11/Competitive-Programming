//bcacbcabbaccbab
//bccabccbbabacbc

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int DP[1002][1002];
int Choice[1002][1002];
string A, B;

int LCS(int i, int j) {
	if (i >= A.size() || j >= B.size()) { return 0; }
	if (DP[i][j] != -1) { return DP[i][j]; }

	int res;
	if (A[i] == B[j]) { res = 1 + LCS(i + 1, j + 1); Choice[i][j] = 1; }
	else {
		int c1 = LCS(i + 1, j); int c2 = LCS(i, j + 1);
		if (c1 > c2) { res = c1; Choice[i][j] = 2; }
		else { res = c2; Choice[i][j] = 3; }
	}

	DP[i][j] = res; return res;
}

void resetDP() {
	for (int i = 0; i < 1002; i++)
		for (int j = 0; j < 1002; j++) {
			DP[i][j] = -1; Choice[i][j] = -1;
		}
}

void printChoice() {
	int i = 0, j = 0;
	while (i < A.size() && j < B.size()) {
		if (Choice[i][j] == 1) { cout << A[i]; i++; j++; }
		else if (Choice[i][j] == 2) { i++; }
		else { j++; }
	}
}

int main() {
	A = ""; B = "";
	while (getline(cin, A)) {
		getline(cin, B);
		resetDP();

		cout << LCS(0, 0) << endl; printChoice();
	}
}