#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll gcd(ll x, ll y) {
	return x ? gcd(y % x, x) : y;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll L, R; cin >> L >> R;
	ll ans = 1;
	for (ll diff = R - L; diff > 0; diff--) {
		for (ll l = L; l + diff <= R; l++) {
			if (gcd(l, l + diff) == 1) {
				ans = diff; break;
			}
		}
		if (ans > 1) { break; }
	}

	cout << ans << '\n';
}