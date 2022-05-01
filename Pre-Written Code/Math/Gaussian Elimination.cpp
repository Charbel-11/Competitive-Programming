#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;
const double EPS = 1e-9;

// Runs in O(min(n,m).nm)
// Returns the rank and the determinant of a (without the augmented part)
// If augmented=true, a is assumed to have b as last column (where ax=b)
// If augmented=false, a will be transformed to an upper triangular matrix
pair<int, double> GaussianElimination(vector<vector<double>> &a, bool augmented = false) {
	int n = a.size(), m = a[0].size(), rank = 0;
	double det = 1;
	
	for (int col = 0; col < m - augmented; col++) {
		if (rank == n) { det = 0; break; }
		int pivot = rank;
		for (int i = rank + 1; i < n; i++) {
			if (abs(a[i][col]) > abs(a[pivot][col]))
				pivot = i;
		}
		if (abs(a[pivot][col]) < EPS) { det = 0; continue; }

		if (rank != pivot) {
			det = -det;
			swap(a[rank], a[pivot]);
		}
		det *= a[rank][col];

		if (augmented && a[rank][col] != 1) {
			double c = 1 / a[rank][col];
			for (int j = col; j < m; j++) { a[rank][j] *= c; }
		}

		for (int i = (augmented ? 0 : rank + 1); i < n; i++) {
			if (i == rank) { continue; }
			if (abs(a[i][col]) > EPS) {
				double c = a[i][col] / a[rank][col];
				for (int j = col; j < m; j++) { a[i][j] -= a[rank][j] * c; }
			}
		}
		rank++;
	}
	
	return {rank, det};
}

// Finds x in ax=b in O(min(n,m).nm)
// Returns 0 if there are no solution, 1 if there is exactly one solution and 2 if there are infinitely many solutions
// If there is a unique solution, it is returned in ans (if there are infinitely many, ans is one of them)
int LinearSystem(vector<vector<double>> a, vector<double> b, vector<double>& ans){
	int n = a.size(), m = a[0].size();
	for (int i = 0; i < n; i++) { a[i].push_back(b[i]); }
	
	auto p = GaussianElimination(a, true);
	int rank = p.first;
	
	for (int i = rank; i < n; ++i) {
		if (abs(a[i][m]) > EPS) { return 0; }
	}
	
	ans.clear(); ans.resize(m, 0);
	for (int i = 0, j = 0; i < rank; i++) {
		while (a[i][j] == 0) { j++; }
		ans[j] = a[i][m];
	}

	if (rank < n){ return 2; }
	else { return 1; }
}