//https://codeforces.com/contest/1182/problem/E
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
					res[i][j] = (res[i][j] + v[i][k] * rhs[k][j]) % (mod - 1);
		return move(res);
	}

	Matrix operator ^(ll x) {
		Matrix res(n), a(v);
		for (; x; x >>= 1, a = a * a)
			if (x & 1) { res = res * a; }
		return move(res);
	}
};


ll power(ll x, ll n) {
	ll res = 1;
	for (; n; n >>= 1, x = (x * x) % mod)
		if (n & 1) { res = (res * x) % mod; }
	return res;
}

ll modInv(ll x) { return power(x, mod - 2); }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	vector<vector<ll>> v = { {1, 1, 0},	{1, 0, 1}, {1, 0, 0} };

	ll n, f1, f2, f3, c; cin >> n >> f1 >> f2 >> f3 >> c;
	f1 = (f1 * c) % mod; f2 = (f2 * c) % mod; f2 = (f2 * c) % mod;
	f3 = (f3 * c) % mod; f3 = (f3 * c) % mod; f3 = (f3 * c) % mod;
	Matrix M(v); M = M ^ (n - 3);

	f1 = power(f1, M[2][0]); f2 = power(f2, M[1][0]); f3 = power(f3, M[0][0]); 
	ll res = f1 * f2; res %= mod; 
	res *= f3; res %= mod;
	res *= modInv(power(c, n)); res %= mod;
	cout << res << endl;
}