#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		int n; ll x; cin >> n >> x;
		ll maxDamage = 0;
		ll maxBlow = 0;

		for (int i = 0; i < n; i++) {
			ll d, h; cin >> d >> h;

			maxBlow = max(maxBlow, d);
			maxDamage = max(maxDamage, d - h);
		}

		if (maxBlow >= x) { cout << 1 << endl; continue; }
		if (maxDamage == 0) { cout << -1 << endl; continue; }

		ll res = x / maxDamage;
		x -= res * maxDamage;
		bool b = true;
		if (x) { res++; b = false; }

		x += maxDamage;
		while (x <= maxBlow) {
			x += maxDamage;
			res--;

			if (b) { res++; b = false; }
		}

		cout << res << endl;
	}
}