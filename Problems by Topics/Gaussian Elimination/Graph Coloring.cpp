//https://lightoj.com/problem/graph-coloring

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
typedef long long ll;
const ll modCount = 1e9+7;
ll mod;

// fast exponentiation modulo mod
ll powe(ll x, ll p, ll m) {
	ll res = 1;
	for (; p; p >>= 1, x = (x * x) % m)
		if (p & 1) res = (res * x) % m;
	return res;
}

// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2, mod); }

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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int t; cin >> t;
	for(int qq = 1; qq <= t; qq++){
		int n, m; cin >> n >> m >> mod;
		
		vector<vector<ll>> adj(n, vector<ll>(n, 0));
		for(int i = 0; i < n; i++){ adj[i][i] = 1; }
		for(int i = 0; i < m; i++){
			int u, v; cin >> u >> v; u--; v--;
			adj[u][v] = adj[v][u] = mod - 1;
		}
		
		auto p = GaussianElimination(adj);
		ll ans = powe(mod, n-p.first, modCount);
		cout << "Case " << qq << ": " << ans << '\n';
	}
}