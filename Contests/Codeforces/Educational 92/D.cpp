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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		ll n, k; cin >> n >> k;
		ll l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
		if (l1 > l2) { swap(l1, l2); swap(r1, r2); }

		if (l2 < r1){
			ll intersect = (min(r1, r2) - max(l1, l2));
			k -= intersect * n;
			if (k < 0) { cout << 0 << '\n'; continue; }

			//Go right
			ll diff = abs(r1 - r2);
			r1 = r2 = max(r1, r2); 

			ll moves = diff * n, points = n * diff;
			if (points >= k) { cout << k << '\n'; continue; }
			k -= points;

			//Go left
			diff = l2 - l1;	points = n * diff;
			if (points >= k) { cout << moves + k << '\n'; continue; }
			moves += diff * n; k -= points;

			cout << moves + k * 2ll << '\n';
			continue;
		}

		//Not intersecting
		ll maxR = max(r1 - l1, r2 - l2);
		ll minR = min(r1 - l1, r2 - l2);
		ll diff = l2 - r1, full = 0, moves = 0;
		ll ans = (ll)1e17;

		while (k > 0 && full != n) {
			full++; moves += diff;
			if (k <= maxR) { ans = min(ans, moves + k); k = -1; break; }
			k -= maxR; moves += maxR;
			if (k <= diff + minR) { ans = min(ans, moves + k);  k = -1; break; }
			k -= (diff + minR); moves += diff + minR;
			ans = min(ans, moves + k * 2);
		}
		if (k > 0) { ans = min(ans, moves + k * 2); }

		cout << ans << '\n';
	}
}