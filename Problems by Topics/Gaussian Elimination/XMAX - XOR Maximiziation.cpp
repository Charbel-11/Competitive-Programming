//https://www.spoj.com/problems/XMAX/

#include <vector>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long ll;

const int N = 100065;  // Change accordingly; equal to max num variables + 1

// Runs in O(min(n,m).nm)
// Returns the rank and the determinant of a (without the augmented part)
// If augmented=true, a is assumed to have b as last column (where ax=b)
// If augmented=false, a will be transformed to an upper triangular matrix
pair<int, int> GaussianElimination(vector<bitset<N>>& a, int n, int m, bool augmented = false) {
	int det = 1, rank = 0;
	
	for (int col=0; col<m-augmented; col++) {
		for (int i=rank; i<n; ++i) {
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
int LinearSystem(vector<bitset<N>> a, bitset<64> b, int n, int m, bitset<N>& ans){
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

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int n; cin >> n;
	vector<ll> a(n); for(auto &x : a) { cin >> x; }
	
	vector<bitset<N>> matrix(64);
	for(int i = 0; i < n; i++) {
		ll cur = a[i];
		int curB = 0;
		while (cur) {
			if (cur & 1) { matrix[63 - curB][i] = 1; }
			curB++; cur /= 2;
		}
	}
	
	for(int i = n; i < n+64; i++){
		int b = i-n;
		matrix[63-b][i] = 1;
	}
	
	ll ans = 0;
	bitset<64> candidate;
	bitset<N> vals;
	for(int b = 63; b >= 0; b--){
		candidate[63-b] = 1;
		if (LinearSystem(matrix, candidate, 64, n+b, vals)){
			ans += (1ll << b);
		}
		else{
			candidate[63-b] = 0;
		}
	}
	
	cout << ans << '\n';
}