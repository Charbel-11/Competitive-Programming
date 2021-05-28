//https://code.google.com/codejam/contest/188266/dashboard#s=p2

#include <iostream>
#include <string>
using namespace std;

double DP[42][1000];
long long comb[42][42];
double proba[42];
int C, N;

//A choose B
void fillComb() {
	for (int i = 0; i < 42; i++) { comb[i][i] = 1; comb[i][0] = 1; }

	for (int i = 1; i < 42; i++)
		for (int j = 1; j < i; j++)
			comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
}

double expectedVal(int foundN, int packsUsed, int approx) {
	if (C <= N) { return 1; }
	if (C == foundN) { return packsUsed; }
	if (DP[foundN][packsUsed] != -1) { return DP[foundN][packsUsed]; }

	if (packsUsed == 0) {
		DP[foundN][packsUsed] = expectedVal(N, 1, 0);
		return DP[foundN][packsUsed];
	}

	double expected = 0;

	//i represent the number of found cards (from what is not yet found) in the next draw
	for (int i = 1; i < N + 1; i++) {
		if (i > C - foundN) { break; }

		double prob = double(comb[C - foundN][i] * comb[foundN][N - i]) / comb[C][N];

		//expectedVal will return the product of probabilities with the final num of packsUsed
		expected += prob * expectedVal(foundN + i, packsUsed + 1, 0);
	}

	//If we get the same cards we got before
	if (approx < 900) {
		if (proba[foundN] == -1) {
			proba[foundN] = double(comb[foundN][N]) / comb[C][N];
		}
		expected += proba[foundN] * expectedVal(foundN, packsUsed + 1, approx + 1);
	}

	DP[foundN][packsUsed] = expected; return expected;
}

void resetDP() {
	for (int i = 0; i < 42; i++) {
		proba[i] = -1;
		for (int j = 0; j < 1000; j++) {
			DP[i][j] = -1;
		}
	}
}

int main() {
	fillComb();

	int testCases; cin >> testCases;

	int caseN = 1;
	for (int i = 0; i < testCases; i++) {
		cin >> C >> N;

		resetDP();
		double ev = expectedVal(0, 0, 0);
		cout << "Case #" << caseN << ": " << ev << endl;
		caseN++;
	}
}