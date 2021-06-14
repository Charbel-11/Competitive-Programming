//https://code.google.com/codejam/contest/188266/dashboard#s=p2

#include <iostream>
#include <string>
#include <vector>
using namespace std;

long long comb[42][42];

//A choose B
double choose(int A, int B) {
	if (A == B || B == 0) {
		return 1;
	}
	if (comb[A][B] != -1) { return comb[A][B]; }

	long long p1 = choose(A - 1, B - 1);
	long long p2 = choose(A - 1, B);

	comb[A][B] = p1 + p2;
	return comb[A][B];
}

void resetComb() {
	for (int i = 0; i < 42; i++) {
		for (int j = 0; j < 42; j++) {
			comb[i][j] = -1;
		}
	}
}

int main() {
	resetComb();

	int testCases;
	cin >> testCases;

	int caseN = 1;
	for (int i = 0; i < testCases; i++) {
		int C, N;
		cin >> C >> N;

		double prob[42][42];
		vector<double> exp(C + 1, 0);			//Expected numbers of pack to get to C starting with i

		for (int i = N; i < C; i++) {				//prob to get j new knowing that we have i
			for (int j = 0; j <= N; j++) {
				if (i + j > C) {
					prob[j][i] = 0;
				}
				prob[j][i] = choose(C - i, j) * choose(i, N - j) / choose(C, N);
			}
		}
		for (int i = 0; i <= N; i++) {
			prob[i][0] = 0;
		}
		prob[N][0] = 1;


		exp[C] = 0;
		for (int i = C - 1; i >= N; i--) {
			for (int j = 1; j <= N; j++) {
				if (i + j > C) { break; }

				exp[i] += (exp[i + j] + 1)*prob[j][i];
			}

			//(Expected num of packs without failures +1)*exp number of failures
			exp[i] += (exp[i] + 1)*(prob[0][i]) / (1 - prob[0][i]);		
		}
		exp[0] = 1 + exp[N];

		cout << "Case #" << caseN << ": " << exp[0] << endl;
		caseN++;
	}
}