//https://community.topcoder.com/stat?c=problem_statement&pm=13063

#include <iostream>
#include <string>
#include <vector>

using namespace std;

double DP[1004][502];

double expected(int i, int k) {
	if (DP[i][k] != -1) { return DP[i][k]; }
	if (i == 500) { return 1.0; }
	if (abs(i-500) > k) { return 0.0; }

	double res = 0.5*expected(i - 1, k - 1) + 0.5*expected(i + 1, k - 1);

	DP[i][k] = res;
	return res;
}


void resetDP() {
	for (int i = 0; i < 1004; i++)
			for (int k = 0; k < 502; k++)
				DP[i][k] = -1.0;
}

int main() {
	int N;
	cin >> N;

	resetDP();

	double expectedRes = 0;

	for (int i = 0; i < 1004; i++) {
		expectedRes += expected(i, N);
	}

	cout << expectedRes << endl;
}