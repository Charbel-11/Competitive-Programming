#include <iostream>
#include <string>
#include <climits>

using namespace std;

int DP[2000000][25];

int knapsack(int* val, int* cap, int n, int revenue, int i) {
	if (revenue <= 0) { return 0; } if (i >= n) { return INT_MAX; }
	if (DP[revenue][i] != -1) { return DP[revenue][i]; }

	int minCap = INT_MAX;

	int a = cap[i] + knapsack(val, cap, n, revenue - val[i], i + 1);
	int b = knapsack(val, cap, n, revenue, i + 1);

	minCap = (a < b) ? a : b;

	DP[revenue][i] = minCap;
	return minCap;
}

void resetDP() {
	for (int i = 0; i < 2000000; i++) {
		for (int j = 0; j < 25; j++) {
			DP[i][j] = -1;
		}
	}
}

int main() {
	resetDP();

	int maxCap = 6404180;
	int val[] = { 825594,1677009,1676628,1523970,943972,97426,69666,1296457,1679693,1902996,1844992,1049289,1252836,1319836, 953277,2067538, 675367, 853655,1826027  ,65731,901489 ,577243,466257,369261 };
	int cap[] = { 382745,799601,909247,729069,467902,44328,34610,698150,823460,903959,853665,551830,610856,670702,488960,951111,323046,446298,931161 ,31385,496951,264724,224916,169684 };
	int n = 24;

	int revenue = 1;
	int w = knapsack(val, cap, n, revenue, 0);
	int temp = 0;
	while (w < maxCap) {
		temp = revenue;	revenue++;
		w = knapsack(val, cap, n, revenue, 0);
	}

	cout << temp << endl;
}