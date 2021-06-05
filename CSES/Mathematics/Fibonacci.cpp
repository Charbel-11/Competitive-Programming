#include <iostream>
#include <cmath>
#include <vector>
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;

vector<vector<ll>> matrix_mult(vector<vector<ll>> a, vector<vector<ll>> b) {
	ll n = (ll)a.size();
	vector<vector<ll>> c(n, vector<ll>(n, 0));
	for (ll i = 0; i < n; i++)
		for (ll j = 0; j < n; j++)
			for (ll k = 0; k < n; k++) {
				c[i][j] += a[i][k] * b[k][j];
				c[i][j] %= mod;
			}
	return move(c);
}

vector<vector<ll>> matrix_exp(vector<vector<ll>> a, ll n) {
	vector<vector<ll>> I(a.size(), vector<ll>(a.size(), 0));
	for (ll i = 0; i < (ll)a.size(); i++) { I[i][i] = 1; }
	if (n == 0) { return move(I); }
	if (n == 1) { return move(a); }
	vector<vector<ll>> res = matrix_exp(a, n / 2);
	res = matrix_mult(res, res);
	if (n % 2) { return move(matrix_mult(res, a)); }
	return move(res);
}

int main() {
	ll n; cin >> n;
	vector<vector<ll>> m(2, vector<ll>(2, 1)); m[1][1] = 0;
	cout << matrix_exp(m, n)[0][1] << '\n';
}