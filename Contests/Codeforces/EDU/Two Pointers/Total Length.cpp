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

	int n; ll s; cin >> n >> s;
	vector<ll> a(n); for (auto& x : a) { cin >> x; }

	ll ans = 0;
	int l = 0; ll curS = 0;
	for (int r = 0; r < n; r++) {
		curS += a[r];
		while (curS > s) { curS -= a[l++]; }

		ll range = r - l + 1;
		ans += (range * (range + 1)) / 2;
	}

	cout << ans << '\n';
}