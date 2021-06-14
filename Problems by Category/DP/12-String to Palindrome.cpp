//https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1680
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int DP[1003][1003];
string s;

int findOp(int i, int j) {
	if (i >= j) { return 0; }
	if (DP[i][j] != -1) { return DP[i][j]; }

	if (s[i] == s[j]) {
		DP[i][j] = findOp(i + 1, j - 1); return DP[i][j];
	}

	int a = 1 + findOp(i, j - 1);		//Add from the left or delete from the right
	int b = 1 + findOp(i + 1, j);		//Add from the right or delete from the left
	int c = 1 + findOp(i + 1, j - 1); 	//Replace one of the two letters to match the other one

	a = min(a, b); a = min(a, c);
	DP[i][j] = a; return a;
}

void resetDP() {
	for (int i = 0; i < 1003; i++)
		for (int j = 0; j < 1003; j++)
			DP[i][j] = -1;
}

int main() {
	int T; cin >> T;
	int caseN = 1;
	for (int z = 0; z < T; z++) {
		resetDP();
		cin >> s;
		int op = findOp(0, s.size() - 1);

		cout << "Case " << caseN << ": " << op << endl;
		caseN++;
	}
}