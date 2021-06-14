#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

string s, t;
int DP[3001][3001];
int Choice[3001][3001];

int LCS(int i, int j) {
	if (DP[i][j] != -1) { return DP[i][j]; }
	if (i == s.length() || j == t.length()) { return DP[i][j] = 0; }

	int ans = 0;
	if (s[i] == t[j]) { ans = 1 + LCS(i + 1, j + 1); }
	else {
		int c1 = LCS(i + 1, j);
		int c2 = LCS(i, j + 1);
		if (c1 > c2) { Choice[i][j] = 0; ans = c1; }
		else { Choice[i][j] = 1; ans = c2; }
	}

	return DP[i][j] = ans;
}

int main() {
	cin >> s >> t;

	for (int i = 0; i < 3001; i++)
		for (int j = 0; j < 3001; j++)
			DP[i][j] = Choice[i][j] = -1;

	LCS(0, 0);
	int i = 0, j = 0;
	string ans = "";
	while (i < s.length() && j < t.length()) {
		if (s[i] == t[j]) { ans.push_back(s[i]); i++; j++; continue; }
		if (Choice[i][j] == 0) { i++; }
		else { j++; }
	}

	cout << ans << endl;
}