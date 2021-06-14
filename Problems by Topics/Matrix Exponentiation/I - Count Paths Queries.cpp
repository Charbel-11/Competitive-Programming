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
	Matrix(vector<vector<ll>> &_v) : n(_v.size()) { v = _v; }
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
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m, q; cin >> n >> m >> q;
	vector<vector<ll>> v(n, vector<ll>(n, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b; a--; b--;
		v[a][b] = 1;
	}

	vector<Matrix> powers; powers.push_back(Matrix(v));
	ll p = 1;
	while (p <= 1e9) {
		powers.push_back(powers.back()*powers.back());
		p <<= 1;
	}

	while (q--) {
		int s, t, k; cin >> s >> t >> k; s--; t--;
		vector<ll> rowS(n, 0); p = 0; rowS[s] = 1;
		for (; k; k >>= 1, p++) {
			if (k & 1) {
				vector<ll> newRowS(n, 0);
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						newRowS[i] += rowS[j] * powers[p].v[j][i];
						newRowS[i] %= mod;
					}
				}
				rowS = newRowS;
			}
		}
		cout << rowS[t] << '\n';
	}
}