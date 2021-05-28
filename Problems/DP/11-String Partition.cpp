#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

long long DP[205][205];
long long maxSignedInt = 2147483647;
string input;

long long partitionSum(int i, int j) {
	if (i > j) { return 0; }
	if (DP[i][j] != -1) { return DP[i][j]; }

	if (j - i + 1 <= 10) {
		string cS = input.substr(i, j - i + 1);
		long long curNum = stoll(cS);

		if (curNum <= maxSignedInt) {
			DP[i][j] = curNum; return curNum;
		}
	}

	long long maxNum = 0;
	for (int a = 0; a < j - i; a++) {
		if (a > 10) { break; }
		long long l = partitionSum(i, i + a);
		long long r = partitionSum(i + a + 1, j);
		maxNum = max(maxNum, l + r);
	}

	DP[i][j] = maxNum; return maxNum;
}

void resetDP() {
	for (int i = 0; i < 205; i++)
		for (int j = 0; j < 205; j++)
			DP[i][j] = -1;
}

int main() {
	int testCases; cin >> testCases;
	for (int i = 0; i < testCases; i++) {
		cin >> input;
		resetDP();

		long long res = partitionSum(0, input.size() - 1);
		cout << res << endl;
	}
}