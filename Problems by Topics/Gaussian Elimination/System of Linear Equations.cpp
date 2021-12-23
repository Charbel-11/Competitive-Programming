//https://judge.yosupo.jp/problem/system_of_linear_equations

#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

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

vector<vector<ll>> LinearEquation(vector<vector<ll>> a, vector<ll> b) {
	int n = a.size(), m = a[0].size();
	for (int i = 0; i < n; i++) { a[i].push_back(b[i]); }
	auto p = GaussianElimination(a, true);
	int rank = p.first;
	
	for (int i = rank; i < n; ++i) {
		if (a[i][m] != 0) return vector<vector<ll>>{};
	}
	
	vector<vector<ll>> res(1, vector<ll>(m));
	vector<int> pivot(m, -1);
	for (int i = 0, j = 0; i < rank; ++i) {
		while (a[i][j] == 0) ++j;
		res[0][j] = a[i][m], pivot[j] = i;
	}
	
	// Solution space
	for (int j = 0; j < m; ++j) {
		if (pivot[j] == -1) {
			vector<ll> x(m);
			x[j] = 1;
			for (int k = 0; k < j; ++k) {
				if (pivot[k] != -1) { x[k] = (mod - a[pivot[k]][j]) % mod; }
			}
			res.push_back(x);
		}
	}
	return res;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int n,m; cin >> n >> m;
	vector<vector<ll>> a(n, vector<ll>(m));
	vector<ll> b(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> a[i][j];
	for(int i = 0; i < n; i++) { cin >> b[i]; }
	
	auto res = LinearEquation(a, b);
	if (res.empty()){ cout << -1 << '\n'; return 0; }
	
	cout << res.size()-1 << '\n';
	for(auto &v: res){
		for(auto &x : v){
			cout << x << ' ';
		}
		cout<<'\n';
	}
}