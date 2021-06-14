#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		int N; cin >> N;

		vector<vector<int>> matrix(N);
		for (auto &x : matrix) { x.resize(N); for (auto &y : x) { cin >> y; } }

		int s = 0, r = 0, c = 0;
		for (int i = 0; i < N; i++) { s += matrix[i][i]; }
		for (int i = 0; i < N; i++) {
			set<int> seen;
			for (int j = 0; j < N; j++) {
				if (seen.count(matrix[i][j])) { r++; break; }
				seen.insert(matrix[i][j]);
			}
		}
		for (int j = 0; j < N; j++) {
			set<int> seen;
			for (int i = 0; i < N; i++) {
				if (seen.count(matrix[i][j])) { c++; break; }
				seen.insert(matrix[i][j]);
			}
		}

		cout << "Case #" << q << ": " << s << " " << r << " " << c << endl;
	}
}