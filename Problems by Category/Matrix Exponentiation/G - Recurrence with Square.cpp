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
const ll mod = 1e9 + 7;

struct Matrix {
	int n; vector<vector<ll>> v; Matrix() {}
	Matrix(vector<vector<ll>> &_v) : n(_v.size()) { v = move(_v); }
	Matrix(int _n, ll _x) : n(_n), v(n, vector<ll>(n, _x)) {}
	Matrix(int _n) : n(_n), v(n, vector<ll>(n, 0)) {
		for (int i = 0; i < _n; i++) { v[i][i] = 1; }
	}
	vector<ll>& operator[](int idx) { return v[idx]; }

	Matrix operator *(Matrix &rhs) {
		Matrix res(n, 0);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					res[i][j] = (res[i][j] + v[i][k] * rhs[k][j]) % mod;
		return move(res);
	}

	Matrix operator ^(ll x) {
		Matrix res(n), a(v);
		for (; x; x >>= 1, a = a * a)
			if (x & 1) { res = res * a; }
		return move(res);
	}
};

int main() {
	ll n, k; cin >> n >> k;
	vector<ll> a(n); for (auto &x : a) { cin >> x; }
	vector<ll> c(n); for (auto &x : c) { cin >> x; }
	ll p, q, r; cin >> p >> q >> r;

	if (k < n) { cout << a[k] << '\n'; return 0; }

	reverse(a.begin(), a.end());
	vector<vector<ll>> iV(n + 3, vector<ll>(n + 3));
	for (int i = 0; i < n; i++) { iV[0][i] = a[i]; }
	iV[0][n] = 1; iV[0][n + 1] = n; iV[0][n + 2] = n * n;
	Matrix iM(iV);

	vector<vector<ll>> M(n + 3, vector<ll>(n + 3, 0));
	for (int i = 0; i < n; i++) { M[i][0] = c[i]; }
	M[n][0] = p; M[n + 1][0] = q; M[n + 2][0] = r;

	for (int i = 1; i < n; i++) { M[i-1][i] = 1; }
	M[n][n] = 1; M[n][n + 1] = 1; M[n + 1][n + 1] = 1;
	M[n][n + 2] = 1; M[n + 1][n + 2] = 2; M[n + 2][n + 2] = 1;

	Matrix MM(M);
	MM = MM ^ (k - n + 1);
	cout << (iM*MM)[0][0] << '\n';
}