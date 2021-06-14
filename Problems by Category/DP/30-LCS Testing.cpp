#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector<vector<int>> dp;
string a, b;

string getLCSBotUp() {
	int n = a.size(), m = b.size();
	int i = 0, j = 0;
	
	string res = "";
	while (i < n && j < n) {
		if (dp[i][j] == dp[i + 1][j + 1] + 1 && a[i] == b[j]) {
			res += a[i];
			i++; j++;
		}
		else {
			if (dp[i][j] == dp[i + 1][j]) {
				i++;
			}
			else { j++; }
		}
	}

	return res;
}
int LCSBotUp() {
	int n = a.size(), m = b.size();
	dp.resize(n + 1); for (auto &x : dp) { x.resize(m + 1, -1); }

	for (int i = 0; i <= n; i++) { dp[i][m] = 0; }
	for (int i = 0; i <= m; i++) { dp[n][i] = 0; }

	for (int i = n - 1; i >= 0; i--) {
		for (int j = m - 1; j >= 0; j--) {
			if (a[i] == b[j])
				dp[i][j] = 1 + dp[i + 1][j + 1];
			else
				dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
		}
	}

	return dp[0][0];
}


vector<vector<int>> DP;
vector<vector<int>> Choice;
int LCS(int i, int j) {
	if (i >= a.size() || j >= b.size()) { return 0; }
	if (DP[i][j] != -1) { return DP[i][j]; }

	int res;
	if (a[i] == b[j]) { res = 1 + LCS(i + 1, j + 1); Choice[i][j] = 1; }
	else {
		int c1 = LCS(i + 1, j); int c2 = LCS(i, j + 1);
		if (c1 > c2) { res = c1; Choice[i][j] = 2; }
		else { res = c2; Choice[i][j] = 3; }
	}

	DP[i][j] = res; return res;
}
string printChoice() {
	int i = 0, j = 0;
	string res = "";
	while (i < a.size() && j < b.size()) {
		if (Choice[i][j] == 1) { res += a[i]; i++; j++; }
		else if (Choice[i][j] == 2) { i++; }
		else { j++; }
	}
	return res;
}
int LCSRec() {
	DP.resize(a.size() + 1); for (auto &x : DP) { x.resize(b.size()+1); }
	Choice.resize(a.size() + 1); for (auto &x : Choice) { x.resize(b.size()+1); }
	for (int i = 0; i <= a.size(); i++)
		for (int j = 0; j <= b.size(); j++) {
			DP[i][j] = -1; Choice[i][j] = -1;
		}
	return LCS(0, 0);
}

int main() {
	for (int z = 0; z < 10; z++) {
		int nu = rand() % 5 + 5;
		a = "", b = "";
		for (int i = 0; i < nu; i++) {
			a += 'a' + rand() % 26;
			b += 'a' + rand() % 26;
		}

		int c1, c2;
		string s1;
		c1 = LCSRec();
		c2 = LCSBotUp();
		s1 = getLCSBotUp();

		if (c1 != c2) {
			cout << "DIFFERENT" << endl;
			cout << a << " " << b << endl;
			cout << c1 << " " << c2 << endl;
			cout << s1 << endl;
		}
		else {
			int ind = 0;
			bool OK = true;
			for (int i = 0; i < a.size() && ind < s1.size(); i++) {
				if (s1[ind] == a[i]) { ind++; }
			}
			if (ind != s1.size()) { OK = false; }
			ind = 0;
			for (int i = 0; i < b.size() && ind < s1.size(); i++) {
				if (s1[ind] == b[i]) { ind++; }
			}
			if (ind != s1.size()) { OK = false; }

			if (!OK){
				cout << a << " " << b << " " << s1 << endl;

				for (int i = 0; i < a.size(); i++) {
					for (int j = 0; j < b.size(); j++) {
						cout << dp[i][j] << " ";
					}
					cout << endl;
				}
			}
		}
	}
}