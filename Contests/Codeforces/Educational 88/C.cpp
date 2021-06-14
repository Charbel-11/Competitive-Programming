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
		ll h, c, t; cin >> h >> c >> t;
		if (2*t <= h+c) { cout << 2 << endl; continue; }
		
		ll c1 = (- t + c) / (h + c - 2 * t);
		ll k1 = 2 * c1 - 1, k2 = 2 * (c1 + 1) - 1;
		ll first = c1 * h + (c1 - 1)*c, second = (c1 + 1) * h + (c1)*c;
		double diff1 = (double)abs(first - (k1*t)) / k1, diff2 = (double)abs(second - (k2*t)) / k2;

		ll ans = k2;
		if (diff1 <= diff2) { ans = k1; }
		cout << max(ans, 1ll) << endl;
	}
}