#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll DPa[1002][12], DPb[1002][12];

int main() {
	int n, m; cin >> n >> m;

	ll res = 0;
	for (int j = 1; j <= n; j++) {
		DPa[j][0] = DPb[j][0] = 1;
	}

	for (int i = 1; i < m; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= j; k++) {
				DPa[j][i] += DPa[k][i - 1];
				DPa[j][i] %= mod;
			}
		}
	}
	for (int i = 1; i < m; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = j; k <= n; k++) {
				DPb[j][i] += DPb[k][i - 1];
				DPb[j][i] %= mod;
			}
		}
	}

	for (int j = 1; j <= n; j++) {
		for (int k = 1; k <= j; k++) {
			ll cur = DPb[j][m - 1]; cur %= mod;
			cur *= DPa[k][m - 1]; cur %= mod;
			res += cur; res %= mod;
		}
	}

	cout << res << endl;
}