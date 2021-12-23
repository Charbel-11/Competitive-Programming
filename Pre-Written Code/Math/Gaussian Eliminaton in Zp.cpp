#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	ll res = 1;
	for (; p; p >>= 1, x = (x * x) % mod)
		if (p & 1) res = (res * x) % mod;
	return res;
}

// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

// Runs in O(min(n,m).nm)
// Returns the rank and the determinant of a (without the augmented part)
// If augmented=true, a is assumed to have b as last column (where ax=b)
// If augmented=false, a will be transformed to an upper triangular matrix
pair<int, ll> GaussianElimination(vector<vector<ll>> &a, bool augmented = false) {
	int n = a.size(), m = a[0].size(), rank = 0;
	ll det = 1;
	
	for (int col=0; col<m-augmented; col++) {
		int pivot = -1;
		for (int i = rank; i < n; i++) {
			if (a[i][col] > 0) {
				pivot = i;
				break;
			}
		}
		if (pivot == -1) { det = 0; continue; }
		
		if (rank != pivot) {
			det = mod-det;
			swap(a[rank], a[pivot]);
		}
		det *= a[rank][col]; det %= mod;
		
		if (augmented && a[rank][col] != 1) {
			ll inv = modinv(a[rank][col]);
			for(int j = col; j < m; j++){
				a[rank][j] *= inv;
				a[rank][j] %= mod;
			}
		}
		
		for (int i = (augmented ? 0 : rank + 1); i < n; i++) {
			if (i == rank) { continue; }
			if (a[i][col] != 0) {
				ll c = (a[i][col] * modinv(a[rank][col])) % mod;
				for (int j = col; j < m; j++) {
					ll diff = (a[rank][j] * c) % mod;
					a[i][j] = (a[i][j] - diff + mod) % mod;
				}
			}
		}
		rank++;
	}
	
	return {rank, det};
}

// Finds x in ax=b in O(min(n,m).nm)
// Returns 0 if there are no solution, 1 if there is exactly one solution and 2 if there are infinitely many solutions
// If there is a unique solution, it is returned in ans (if there are infinitely many, ans is one of them)
int LinearSystem(vector<vector<ll>> a, vector<ll> b, vector<ll>& ans){
	int n = a.size(), m = a[0].size();
	for (int i = 0; i < n; i++) { a[i].push_back(b[i]); }
	
	auto p = GaussianElimination(a, true);
	int rank = p.first;
	
	for (int i = rank; i < n; ++i) {
		if (a[i][m] != 0) { return 0; }
	}
	
	ans.clear(); ans.resize(m, 0);
	for (int i = 0, j = 0; i < rank; i++) {
		while (a[i][j] == 0) { j++; }
		ans[j] = a[i][m];
	}
	
	if (rank < n){ return 2; }
	else { return 1; }
}
