//https://codeforces.com/contest/222/problem/E
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
	ll n, m, k; cin >> n >> m >> k;
	vector<vector<ll>> v(m, vector<ll>(m, 1));
	for (int i = 0; i < k; i++) {
		string s; cin >> s;
		int a, b;
		if (s[0] >= 'a' && s[0] <= 'z') { a = s[0] - 'a'; }
		else { a = s[0] - 'A' + 26; }
		if (s[1] >= 'a' && s[1] <= 'z') { b = s[1] - 'a'; }
		else { b = s[1] - 'A' + 26; }
		v[a][b] = 0;
	}

	Matrix M(v);
	M = M ^ (n - 1);
	ll ans = 0;
	for (auto &x : M.v) {
		for (auto &y : x) {
			ans += y; ans %= mod;
		}
	}

	cout << ans << '\n';
}