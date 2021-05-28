#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef unsigned int ll;

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
					res[i][j] = (res[i][j] + v[i][k] * rhs[k][j]);
		return move(res);
	}

	Matrix operator ^(ll x) {
		Matrix res(n), a(v);
		for (; x; x >>= 1, a = a * a)
			if (x & 1) { res = res * a; }
		return move(res);
	}
};

int dx[] = { -2,-1,1,2 };
int dy[] = { -2,-1,1,2 };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll k; cin >> k;
	vector<vector<ll>> v(65, vector<ll>(65, 0));
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int curS = i * 8 + j;
			for (auto &x : dx) {
				for (auto &y : dy) {
					if (abs(x) == abs(y)) { continue; }
					int ni = i + x, nj = j + y;
					if (ni < 0 || ni>7 || nj < 0 || nj>7) { continue; }
					int nxtS = ni * 8 + nj;
					v[curS][nxtS] = 1;
				}
			}
		}
	}
	for (int i = 0; i < 65; i++) { v[i][64] = 1; }

	Matrix M(v);
	M = M ^ k;

	ll ans = 0;
	for (int j = 0; j < 65; j++) { ans += M[0][j]; }
	
	cout << ans << '\n';
}