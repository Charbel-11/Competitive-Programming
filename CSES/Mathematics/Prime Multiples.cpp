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

	ll n; int k; cin >> n >> k;
	vector<ll> a(k); for (auto& x : a) { cin >> x; }

	ll ans = 0;
	for (int i = 1; i < (1 << k); i++) {
		bool odd = false, skip = false;
		ll cur = 1;

		for (int j = 0; j < k; j++) {
			if (!(i & (1 << j))) { continue; }
			if (a[j] > (n + cur - 1) / cur) { skip = true; break; }
			odd = !odd; cur *= a[j];
			if (cur <= 0 || cur > n) { skip = true; break; }
		}
		if (skip) { continue; }

		if (odd) { ans += n / cur; }
		else { ans -= n / cur; }
	}
	cout << ans << '\n';
}