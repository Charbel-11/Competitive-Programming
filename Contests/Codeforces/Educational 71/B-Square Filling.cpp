#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<vector<int>> A(n);
	vector<vector<int>> B(n);
	for (int i = 0; i < n; i++) {
		A[i].resize(m); B[i].resize(m, 0);
		for (int j = 0; j < m; j++) {
			int t; cin >> t;
			A[i][j] = t;
		}
	}

	vector<pair<int, int>> answ;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < m - 1; j++) {
			if (A[i][j] == 1 && A[i + 1][j + 1] == 1 && A[i + 1][j] == 1 && A[i][j + 1] == 1) {
				answ.push_back({ i + 1, j + 1 });
				B[i][j] = 1; B[i + 1][j] = 1; B[i + 1][j + 1] = 1; B[i][j + 1] = 1;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] != B[i][j]) { cout << -1 << endl; return 0; }
		}
	}

	cout << answ.size() << endl;
	for (auto x : answ) { cout << x.first << " " << x.second << endl; }
}