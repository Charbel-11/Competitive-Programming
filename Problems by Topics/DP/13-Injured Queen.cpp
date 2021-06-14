//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1342
#include <iostream>
#include <string>
using namespace std;

long long DP[20][20];
string status;

long long findNumberOfWays(int i, int prevI) {
	if (i == status.size()) { return 1; }

	long long totalNum = 0;

	if (status[i] == '?') {
		for (int j = 0; j < status.size(); j++) {
			if (j < prevI - 1 || j > prevI + 1) {
				if (DP[i][j] != -1) { totalNum += DP[i][j]; }
				else {
					DP[i][j] = findNumberOfWays(i + 1, j);
					totalNum += DP[i][j];
				}
			}
		}
	}
	else {
		int forcedPos = 0;
		if (status[i] == 'A') { forcedPos = 10; }
		else if (status[i] == 'B') { forcedPos = 11; }
		else if (status[i] == 'C') { forcedPos = 12; }
		else if (status[i] == 'D') { forcedPos = 13; }
		else if (status[i] == 'E') { forcedPos = 14; }
		else if (status[i] == 'F') { forcedPos = 15; }
		else { forcedPos = status[i] - '0'; }
		forcedPos--;

		if (forcedPos >= prevI - 1 && forcedPos <= prevI + 1) { return 0; }
		else {
			DP[i][forcedPos] = findNumberOfWays(i + 1, forcedPos);
			totalNum += DP[i][forcedPos];
		}
	}

	return totalNum;
}

void resetDP() {
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			DP[i][j] = -1;
}

int main() {
	while (true) {
		getline(cin, status); if (status.empty()) { break; }
		resetDP();
		long long ways = findNumberOfWays(0, -5);
		cout << ways << endl;
	}
}