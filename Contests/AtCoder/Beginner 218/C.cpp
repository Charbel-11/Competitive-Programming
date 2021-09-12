#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n;

vector<string> rotateRight(const vector<string>& S) {
	vector<string> res(n, string(n, '.'));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int ni = j, nj = n - i - 1;
			res[ni][nj] = S[i][j];
		}
	}

	return move(res);
}

vector<string> translateTo(const vector<string>& S, int deltaRow, int deltaCol) {
	vector<string> res(n, string(n, '.'));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int ni = i + deltaRow, nj = j + deltaCol;
			if (ni < n && ni >= 0 && nj < n && nj >= 0) { res[ni][nj] = S[i][j]; }
		}
	}
	
	return move(res);
}

bool areEqual(const vector<string>& v1, const vector<string>& v2) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (v1[i][j] != v2[i][j]) { return false; }
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n;
	vector<string> S(n), T(n);
	for (auto& s : S) { cin >> s; }
	for (auto& s : T) { cin >> s; }

	int cntS = 0, cntT = 0;
	for (auto& s : S) 
		for (auto& c : s) 
			if (c == '#') { cntS++; }
	for (auto& s : T)
		for (auto& c : s)
			if (c == '#') { cntT++; }

	if (cntS != cntT) { cout << "No" << '\n'; return 0; }

	bool OK = false;
	for (int r = 0; r < 4; r++) {
		vector<int> rowS(n, 0), rowT(n, 0);
		vector<int> colS(n, 0), colT(n, 0);

		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++) {
				if (S[i][j] == '#') { rowS[i]++; colS[j]++; }
				if (T[i][j] == '#') { rowT[i]++; colT[j]++; }
			}
		}

		int firstNonZeroRowS = -1, firstNonZeroRowT = -1;
		int firstNonZeroColS = -1, firstNonZeroColT = -1;
		for (int i = 0; i < n; i++) {
			if (rowS[i] != 0) {
				if (firstNonZeroRowS == -1) { firstNonZeroRowS = i; }
			}
			if (colS[i] != 0) {
				if (firstNonZeroColS == -1) { firstNonZeroColS = i; }
			}
			if (rowT[i] != 0) {
				if (firstNonZeroRowT == -1) { firstNonZeroRowT = i; }
			}
			if (colT[i] != 0) {
				if (firstNonZeroColT == -1) { firstNonZeroColT = i; }
			}
		}

		vector<string> translatedS = translateTo(S, firstNonZeroRowT - firstNonZeroRowS, firstNonZeroColT - firstNonZeroColS);

		if (areEqual(translatedS, T)) { OK = true; break; }

		S = rotateRight(S);
	}

	if (OK) { cout << "Yes" << '\n'; }
	else { cout << "No" << '\n'; }
}