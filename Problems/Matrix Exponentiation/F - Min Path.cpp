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
ll INF = (ll)2e18;

struct Matrix {
	int n; vector<vector<ll>> v; Matrix() {}
	Matrix(vector<vector<ll>> &_v) : n(_v.size()) { v = move(_v); }
	Matrix(int _n, ll _x) : n(_n), v(n, vector<ll>(n, _x)) {}
	Matrix(int _n) : n(_n), v(n, vector<ll>(n, 0)) {
		for (int i = 0; i < _n; i++) { v[i][i] = 1; }
	}
	vector<ll>& operator[](int idx) { return v[idx]; }

	Matrix operator *(Matrix &rhs) {
		Matrix res(n, INF);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++) {
					if (v[i][k] == INF || rhs[k][j] == INF) { continue; }
					res[i][j] = min(res[i][j], v[i][k] + rhs[k][j]);
				}
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
	vector<vector<ll>> v(n, vector<ll>(n, INF));
	for (int i = 0; i < m; i++) {
		int a, b; ll c; cin >> a >> b >> c; a--; b--;
		v[a][b] = c;
	}

	Matrix M(v);
	M = M ^ k;

	ll ans = INF;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ans = min(ans, M[i][j]);

	if (ans == INF) { cout << "IMPOSSIBLE\n"; }
	else { cout << ans << '\n'; }
}