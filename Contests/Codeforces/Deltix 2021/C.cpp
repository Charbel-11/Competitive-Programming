#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<ll> c(n); for (auto& x : c) { cin >> x; }

	ll ans = 0;
	for (int l = 0; l < n; l += 2) {
		if (l + 1 < n) { ans += min(c[l], c[l + 1]); }
		if (l + 3 >= n) { break; }

		ll openNeeded = c[l + 1], closeNeeded = c[l + 2];
		for (int r = l + 3; r < n; r += 2) {
			ll openAv = c[l] - openNeeded;
			ll closeAv = c[r] - closeNeeded;
			ll curAv = max(0ll, min(openAv, closeAv));
			ans += curAv;

			if (openAv >= 0 && closeAv >= 0 && openNeeded > 0 && closeNeeded > 0) { ans++; }

			if (r + 1 < n) {
				closeNeeded -= c[r - 1];

				ll diff = abs(c[r] - c[r - 1]);
				if (c[r] > c[r - 1]) {
					ll rem = min(closeNeeded, diff);
					closeNeeded -= rem; diff -= rem;
					openNeeded += diff;
				}
				else {
					closeNeeded += diff;
				}

				closeNeeded += c[r + 1];
			}
		}
	}

	cout << ans << '\n';
}