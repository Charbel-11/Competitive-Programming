#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ll n, m; cin >> n >> m;

	vector<ll> fact(n + 1);
	fact[0] = fact[1] = 1ll;
	for (ll i = 2ll; i < n + 1; i++) {
		fact[i] = fact[i - 1] * i;
		fact[i] %= m;
	}

	ll res = 0;
//	ll res = n; res%=m;
//	res *= fact[n]; res%= m;

	for (ll l = 1ll; l <= n; l++) {
		ll temp = n - l + 1;
		temp *= fact[l]; temp %= m;
		temp *= (n - l + 1); temp%=m;
		temp *= fact[n - l]; temp %= m;
		res += temp; res%=m;
	}

	cout << res << endl;
}