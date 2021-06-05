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

//Matrix exponentiation
struct Matrix {
	int n; vector<vector<ll>> v; Matrix() {}
	Matrix(vector<vector<ll>>& _v) : n(_v.size()) { v = move(_v); }
	Matrix(int _n, ll _x) : n(_n), v(n, vector<ll>(n, _x)) {}
	Matrix(int _n) : n(_n), v(n, vector<ll>(n, 0)) {
		for (int i = 0; i < _n; i++) { v[i][i] = 1; }
	}
	vector<ll>& operator[](int idx) { return v[idx]; }

	Matrix operator *(Matrix& rhs) {
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

	vector<ll> dp(6, 0);
	for (int i = 0; i < 6; i++) {
		dp[i] = 1ll << i;
	}
	ll n; cin >> n;
	if (n <= 6) { cout << dp[n - 1] << '\n'; return 0; }

	vector<vector<ll>> v = { {0,0,0,0,0,1},{1,0,0,0,0,1},{0,1,0,0,0,1},{0,0,1,0,0,1},{0,0,0,1,0,1},{0,0,0,0,1,1} };
	Matrix M(v);
	M = M ^ (n - 6);

	ll ans = 0;
	for (int i = 0; i < 6; i++) {
		ans += dp[i] * M[i][5];
		ans %= mod;
	}
	cout << ans << '\n';
}