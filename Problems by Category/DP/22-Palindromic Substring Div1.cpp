//https://community.topcoder.com/stat?c=problem_statement&pm=12964&rd=15840
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

double DP[5002][5002];		//prob that DP[i][j] is palindrome
string s;

double expected(int i, int j) {
	if (DP[i][j] != -1) { return DP[i][j]; }
	if (i >= j) { DP[i][j] = 1; return 1; }

	double answ;
	if (s[i] == '?' || s[j] == '?') { answ = expected(i + 1, j - 1) / 26; }
	else if (s[i] == s[j]) { answ = expected(i + 1, j - 1); }
	else { answ = 0; }

	DP[i][j] = answ;
	return DP[i][j];
}

void resetDP() {
	for (int i = 0; i < 5002; i++)
		for (int j = 0; j < 5002; j++)
			DP[i][j] = -1.0;
}

int main() {
	cin >> s;

	resetDP();

	double res = 0;
	for (int i = 0; i < s.size(); i++) {
		for (int j = i; j < s.size(); j++) {
			expected(i, j);
			if (DP[i][j] != -1) res += DP[i][j];
		}
	}

	cout << setprecision(10) << res << endl;
}