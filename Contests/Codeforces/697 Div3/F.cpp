#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

bool make0(vector<vector<int>> M1) {
	int n = M1.size();
	vector<vector<int>> M = M1;

	int startI = -1, startJ = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (M[i][j]) { startI = i; startJ = j; break; }
		}
	}
	if (startI == -1 && startJ == -1) { return true; }

	for (int j = 0; j < n; j++) {
		M[startI][j] ^= 1;
		if (M[startI][j] == 1){
			for (int i = 0; i < n; i++) { M[i][j] ^= 1; }
		}
	}
	bool OK = true;
	for (int i = 0; i < n; i++) {	
		int cnt1 = 0;
		for (int j = 0; j < n; j++) { cnt1 += M[i][j]; }
		if (cnt1 > 0 && cnt1 < n) { OK = false; break; }
	}
	if (OK) { return true; }

	M = M1;
	for (int i = 0; i < n; i++) {
		M[i][startJ] ^= 1;
		if (M[i][startJ] == 1) {
			for (int j = 0; j < n; j++) { M[i][j] ^= 1; }
		}
	}
	OK = true;
	for (int j = 0; j < n; j++) {
		int cnt1 = 0;
		for (int i = 0; i < n; i++) { cnt1 += M[i][j]; }
		if (cnt1 > 0 && cnt1 < n) { OK = false; break; }
	}
	return OK;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<string> M1(n); for (auto& s : M1) { cin >> s; }
		vector<string> M2(n); for (auto& s : M2) { cin >> s; }

		vector<vector<int>> M(n, vector<int>(n, 0));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (M1[i][j] != M2[i][j]) { M[i][j] = 1; }
			}
		}

		if (make0(M)) { cout << "YES" << '\n'; }
		else { cout << "NO" << '\n'; }
	}
}