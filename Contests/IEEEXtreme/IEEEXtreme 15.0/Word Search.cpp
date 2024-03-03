#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<string> grid;
int r, c, q;

bool matchH(string& s, int i, int j) {
	int n = s.size();
	if (j + n - 1 >= c) { return false; }

	for (int k = 0; k < n; k++) {
		if (s[k] != grid[i][j + k]) { return false; }
	}
	return true;
}

bool matchHR(string& s, int i, int j) {
	int n = s.size();
	if (j - (n - 1) < 0) { return false; }

	for (int k = 0; k < n; k++) {
		if (s[k] != grid[i][j - k]) { return false; }
	}
	return true;
}

bool matchV(string& s, int i, int j) {
	int n = s.size();
	if (i + (n - 1) >= r) { return false; }

	for (int k = 0; k < n; k++) {
		if (s[k] != grid[i + k][j]) { return false; }
	}
	return true;
}

bool matchVR(string& s, int i, int j) {
	int n = s.size();
	if (i - (n - 1) < 0) { return false; }

	for (int k = 0; k < n; k++) {
		if (s[k] != grid[i - k][j]) { return false; }
	}
	return true;
}

bool matchDiag(string& s, int i, int j, int dx, int dy) {
	int n = s.size();
	int maxDx = i + dx * (n - 1), maxDy = j + dy * (n - 1);
	if (maxDx < 0 || maxDy < 0 || maxDx >= r || maxDy >= c) { return false; }

	for (int k = 0; k < n; k++) {
		if (s[k] != grid[i + dx * k][j + dy * k]) { return false; }
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> r >> c >> q;
	grid.resize(r); for (auto& s : grid) { cin >> s; }

	while (q--) {
		string s; cin >> s;  int n = s.size();

		bool OK = false;
		int rs = -1, cs, re, ce;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (grid[i][j] != s[0]) { continue; }

				if (matchDiag(s, i, j, -1, -1)) {
					rs = i; cs = j; re = i - (n - 1); ce = j - (n - 1);
					OK = true; break;
				}
				else if (matchVR(s, i, j)) {
					rs = i; cs = j; re = i - (n - 1); ce = j;
					OK = true; break;
				}
				else if (matchDiag(s, i, j, -1, 1)) {
					rs = i; cs = j; re = i - (n - 1); ce = j + (n - 1);
					OK = true; break;
				}
				else if (matchHR(s, i, j)) {
					rs = i; cs = j; re = i; ce = j - (n - 1);
					OK = true; break;
				}
				else if (matchH(s, i, j)) {
					rs = i; cs = j; re = i; ce = j + n - 1;
					OK = true; break;
				}
				else if (matchDiag(s, i, j, 1, -1)) {
					rs = i; cs = j; re = i + (n - 1); ce = j - (n - 1);
					OK = true; break;
				}
				else if (matchV(s, i, j)) {
					rs = i; cs = j; re = i + n - 1; ce = j;
					OK = true; break;
				}
				else if (matchDiag(s, i, j, 1, 1)) {
					rs = i; cs = j; re = i + (n - 1); ce = j + (n - 1);
					OK = true; break;
				}
			}
			if (OK) { break; }
		}

		if (rs == -1) { cout << -1 << '\n'; }
		else { cout << rs << " " << cs << " " << re << " " << ce << '\n'; }
	}
}