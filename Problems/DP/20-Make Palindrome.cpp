//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=114&page=show_problem&problem=1394
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string s;
int DP[1002][1002];
int Choice[1002][1002];

int findMin(int i, int j) {
	if (DP[i][j] != -1) { return DP[i][j]; }
	if (i >= j) { return DP[i][j] = 0; }

	if (s[i] == s[j]) { Choice[i][j] = 0; return findMin(i + 1, j - 1); }

	int c1 = 1 + findMin(i + 1, j);
	int c2 = 1 + findMin(i, j - 1);

	if (c1 < c2) { DP[i][j] = c1; Choice[i][j] = 1; }
	else { DP[i][j] = c2; Choice[i][j] = 2; }

	return DP[i][j];
}

void resetDP() {
	for (int i = 0; i < 1002; i++)
		for (int j = 0; j < 1002; j++) {
			DP[i][j] = -1; Choice[i][j] = -1;
		}
}

void printPalindrome(int extra) {
	int n = s.size() + extra; vector<char> answ(n);
	int i = 0, j = s.size() - 1;
	int a = 0, b = n - 1;

	while (i <= j) {
		if (Choice[i][j] == 0) { answ[a] = s[i++]; answ[b] = s[j--]; }
		else if (Choice[i][j] == 1) { answ[a] = s[i]; answ[b] = s[i++]; }
		else { answ[a] = s[j]; answ[b] = s[j--]; }
		a++; b--;
	}

	for (auto x : answ) { cout << x; } cout << endl;
}

int main() {
	while (true) {
		cin >> s; if (cin.fail()) { break; }
		resetDP();

		int minCost = findMin(0, s.size() - 1);
		cout << minCost << " ";
		printPalindrome(minCost);
	}
}