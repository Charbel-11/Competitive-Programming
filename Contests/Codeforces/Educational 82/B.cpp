#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int T; cin >> T;

	while (T--) {
		ll n, g, b; cin >> n >> g >> b;
		ll needed = (n + 1) / 2;
		ll goodPeriodsNeeded = (needed + g - 1) / g;

		ll ans = (b + g) * (goodPeriodsNeeded - 1);
		needed -= g * (goodPeriodsNeeded - 1);
		ans += needed;

		cout << max(ans, n) << endl;
	}
}