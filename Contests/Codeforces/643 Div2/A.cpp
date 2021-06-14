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

int product(ll a) {
	ll mi = 9, ma = 0;
	while (a) {
		mi = min(mi, a % 10);
		ma = max(ma, a % 10);
		a /= 10;
	}
	return (int)mi*ma;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		ll a, k; cin >> a >> k; k--;

		while (k--) {
			int prod = product(a);
			if (prod == 0) { break; }
			a += prod;
		}

		cout << a << endl;
	}
}