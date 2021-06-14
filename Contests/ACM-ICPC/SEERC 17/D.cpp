#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int compute_rank(vector<vector<int>> A) {
	int n = A.size();
	int m = A[0].size();

	int rank = 0;
	vector<bool> row_selected(n, false);
	for (int i = 0; i < m; ++i) {
		int j;
		for (j = 0; j < n; ++j) {
			if (!row_selected[j] && abs(A[j][i]) > EPS)
				break;
		}

		if (j != n) {
			++rank;
			row_selected[j] = true;
			for (int p = i + 1; p < m; ++p)
				A[j][p] /= A[j][i];
			for (int k = 0; k < n; ++k) {
				if (k != j && abs(A[k][i]) > EPS) {
					for (int p = i + 1; p < m; ++p)
						A[k][p] -= A[j][p] * A[k][i];
				}
			}
		}
	}
	return rank;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {

	}
}