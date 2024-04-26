#include <bits/stdc++.h>
using namespace std;

const int N = 100;  // Change accordingly; equal to max num variables + 1

// Runs in O(min(n,m).nm/32)
// Returns the rank and the determinant of a (without the augmented part)
// If augmented=true, a is assumed to have b as last column (where ax=b); a will be transformed to a RREF
// If augmented=false, a will be transformed to an upper triangular matrix
pair<int, int> GaussianElimination(vector<bitset<N>>& a, int n, int m, bool augmented = false) {
	int det = 1, rank = 0;
	
	for (int col = 0; col < m - augmented; col++) {
		if (rank == n) { det = 0; break; }
		for (int i = rank; i < n; ++i) {
			if (a[i][col]) {
				swap(a[i], a[rank]);
				break;
			}
		}
		if (!a[rank][col]) { det = 0; continue; }

		for (int i = (augmented ? 0 : rank + 1); i < n; i++) {
			if (i != rank && a[i][col])
				a[i] ^= a[rank];
		}
		rank++;
	}
	
	return {rank, det};
}

// Finds x in ax=b in O(min(n,m).nm/32)
// Returns 0 if there are no solution, 1 if there is exactly one solution and 2 if there are infinitely many solutions
// If there is a unique solution, it is returned in ans (if there are infinitely many, ans is one of them)
// Bitset ordering in a is not important; so we can assume a[i][j] is the (i,j) entry of matrix a
int LinearSystem(vector<bitset<N>> a, bitset<N>& b, int n, int m, bitset<N>& ans){
	for (int i = 0; i < n; i++) { a[i][m] = b[i]; }
	
	auto p = GaussianElimination(a, n, m + 1, true);
	int rank = p.first;
	
	for (int i = rank; i < n; ++i) {
		if (a[i][m]) { return 0; }
	}
	
	ans.reset();
	for (int i = 0, j = 0; i < rank; i++) {
		while (!a[i][j]) { j++; }
		ans[j] = a[i][m];
	}
	
	if (rank < n){ return 2; }
	else { return 1; }
}