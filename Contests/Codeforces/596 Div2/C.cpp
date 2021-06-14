#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int countBits(ll num) {
	int res = 0;
	while (num) {
		if (num & 1) { res++; }
		num /= 2;
	}
	return res;
}

int main() {
	ll n, p; cin >> n >> p;

	ll k = 1;
	while (k < (long long)1e5) {
		ll t = n - k * p;
		if (t < 0) { cout << -1 << endl; return 0; }
		if (countBits(t) <= k && t >= k) {
			cout << k << endl; return 0;
		}
		k++;
	}

	cout << -1 << endl;
}