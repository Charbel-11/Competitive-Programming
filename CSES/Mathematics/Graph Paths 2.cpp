#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <climits>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
const ll mod = 1e9 + 7;

//Matrix exponentiation
struct Matrix {
	int n; vector<vector<ll>> v; Matrix() {}
	Matrix(vector<vector<ll>>& _v) : n(_v.size()) { v = move(_v); }
	Matrix(int _n, ll _x) : n(_n), v(n, vector<ll>(n, _x)) {}
	Matrix(int _n) : n(_n), v(n, vector<ll>(n, ULLONG_MAX/4)) {
		for (int i = 0; i < _n; i++) { v[i][i] = 0; }
	}
	vector<ll>& operator[](int idx) { return v[idx]; }

	Matrix operator *(Matrix& rhs) {
		Matrix res(n, ULLONG_MAX / 4);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					res[i][j] = min(res[i][j], v[i][k] + rhs[k][j]);
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

	int n, m, k; cin >> n >> m >> k;
	vector<vector<ll>> v(n, vector<ll>(n, ULLONG_MAX / 4));
	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y; x--; y--;
		ll c; cin >> c;
		v[x][y] = min(v[x][y], c);
	}

	Matrix M(v); M = M ^ k;
	if (M[0][n - 1] == ULLONG_MAX / 4) { cout << -1 << '\n'; }
	else { cout << M[0][n - 1] << '\n'; }
}