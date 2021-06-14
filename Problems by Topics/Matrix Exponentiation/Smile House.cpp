//https://codeforces.com/contest/147/problem/B
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Matrix {
	int n; vector<vector<int>> v; Matrix() {}
	Matrix(vector<vector<int>> &_v) : n(_v.size()) { v = move(_v); }
	Matrix(int _n, int _x) : n(_n), v(n, vector<int>(n, _x)) {}

	Matrix operator *(Matrix &rhs) {
		Matrix res(n, -1e9);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++) {
					res.v[i][j] = max(res.v[i][j], v[i][k] + rhs.v[k][j]);
				}
		return move(res);
	}
};

Matrix power[9];
int n, m;

bool check(int x) {
	Matrix res; bool b = true;
	int p = 0;
	for (; x; x >>= 1, p++)
		if (x & 1) {
			if (b) { res = power[p]; b = false; }
			else { res = res * power[p]; }
		}
	
	for (int i = 0; i < n; i++) { if (res.v[i][i] > 0) return true; }
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	vector<vector<int>> g(n, vector<int>(n, -1e9));
	for (int i = 0; i < n; i++) { g[i][i] = 0; }
	for (int i = 0; i < m; i++) {
		int u, v, c1, c2; cin >> u >> v >> c1 >> c2;
		u--; v--; g[u][v] = c1; g[v][u] = c2;
	}

	power[0] = Matrix(g);
	for (int i = 1; i < 9; i++) { power[i] = power[i - 1] * power[i - 1]; }

	int l = 2, r = n + 2;
	while (l < r) {
		int mid = (l + r) >> 1;
		bool b = check(mid);
		if (b) { r = mid; }
		else { l = mid + 1; }
	}

	if (l == n + 2) { cout << 0 << '\n'; }
	else { cout << l << '\n'; }
}