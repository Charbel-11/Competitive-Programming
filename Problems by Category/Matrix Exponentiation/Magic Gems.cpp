//https://codeforces.com/contest/1117/problem/D
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
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll n; int m; cin >> n >> m;
	if (n < m) { cout << 1 << '\n'; return 0; }

	vector<vector<ll>> dpInitial(m, vector<ll>(m, 0)), v(m, vector<ll>(m, 0));
	for (int i = 0; i < m; i++) { dpInitial[0][i] = 1; }
	v[0][0] = 1; v[m - 1][0] = 1;
	for (int i = 1; i < m; i++) { v[i - 1][i] = 1; }

	Matrix M(v); M = M ^ (n - m + 1);
	M = Matrix(dpInitial)*M;
	cout << M[0][0] << '\n';
}