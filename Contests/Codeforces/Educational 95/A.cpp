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
		ll x, y, k; cin >> x >> y >> k;
		ll needed = k + y * k - 1;
		ll ans = (needed + x - 2) / (x - 1) + k;
		cout << ans << '\n';
	}
}